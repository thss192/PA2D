#pragma once
// PA2D - CPU-Side Software 2D Graphics Library
// Copyright (c) 2025 PrismArch
//
// Repository:    https://github.com/thss192/PA2D
// Documentation: https://PrismArch.cn
// Version:       1.0.0-beta1 (2025-12-20)
// Free: Personal/Educational | Commercial: Licensed
//
// Features:
//   - CPU software renderer with AVX2 optimization
//   - Thread-per-window architecture  
//   - Multi-window support
//
// Requirements:
//   - Windows 7+
//   - C++11 compiler (VS2015+ recommended)
//   - AVX2 CPU for best performance
#include <vector>
#include <array> 
#include <cstdint>
#include <string>
#include <functional>
namespace pa2d {
    // ==================== VERSION ====================
    const char* getVersion();
    // ==================== CPU REQUIREMENT ====================
    // AVX2 hardware requirement check - executes at program startup
    // If CPU lacks AVX2 support, displays error message and terminates
    static const struct AVX2_Verifier {
        AVX2_Verifier();
    }AVX2_CHECK_INSTANCE;
    // ==================== Color(ARGB) ====================
    struct Color {
        union { 
            uint32_t data, argb;
            struct { uint8_t b, g, r, a; };
            struct { uint32_t rgb : 24, _ : 8; };
        };
        Color() :data(0) {}
        Color(uint32_t argb) :data(argb) {}
        Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) :a(a), r(r), g(g), b(b) {}
        Color(uint8_t r, uint8_t g, uint8_t b) : a(255), r(r), g(g), b(b) {}
        Color(uint8_t alpha, const Color& base) : data(((uint32_t)alpha << 24) | (base.data & 0x00FFFFFF)) {}
        operator uint32_t() const { return data; }
    };
    extern const Color White, Black, None, Red, Green, Blue, Cyan, Magenta, Yellow, Gray, LightGray, DarkGray;
    // ==================== BUFFER ====================
    // Pixel buffer container with SIMD-optimized operations
    // Note: For best performance, access color pointer directly instead of using at()
    // All rendering is off-screen to Buffers - Window renders Buffer to display
    struct Buffer {
        Color* color;        // Direct pixel data access (row-major layout)
        int width, height;
        Buffer(int width = 0, int height = 0, const Color& color = None);
        Buffer(const Buffer& rhs);
        Buffer(Buffer&& rhs) noexcept;
        ~Buffer();
        size_t size() const { return (size_t)width * height; }
        Color& at(int x, int y);
        const Color& at(int x, int y) const;
        void resize(int width, int height, const Color& color = None);
        void clear(const Color& color = None);
        Buffer& operator=(const Buffer& rhs);
        Buffer& operator=(Buffer&& rhs) noexcept;
        explicit operator bool() const { return color && width > 0 && height > 0; }
    };
    // ==================== TEXT STYLES ====================
    // Windows GDI text rendering (anti-aliasing optional)
    void setTextAntialias(bool enable);
    // String encoding configuration
    enum class TextEncoding { ANSI, UTF8};
    TextEncoding getTextEncoding();
    void setTextEncoding(TextEncoding encoding);
    class FontStyle {
        int styleBits_; float italicAngle_, rotationAngle_;
    public:
        static const FontStyle Regular, Bold, Italic, Underline, Strikeout;
        FontStyle italicAngle(float angle) const;
        FontStyle rotation(float angle) const;
        FontStyle operator|(const FontStyle& rhs) const;
        bool operator&(const FontStyle& rhs) const;
        bool operator==(const FontStyle& rhs) const;
    };
    // ==================== GEOMETRY STYLE ====================
    // Fluent-style drawing configuration with user-defined literals
    // Use: Style().fill(Red).stroke(Black).width(2.0f) 
    // Or:  0xffff0000_fill + 0xff000000_stroke + 2.0_w + 5.0_r
    struct Style {
        Color fill_;        Style& fill(Color);
        Color stroke_;      Style& stroke(Color);
        float width_;       Style& width(float);
        float radius_ ;     Style& radius(float);
        bool arc_;          Style& arc(bool);
        bool edges_;        Style& edges(bool);
        Style(Color fill_ = 0, Color stroke_ = 0, float width_ = 1.0f, float radius_ = 0.0f, bool arc_ = true, bool edges_ = true);
        Style operator+(const Style& rhs) const;
        Style& operator+=(const Style& rhs);
    };
    // ==================== GEOMETRY OBJECTS ====================
    // Geometry objects with unified transformation interface
    struct Point {
        float x, y;
        Point() :x(0), y(0) {};
        Point(float x, float y);
        Point operator+(const Point& rhs) const;    Point& operator+=(const Point& rhs);
        Point operator-(const Point& rhs) const;    Point& operator-=(const Point& rhs);
        Point& operator+=(float rhs);   Point operator+(float rhs) const;
        Point& operator-=(float rhs);   Point operator-(float rhs) const;
        Point& operator*=(float rhs);   Point operator*(float rhs) const;
        Point& operator/=(float rhs);   Point operator/(float rhs) const;
        Point operator-() const;
        bool operator==(const Point& rhs) const;
        bool operator!=(const Point& rhs) const;
        friend Point operator*(float scalar, const Point& point);
        Point& translate(float dx, float dy);
        Point& scale(float scaleX, float scaleY); Point& scale(float scale);
        Point& rotate(float angle, float centerX = 0, float centerY = 0);
    };
    struct PointInt { int x, y; };
    struct Size { int width, height; };
    class Rect;
    // ==================== SHAPE SYSTEM MACROS ====================
    // Helper macros for uniform shape interface declaration
    // Note: Geometric transformations default to origin (0,0) 
    //       Use OnSelf variants for transformations around shape's own center
    class Shape {
    public:
        enum class GeometryType { POINTS, LINE, POLYGON, RECT, TRIANGLE, CIRCLE, ELLIPTIC, SECTOR, RAY };
        GeometryType getType() const { return type_; }
#define PA2D_SHAPE_API(ClassName, PureVirtual) \
    virtual ClassName& translate(float dx, float dy) PureVirtual; \
    virtual ClassName& translate(Point delta) PureVirtual; \
    virtual ClassName& scale(float scale) PureVirtual; \
    virtual ClassName& scale(float scaleX, float scaleY) PureVirtual; \
    virtual ClassName& scaleOnSelf(float scaleX, float scaleY) PureVirtual; \
    virtual ClassName& scaleOnSelf(float scale) PureVirtual; \
    virtual ClassName& rotate(float angle, float centerX, float centerY) PureVirtual; \
    virtual ClassName& rotate(float angle, Point center) PureVirtual; \
    virtual ClassName& rotate(float angle) PureVirtual; \
    virtual ClassName& rotateOnSelf(float angle) PureVirtual; \
    virtual bool contains(Point point) const PureVirtual; \
    virtual Rect getBoundingBox() const PureVirtual; \
    virtual Point getCenter() const PureVirtual;
        PA2D_SHAPE_API(Shape, = 0);
    private:
        GeometryType type_ = GeometryType::POINTS;
    };
    struct Points : public Shape {
        std::vector<Point> points;
        Points();
        Points(int size);
        Points(std::vector<Point>& points);
        PA2D_SHAPE_API(Points, override)
        Points& operator=(const std::vector<Point>& points);
        operator std::vector<Point>() const;
        operator const std::vector<Point>& () const;
    };
    class Line : public Shape {
        Point start_, end_;
    public:
        Line(); Line(float x0, float y0, float x1, float y1);
        Line(const Point& start, const Point& end);
        Line& start(float x, float y); Line& start(const Point& start);
        Line& end(float x, float y);   Line& end(const Point& end);
        Point& start();                Point start() const;
        Point& end();                  Point end() const;
        PA2D_SHAPE_API(Line, override)
        operator std::vector<Point>() const;
    };
    class Polygon : public Shape {
        Points points_;
    public:
        Polygon(); Polygon(const std::vector<Point>& points);
        std::vector<Point>& getPoints();    const std::vector<Point>& getPoints() const;
        PA2D_SHAPE_API(Polygon, override)
        Polygon& operator=(const std::vector<Point>& vec);
        operator std::vector<Point>() const;
        operator const std::vector<Point>& () const;
    };
    class Rect : public Shape {
        Point center_;
        float width_, height_, rotation_;
        mutable std::array<Point, 4> cachedVertices_;
        mutable bool verticesDirty_;
    public:
        Rect(); Rect(float centerX, float centerY, float width, float height, float rotation = 0.0f);
        Rect(const std::vector<Point>& points);
        Rect& center(const Point& center);  Rect& center(float x, float y);
        Rect& width(float width);           float width() const;
        Rect& height(float height);         float height() const;
        Rect& rotation(float rotation);     float rotation() const;
        Point center() const;
        auto begin();   auto begin() const;
        auto end();     auto end() const;
        PA2D_SHAPE_API(Rect, override)
        Point& operator[](size_t index);
        const Point& operator[](size_t index) const;
        Rect& operator=(const std::vector<Point>& points);
        operator std::vector<Point>() const;
    };
    class Triangle : public Shape {
        std::array<Point, 3> vertices_;
    public:
        Triangle(); Triangle(const Point& p0, const Point& p1, const Point& p2);
        Triangle(float px0, float py0, float px1, float py1, float px2, float py2);
        Triangle(const std::vector<Point>& points);
        auto begin();   auto begin() const;
        auto end();     auto end() const;
        PA2D_SHAPE_API(Triangle, override)
        Point& operator[](size_t index);
        const Point& operator[](size_t index) const;
        Triangle& operator=(const std::vector<Point>& points);
        operator std::vector<Point>() const;
    };
    class Elliptic : public Shape {
        Point center_;
        float width_, height_, rotation_;
    public:
        Elliptic(); Elliptic(float centerX, float centerY, float width, float height, float rotation = 0.0f);
        Elliptic& x(float x);                   float x() const;
        Elliptic& y(float y);                   float y() const;
        Elliptic& center(const Point& center);  Elliptic& center(float x, float y);
        Elliptic& width(float width);           float width() const;
        Elliptic& height(float height);         float height() const;
        Elliptic& rotation(float rotation);     float rotation() const;
        Point& center();                        Point center() const;
        PA2D_SHAPE_API(Elliptic, override)
        operator Point() const;
    };
    class Circle : public Shape {
        Point center_;
        float radius_;
    public:
        Circle(); Circle(float centerX, float centerY, float radius);
        Circle(const Point& center, float radius);
        Circle& x(float x);                     float x() const;
        Circle& y(float y);                     float y() const;
        Circle& center(const Point& center);    Circle& center(float x, float y);
        Circle& radius(float radius);           float radius() const;
        Point& center();                        Point center() const;
        PA2D_SHAPE_API(Circle, override)
        operator Point() const;
    };
    class Sector : public Shape {
        Point center_;
        float radius_, startAngle_, endAngle_;
    public:
        Sector(); Sector(Point center, float radius, float startAngle = 0.0f, float endAngle = 360.0f);
        Sector(float centerX, float centerY, float radius, float startAngle = 0.0f, float endAngle = 360.0f);
        Sector& x(float x);                     float x() const;
        Sector& y(float y);                     float y() const;
        Sector& center(const Point& center);    Sector& center(float x, float y);
        Sector& radius(float radius);           float radius() const;
        Sector& startAngle(float startAngle);   float startAngle() const;
        Sector& endAngle(float endAngle);       float endAngle() const;
        Point& center();                        Point center() const;
        PA2D_SHAPE_API(Sector, override)
        operator Point() const;
    };
    class Ray : public Shape {
        Point start_, end_;
        float length_, angle_;
    public:
        Ray(); Ray(float x1, float y1, float x2, float y2);
        Ray(const Point& start, const Point& end);
        Ray(const Point& start, float length = 0.0f, float angle = 0.0f);
        Ray& start(float x, float y);   Ray& start(const Point& start);
        Ray& end(float x, float y);     Ray& end(const Point& end);
        Point& start();                 Point start() const;
        Point& end();                   Point end() const;
        Ray& angle(float angle);        float angle() const;
        Ray& length(float length);      float length() const;
        Ray& toEnd();
        Ray& stretch(float factor);
        Ray& spin(float angle);
        PA2D_SHAPE_API(Ray, override)
        operator std::vector<Point>() const;
    };
#undef PA2D_SHAPE_API
    // ==================== PATH BUILDER ====================
    class Path {
        class Builder {
            std::vector<Point> points_;
        public:
            Builder(float startX, float startY);
            Builder(const Builder&) = delete;
            Builder& operator=(const Builder&) = delete;
            Builder(Builder&&) = default;
            Builder& operator=(Builder&&) = default;
            Builder move(float dx, float dy)&&;
            Builder moveTo(float x, float y)&&;
            Builder translate(float dx, float dy)&&;
            Builder scale(float scale)&&;
            Builder scale(float scaleX, float scaleY)&&;
            Builder scaleOnSelf(float scale)&&;
            Builder scaleOnSelf(float scaleX, float scaleY)&&;
            Builder rotate(float angle)&&;
            Builder rotate(float angle, float centerX, float centerY)&&;
            Builder rotateOnSelf(float angle)&&;
            template<typename T>T to()&& { return T(std::move(points_)); }
            template<typename T>operator T()&& { return T(std::move(points_)); }
            template<typename T>operator T()& { return T(points_); }
            template<typename T>operator T() const& = delete;
        };
        Path() = delete;
    public:
        static Builder from(float x, float y);
        static Builder from(const Point& start);
    };
    // ==================== CANVAS ====================
    // High-level drawing interface (proxy for Buffer API)
    // Each Canvas contains an internal Buffer with automatic management
    // All drawing operations are anti-aliased by default
    class Canvas {
        Buffer buffer_;
    public:
        Canvas();
        Canvas(int width, int height, Color background = White);
        Canvas(const Canvas& rhs);
        Canvas(Canvas&& rhs) noexcept;
        Canvas(const Buffer& rhs);
        Canvas(Buffer&& rhs) noexcept;
        Canvas& operator=(const Canvas& rhs);
        Canvas& operator=(const Canvas&& rhs) noexcept;
        Canvas& operator=(const Buffer& rhs);
        Canvas& operator=(const Buffer&& rhs) noexcept;
        Canvas(const char* filePath);
        Canvas(int resourceID);
        int width() const;
        int height() const;
        Color& at(int x, int y);
        const Color& at(int x, int y) const;
        Buffer& getBuffer();
        const Buffer& getBuffer() const; 
        // ==================== IMAGE OPERATIONS ====================
        bool loadImage(const char* filePath, int width = -1, int height = -1);
        bool loadImage(int resourceID, int width = -1, int height = -1);
        Canvas& clear(Color color = White);
        Canvas& crop(int left, int top, int width, int height);
        Canvas& resize(int width, int height);
        Canvas& resizeBuffer(int newWidth, int newHeight, uint32_t color = White);
        // ==================== BASIC SHAPES ====================
        Canvas& line(float startX, float startY, float endX, float endY, const Style& style);
        Canvas& polyline(const std::vector<Point>& points, const Style& style, bool closed = false);
        Canvas& polygon(const std::vector<Point>& vertices, const Style& style);
        Canvas& triangle(float x0, float y0, float x1, float y1, float x2, float y2, const Style& style);
        Canvas& rect(float left, float top, float width, float height, const Style& style);
        Canvas& rect(float centerX, float centerY, float width, float height, float angle, const Style& style);
        Canvas& circle(float centerX, float centerY, float radius, const Style& style);
        Canvas& ellipse(float centerX, float centerY, float width, float height, const Style& style);
        Canvas& ellipse(float centerX, float centerY, float width, float height, float angle, const Style& style);
        Canvas& sector(float centerX, float centerY, float radius, float startAngle, float endAngle, const Style& style);
        // ==================== OBJECT-ORIENTED DRAWING ====================
        Canvas& draw(const Shape& shape, const Style& style);
        // ==================== IMAGE BLENDING ====================
        Canvas& copy(const Canvas& src, int dstX = 0, int dstY = 0);
        Canvas& blend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255, int mode = 0);
        Canvas& alphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& addBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& multiplyBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& screenBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& overlayBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& destAlphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        // ==================== IMAGE TRANSFORM DRAWING ====================
        Canvas& draw(const Canvas& src, float centerX, float centerY, int alpha = 255);
        Canvas& drawResized(const Canvas& src, float centerX, float centerY, int width, int height);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scaleX, float scaleY);
        Canvas& drawRotated(const Canvas& src, float centerX, float centerY, float rotation);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scale);
        Canvas& drawTransformed(const Canvas& src, float centerX, float centerY, float scale, float rotation);
        Canvas& drawTransformed(const Canvas& src, float centerX, float centerY, float scaleX, float scaleY, float rotation);
        // ==================== IMAGE TRANSFORM COPIES ====================
        Canvas cropped(int left, int top, int width, int height) const;
        Canvas resized(int width, int height) const;
        Canvas scaled(float scaleX, float scaleY) const;
        Canvas scaled(float scale) const;
        Canvas rotated(float rotation) const;
        Canvas transformed(float scale, float rotation) const;
        Canvas transformed(float scaleX, float scaleY, float rotation) const;
        // ==================== TEXT RENDERING ====================
        Canvas& text(const std::wstring& text, int x, int y, const Color& color = Black, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& text(const std::string& text, int x, int y, const Color& color = Black, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::wstring& text, int centerX, int centerY, const Color& color = Black, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::string& text, int centerX, int centerY, const Color& color = Black, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::wstring& text, int left, int top, int width, int height, const Color& color = Black, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::string& text, int left, int top, int width, int height, const Color& color = Black, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::wstring& text, int left, int top, int width, int height, const Color& color = Black, int preferredFontSize = -1, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::string& text, int left, int top, int width, int height, const Color& color = Black, int preferredFontSize = -1, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
    };
    // ==================== WINDOW ====================
    // Thread-per-window architecture (background message loops)
    // Multiple windows supported - avoid concurrent Canvas access across threads
    // Note: Windows are created hidden - must call window.show() to display
    //       Windows use explicit rendering - call render() after show() and for content updates
    //       Resize may clip content - listen to onResize event and re-render accordingly
    struct KeyEvent {
        int keyCode;
        bool pressed;
    };
    struct MouseEvent {
        int x, y;
        int button;       // Button identifier: 0=Left, 1=Right, 2=Middle, -1=Wheel, -2=Move, -3=Leave
        bool pressed;     // Press/release for buttons
        int wheelDelta;   // Wheel increment
    };
    // Event callback type definitions
    using KeyCallback = std::function<void(const KeyEvent&)>;
    using MouseCallback = std::function<void(const MouseEvent&)>;
    using ResizeCallback = std::function<void(int, int)>;
    using CharCallback = std::function<void(wchar_t)>;
    using FocusCallback = std::function<void(bool)>;
    using CloseCallback = std::function<bool()>;
    using MenuCallback = std::function<void(int)>;
    using FileListCallback = std::function<void(const std::vector<std::string>&)>;
    // ============= WINDOWS HANDLE TYPES =============
    class Window {
    public:
        // These are defined as void* to avoid conflicts with windows.h
        using HWND = void*;
        using HMENU = void*;
        using HICON = void*;
        using HCURSOR = void*;
        using COLORREF = unsigned long;
        // ==================== CONSTRUCTION & DESTRUCTION ====================
        // Window objects support both copy and move semantics for flexible window management.
        Window(int width = -1, int height = -1, const char* title="PA2D");
        Window(const Window& rhs);
        Window(Window&& rhs) noexcept;
        Window& operator=(const Window& rhs);
        Window& operator=(Window&& rhs) noexcept;
        ~Window();
        // ==================== HANDLE ACCESS ====================
        HWND getHandle() const;
        // ==================== WINDOW STATE ====================
        int width() const;
        int height() const;
        bool isOpen() const;
        bool isClosed() const;
        bool isVisible() const;
        bool isMaximized() const;
        bool isMinimized() const;
        bool isFullscreen() const;
        // ==================== WINDOW OPERATIONS ====================
        Window& show();
        Window& hide();
        Window& close();
        Window& setVisible(bool visible);
        Window& focus();
        // ==================== BLOCKING WAIT ====================
        // Note: Blocks this thread until the window is closed
        void waitForClose();
        // ==================== SIZE & POSITION ====================
        Window& setPosition(int x, int y);
        PointInt getPosition() const;
        Window& setClientSize(int width, int height);
        Size getClientSize() const;
        Window& setWindowSize(int width, int height);
        Size getWindowSize() const;
        // ==================== RENDERING ====================
        Window& render(const Canvas& canvas, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0, int width = -1, int height = -1, bool clearBackground = true, COLORREF bgColor = 0);
        Window& render(const Buffer& buffer, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0, int width = -1, int height = -1, bool clearBackground = true, COLORREF bgColor = 0);
        Window& renderCentered(const Canvas& canvas, bool clearBackground = true, COLORREF bgColor = 0);
        Window& renderCentered(const Buffer& buffer, bool clearBackground = true, COLORREF bgColor = 0);
        // ==================== EVENT CALLBACKS ====================
        Window& onKey(KeyCallback cb);
        Window& onMouse(MouseCallback cb);
        Window& onResize(ResizeCallback cb);
        Window& onClose(CloseCallback cb);
        Window& onChar(CharCallback cb);
        Window& onFocus(FocusCallback cb);
        Window& onMenu(MenuCallback cb);
        Window& onFileDrop(FileListCallback cb);
        Window& onClipboardFiles(FileListCallback cb);
        Window& disableClipboardFiles();
        // ==================== INPUT STATE ====================
        Point getMousePosition() const;
        bool isMouseInWindow() const;
        bool isMouseButtonPressed(int button) const;
        bool isKeyPressed(int vkCode) const;
        bool isShiftPressed() const;
        bool isCtrlPressed() const;
        bool isAltPressed() const;
        // ==================== WINDOW CONTROL ====================
        Window& maximize();
        Window& minimize();
        Window& restore();
        Window& flash(bool flashTitleBar = true);
        Window& setResizable(bool resizable);
        Window& setAlwaysOnTop(bool onTop);
        Window& setBorderless(bool borderless);
        Window& setTitlebarless(bool titlebarless);
        Window& setFullscreen(bool fullscreen);
        Window& setMinSize(int minWidth, int minHeight);
        Window& setMaxSize(int maxWidth, int maxHeight);
        Window& setMinimizeButton(bool show);
        Window& setMaximizeButton(bool show);
        Window& setCloseButton(bool show);
        // ==================== APPEARANCE ====================
        Window& setTitle(const char* title);
        Window& setTitle(const wchar_t* title);
        std::string getTitle() const;
        Window& setCursor(HCURSOR cursor);
        Window& setCursorDefault();
        Window& setCursorWait();
        Window& setCursorCross();
        Window& setCursorHand();
        Window& setCursorText();
        Window& setCursorVisibility(bool visible);
        Window& setCursorPosition(int x, int y);
        Window& setIcon(HICON icon);
        Window& setIconFromResource(int resourceId);
        // ==================== INPUT ====================
        Window& setMouseCapture(bool capture);
        // ==================== CLIPBOARD ====================
        bool setClipboardText(const std::string& text);
        std::string getClipboardText();
        bool setClipboardText(const std::wstring& text);
        std::wstring getClipboardTextW();
        bool hasClipboardText() const;
        std::vector<std::string> getClipboardFiles();
        bool hasClipboardFiles() const;
        Window& enableFileDrop(bool enable = true);
        // ==================== MENU ====================
        Window& setMenu(HMENU menu);
        HMENU createMenu();
        HMENU createPopupMenu();
        Window& appendMenuItem(HMENU menu, const char* text, int id, bool enabled = true);
        Window& appendMenuSeparator(HMENU menu);
        Window& appendMenuPopup(HMENU menu, const char* text, HMENU popupMenu);
        Window& destroyMenu(HMENU menu);
    private:
        struct Impl;Impl* pImpl_;
    };
    // ==================== SYSTEM  ====================
    Point getGlobalMousePosition();
    Point getScreenSize();
    Point getWorkAreaSize();
    double getDpiScale();
    // ==================== BUFFER API ====================
    // Direct buffer manipulation
    // Canvas acts as a proxy layer over these functions - each Canvas contains an internal Buffer
    void line(Buffer& buffer, float startX, float startY, float endX, float endY, const Color& color, float width);
    void polyline(Buffer& buffer, const std::vector<Point>& points, const Color& color, float width, bool closed);
    void polygon(Buffer& buffer, const std::vector<Point>& vertices, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void triangle(Buffer& buffer, float x0, float y0, float x1, float y1, float x2, float y2, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void rect(Buffer& buffer, float left, float top, float width, float height, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void rect(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void roundRect(Buffer& buffer, float left, float top, float width, float height, const Color& fillColor, const Color& strokeColor, float radius, float strokeWidth);
    void roundRect(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor, const Color& strokeColor, float radius, float strokeWidth);
    void circle(Buffer& buffer, float centerX, float centerY, float radius, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void ellipse(Buffer& buffer, float centerX, float centerY, float width, float height, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void ellipse(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor, const Color& strokeColor, float strokeWidth);
    void sector(Buffer& buffer, float centerX, float centerY, float radius, float startAngle, float endAngle, const Color& fillColor, const Color& strokeColor, float strokeWidth, bool arc, bool edges);
    bool loadImage(Buffer& buffer, const char* filePath);
    bool loadImage(Buffer& buffer, int resourceID);
    bool loadImage(Buffer& buffer, void* data, int size);
    void drawResized(Buffer& dest, const Buffer& src, float centerX, float centerY, int width, int height);
    void drawScaled(Buffer& dest, const Buffer& src, float centerX, float centerY, float scaleX, float scaleY);
    void drawScaled(Buffer& dest, const Buffer& src, float centerX, float centerY, float scale);
    void drawRotated(Buffer& dest, const Buffer& src, float centerX, float centerY, float rotation);
    void drawTransformed(Buffer& dest, const Buffer& src, float centerX, float centerY, float scale, float rotation);
    void drawTransformed(Buffer& dest, const Buffer& src, float centerX, float centerY, float scaleX, float scaleY, float rotation);
    void copy(Buffer& dest, const Buffer& src);
    Buffer crop(const Buffer& src, int left, int top, int width, int height);
    Buffer resized(const Buffer& src, int width, int height);
    Buffer scaled(const Buffer& src, float scaleX, float scaleY);
    Buffer scaled(const Buffer& src, float scale);
    Buffer rotated(const Buffer& src, float rotation);
    Buffer transformed(const Buffer& src, float scale, float rotation);
    Buffer transformed(const Buffer& src, float scaleX, float scaleY, float rotation);
    void alphaBlend(const Buffer& src, Buffer& dest, int x, int y, int alpha);
    void copyBlend(const Buffer& src, Buffer& dest, int x, int y);
    void addBlend(const Buffer& src, Buffer& dest, int x, int y, int alpha);
    void multiplyBlend(const Buffer& src, Buffer& dest, int x, int y, int alpha);
    void screenBlend(const Buffer& src, Buffer& dest, int x, int y, int alpha);
    void overlayBlend(const Buffer& src, Buffer& dest, int x, int y, int alpha);
    void destAlphaBlend(const Buffer& src, Buffer& dest, int x, int y, int alpha);
    bool text(Buffer& buffer, const std::wstring& text, float x, float y, const Color& color, int fontSize, const std::wstring& fontName, const FontStyle& style);
    bool text(Buffer& buffer, const std::string& text, float x, float y, const Color& color, int fontSize, const std::string& fontName, const FontStyle& style);
    bool textCentered(Buffer& buffer, const std::wstring& text, float centerX, float centerY, const Color& color, int fontSize, const std::wstring& fontName, const FontStyle& style);
    bool textCentered(Buffer& buffer, const std::string& text, float centerX, float centerY, const Color& color, int fontSize, const std::string& fontName, const FontStyle& style);
    bool textInRect(Buffer& buffer, const std::wstring& text, float left, float top, float width, float height, const Color& color, int fontSize, const std::wstring& fontName, const FontStyle& style);
    bool textInRect(Buffer& buffer, const std::string& text, float left, float top, float width, float height, const Color& color, int fontSize, const std::string& fontName, const FontStyle& style);
    bool textFitRect(Buffer& buffer, const std::wstring& text, float left, float top, float width, float height, const Color& color, int preferredFontSize, const std::wstring& fontName, const FontStyle& style);
    bool textFitRect(Buffer& buffer, const std::string& text, float left, float top, float width, float height, const Color& color, int preferredFontSize, const std::string& fontName, const FontStyle& style);
}
#ifndef PA2D_DISABLE_LITERALS
inline pa2d::Style operator"" _fill(unsigned long long hex) { return pa2d::Style().fill((uint32_t)hex); }
inline pa2d::Style operator"" _stroke(unsigned long long hex) { return pa2d::Style().stroke((uint32_t)hex); }
inline pa2d::Style operator"" _w(long double w) { return pa2d::Style().width((float)w); }
inline pa2d::Style operator"" _w(unsigned long long w) { return pa2d::Style().width((float)w); }
inline pa2d::Style operator"" _r(long double r) { return pa2d::Style().radius((float)r); }
inline pa2d::Style operator"" _r(unsigned long long r) { return pa2d::Style().radius((float)r); }
namespace pa2d {extern const Style
    arc,    no_arc,    // Sector arc control
    edges,  no_edges,  // Sector edges control
    White_fill,     White_stroke,
    Black_fill,     Black_stroke,
    None_fill,      None_stroke,
    Red_fill,       Red_stroke,
    Green_fill,     Green_stroke,
    Blue_fill,      Blue_stroke,
    Cyan_fill,      Cyan_stroke,
    Magenta_fill,   Magenta_stroke,
    Yellow_fill,    Yellow_stroke,
    Gray_fill,      Gray_stroke,
    LightGray_fill, LightGray_stroke,
    DarkGray_fill,  DarkGray_stroke;
    uint32_t parseColorString(const char* str, size_t len);
}
// Supported formats: "#RRGGBB", "#AARRGGBB", "R,G,B", "A,R,G,B"
inline pa2d::Style operator"" _fill(const char* str, size_t len) { return pa2d::Style().fill(pa2d::parseColorString(str, len)); }
inline pa2d::Style operator"" _stroke(const char* str, size_t len) { return pa2d::Style().stroke(pa2d::parseColorString(str, len)); }
#endif

#ifdef _WIN32
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shell32.lib")
#endif
#pragma comment(linker, "/ARCH:AVX2")

#ifdef _DEBUG
#pragma comment(lib, "pa2dd.lib")
#else
#pragma comment(lib, "pa2d.lib")
#endif