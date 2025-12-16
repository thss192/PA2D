#pragma once
// ============================================
// PA2D - CPU-Side Software 2D Graphics Library
// ============================================
// Copyright (c) 2025 PrismArch. All rights reserved.
//
// Repository: https://github.com/thss192/PA2D
// Documentation: https://PrismArch.cn
// Contact: 1926224891@qq.com
//
// Version: 1.0.0-beta.1 (Released: 2025-12-16)
//
// License: Personal/educational use only.
//          See documentation for full terms.
//
// Features:
//   - CPU software renderer with AVX2 optimization
//   - Windows GDI for font rendering
//   - Thread-per-window architecture
//   - Multi-window support (copy/move semantics)
//   - Anti-aliased rendering by default
// 
// Requirements:
//   - Windows 7 or later
//   - Modern C++ compiler (Visual Studio 2015+ recommended)
//   - For best performance: CPU with AVX2 support
// ============================================
#include <vector>
#include <array> 
#include <cstdint>
#include <string>
#include <functional>
namespace pa2d {
    // ==================== VERSION ====================
    const char* getVersion();
    // ==================== Color(ARGB) ====================
    struct Color {
        union { 
            uint32_t data, argb;
            struct { uint8_t b, g, r, a; };
            struct { uint32_t rgb : 24, _ : 8; };
        };
        Color() :data() {}
        Color(uint32_t argb) :data(argb) {}
        Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) :a(a), r(r), g(g), b(b) {}
        Color(uint8_t alpha, const Color& base) : data((static_cast<uint32_t>(alpha) << 24) | (base.data & 0x00FFFFFF)) {}
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
        Buffer(const Buffer& other);
        Buffer(Buffer&& other) noexcept;
        ~Buffer();
        size_t size() const { return (size_t)width * height; }
        Color& at(int x, int y);
        const Color& at(int x, int y) const;
        void changeSize(int width, int height, const Color& color = None);
        void clear(const Color& color = None);
        Buffer& operator=(const Buffer& other);
        Buffer& operator=(Buffer&& other) noexcept;
        explicit operator bool() const { return color && width > 0 && height > 0; }
    };
    // ==================== TEXT STYLES ====================
    // Windows GDI text rendering (anti-aliasing optional)
    void setTextAntiAliasing(bool enable);
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
        FontStyle operator|(const FontStyle&) const;
        bool operator&(const FontStyle&) const;
        bool operator==(const FontStyle&) const;
    };
    // ==================== GEOMETRY STYLE ====================
    // Fluent-style drawing configuration with user-defined literals
    // Use: Style().fill(Red).stroke(Black).width(2.0f) 
    // Or:  0xffff0000_fill + 0xff000000_stroke + 2.0_w + 5.0_r
    struct Style {
        Color fillColor_ = 0;       Style& fill(Color v) { fillColor_ = v; return *this; }
        Color strokeColor_ = 0;     Style& stroke(Color v) { strokeColor_ = v; return *this; }
        float strokeWidth_ = 1.0f;  Style& width(float v) { strokeWidth_ = v; return *this; }
        float radius_ = 0.0f;       Style& radius(float v) { radius_ = v; return *this; }
        bool arc_ = true;           Style& arc(bool v) { arc_ = v; return *this; }
        bool edges_ = true;         Style& edges(bool v) { edges_ = v; return *this; }
        Style() = default;
        Style(Color fill, Color stroke = 0, float width = 1.0f, float radius = 0.0f, bool Arc = true, bool edges = true);
        Style operator+(const Style& other) const;
        Style& operator+=(const Style& other);
    };
    // ==================== GEOMETRY OBJECTS ====================
    // Geometry objects with unified transformation interface
    struct Point {
        float x, y;
        Point() :x(0), y(0) {}; Point(float x, float y);
        Point operator+(const Point&) const; Point& operator+=(const Point&);
        Point operator-(const Point&) const; Point& operator-=(const Point&);
        Point operator-() const; bool operator==(const Point&) const; bool operator!=(const Point&) const;
        Point& operator+=(float); Point operator+(float) const;
        Point& operator-=(float); Point operator-(float) const;
        Point& operator*=(float); Point operator*(float) const;
        Point& operator/=(float); Point operator/(float) const;
        friend Point operator*(float, const Point&);
        Point& translate(float dx, float dy);
        Point& scale(float factorX, float factorY); Point& scale(float factor);
        Point& rotate(float angleDegrees, float centerX = 0, float centerY = 0);
    };
    struct BoundingBox {
        float x, y;
        float width, height;
        BoundingBox(float x = 0, float y = 0, float width = 0, float height = 0);
        float left() const;
        float right() const;
        float bottom() const;
        float top() const;
        Point center() const;
        bool contains(float px, float py) const;
    };
    // ==================== SHAPE SYSTEM MACROS ====================
    // Helper macros for uniform shape interface declaration
    // Note: Geometric transformations default to origin (0,0) 
    //       Use OnSelf variants for transformations around shape's own center
    class Shape {
    public:
        enum class GeometryType { POINTS, LINE, POLYGON, RECT, TRIANGLE, CIRCLE, ELLIPTIC, SECTOR, RAY };
        GeometryType getType() const { return type; }
#define PA2D_SHAPE_API(ClassName, PureVirtual) \
    virtual ClassName& translate(float dx, float dy) PureVirtual; \
    virtual ClassName& translate(Point delta) PureVirtual; \
    virtual ClassName& scale(float factor) PureVirtual; \
    virtual ClassName& scale(float factorX, float factorY) PureVirtual; \
    virtual ClassName& scaleOnSelf(float factorX, float factorY) PureVirtual; \
    virtual ClassName& scaleOnSelf(float factor) PureVirtual; \
    virtual ClassName& rotate(float angleDegrees, float centerX, float centerY) PureVirtual; \
    virtual ClassName& rotate(float angleDegrees, Point center) PureVirtual; \
    virtual ClassName& rotate(float angleDegrees) PureVirtual; \
    virtual ClassName& rotateOnSelf(float angleDegrees) PureVirtual; \
    virtual bool contains(Point point) const PureVirtual; \
    virtual BoundingBox getBoundingBox() const PureVirtual; \
    virtual Point getCenter() const PureVirtual;
        PA2D_SHAPE_API(Shape, = 0);
    private:
        GeometryType type = GeometryType::POINTS;
    };
    struct Points : public Shape {
        std::vector<Point> points;
        Points(); Points(int size);
        Points(const std::vector<Point>& points);
        Points(std::vector<Point>&& points);
        Points& operator=(const std::vector<Point>& points);
        Points& operator=(std::vector<Point>&& points);
        PA2D_SHAPE_API(Points, override)
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
        Polygon(std::vector<Point>&& points);
        std::vector<Point>& getPoints();    const std::vector<Point>& getPoints() const;
        Polygon& operator=(const std::vector<Point>& vec);
        Polygon& operator=(std::vector<Point>&& points);
        PA2D_SHAPE_API(Polygon, override)
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
        Rect& operator=(const std::vector<Point>& points);
        Point& operator[](size_t index);
        const Point& operator[](size_t index) const;
        PA2D_SHAPE_API(Rect, override)
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
        Triangle& operator=(const std::vector<Point>& points);
        Point& operator[](size_t index);
        const Point& operator[](size_t index) const;
        PA2D_SHAPE_API(Triangle, override)
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
        Ray& spin(float degrees);
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
            Builder scale(float factor)&&;
            Builder scale(float factorX, float factorY)&&;
            Builder scaleOnSelf(float factor)&&;
            Builder scaleOnSelf(float factorX, float factorY)&&;
            Builder rotate(float angleDegrees)&&;
            Builder rotate(float angleDegrees, float centerX, float centerY)&&;
            Builder rotateOnSelf(float angleDegrees)&&;
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
        Canvas(const Buffer& buffer); Canvas(Buffer&& buffer);
        Canvas(const Canvas& other); Canvas(Canvas&& other) noexcept;
        Canvas(const char* filePath);
        Canvas(int resourceID);
        int width() const; int height() const;
        Color& at(int x, int y); const Color& at(int x, int y) const;
        const Buffer& getBuffer() const; Buffer& getBuffer();
        Canvas& operator=(const Canvas& other);
        Canvas& operator=(const Buffer& buffer);
        // ==================== IMAGE OPERATIONS ====================
        bool loadImage(const char* filePath, int width = -1, int height = -1);
        bool loadImage(int resourceID, int width = -1, int height = -1);
        Canvas& clear(Color color = White);
        Canvas& crop(int x, int y, int width, int height);
        Canvas& resize(int width, int height);
        Canvas& changeSize(int newWidth, int newHeight, uint32_t color = White);
        // ==================== BASIC SHAPES ====================
        Canvas& line(float x0, float y0, float x1, float y1, const Style& style);
        Canvas& polyline(const std::vector<Point>& points, const Style& style, bool closed = false);
        Canvas& polygon(const std::vector<Point>& vertices, const Style& style);
        Canvas& triangle(float x0, float y0, float x1, float y1, float x2, float y2, const Style& style);
        Canvas& rect(float x, float y, float width, float height, const Style& style);
        Canvas& rect(float cx, float cy, float width, float height, float angle, const Style& style);
        Canvas& roundRect(float x, float y, float width, float height, const Style& style);
        Canvas& roundRect(float centerX, float centerY, float width, float height, float angle, const Style& style);
        Canvas& circle(float centerX, float centerY, float radius, const Style& style);
        Canvas& ellipse(float cx, float cy, float width, float height, const Style& style);
        Canvas& ellipse(float cx, float cy, float width, float height, float angle, const Style& style);
        Canvas& sector(float cx, float cy, float radius, float startAngleDeg, float endAngleDeg, const Style& style);
        // ==================== OBJECT-ORIENTED DRAWING ====================
        Canvas& draw(const Points&, const Style&);
        Canvas& draw(const Line&, const Style&);
        Canvas& draw(const Ray&, const Style&);
        Canvas& draw(const Rect&, const Style&);
        Canvas& draw(const Triangle&, const Style&);
        Canvas& draw(const Polygon&, const Style&);
        Canvas& draw(const Circle&, const Style&);
        Canvas& draw(const Elliptic&, const Style&);
        Canvas& draw(const Sector&, const Style&);
        // ==================== IMAGE BLENDING ====================
        Canvas& copy(const Canvas& src, int dstX = 0, int dstY = 0);
        Canvas& blend(const Canvas& other, int x = 0, int y = 0, int alpha = 255, int Mode = 0);
        Canvas& alphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& addBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& multiplyBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& screenBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& overlayBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& destAlphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        // ==================== IMAGE TRANSFORM DRAWING ====================
        Canvas& draw(const Canvas& src, float centerX, float centerY, int alpha = 255);
        Canvas& drawRotated(const Canvas& src, float centerX, float centerY, float rotation = 0.0f);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scaleX, float scaleY);
        Canvas& drawScaledTo(const Canvas& src, float centerX, float centerY, int width, int height);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scale = 1.0f);
        Canvas& drawTransformed(const Canvas& src, float centerX, float centerY, float scale = 1.0f, float rotation = 0.0f);
        Canvas& drawTransformed(const Canvas& src, float centerX, float centerY, float scaleX, float scaleY, float rotation);
        // ==================== IMAGE TRANSFORM COPIES ====================
        Canvas cropped(int x, int y, int width, int height) const;
        Canvas scaled(float scaleX, float scaleY) const;
        Canvas scaledTo(int width, int height) const;
        Canvas scaled(float scale) const;
        Canvas rotated(float rotation) const;
        Canvas transformed(float scale = 1.0f, float rotation = 0.0f) const;
        Canvas transformed(float scaleX, float scaleY, float rotation) const;
        // ==================== TEXT RENDERING ====================
        Canvas& text(const std::wstring& text, int x, int y, const Color& color = Black, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& text(const std::string& text, int x, int y, const Color& color = Black, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::wstring& text, int centerX, int centerY, const Color& color = Black, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::string& text, int centerX, int centerY, const Color& color = Black, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::wstring& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = Black, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::string& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = Black, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::wstring& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = Black, int preferredFontSize = -1, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::string& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = Black, int preferredFontSize = -1, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
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
        Window(int width=-1, int height=-1, const char* title="PA2D Window");
        Window(const Window&);
        Window(Window&&);
        Window& operator=(const Window&);
        Window& operator=(Window&&);
        ~Window();
        // ==================== PUBLIC MEMBERS ====================olm <
        HWND hwnd = nullptr;
        int width = 0;
        int height = 0;
        bool isClosed = false;
        // ==================== WINDOW STATE ====================
        bool isOpen() const;
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
        Window& setClientSize(int width, int height);
        Window& setWindowSize(int width, int height);
        void getPosition(int& x, int& y) const;
        void getClientSize(int& width, int& height) const;
        void getWindowSize(int& width, int& height) const;
        // ==================== RENDERING ====================
        Window& render(const Canvas& canvas, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0, int width = -1, int height = -1, bool clearBackground = true, COLORREF bgColor = 0);
        Window& renderCentered(const Canvas& canvas, bool clearBackground = true, COLORREF bgColor = 0);
        Window& render(const Buffer& buffer, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0, int width = -1, int height = -1, bool clearBackground = true, COLORREF bgColor = 0);
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
    void line(Buffer&, float, float, float, float, const Color&, float);
    void polyline(Buffer&, const std::vector<Point>&, const Color&, float, bool);
    void polygon(Buffer&, const std::vector<Point>&, const Color&, const Color&, float);
    void triangle(Buffer&, float, float, float, float, float, float, const Color&, const Color&, float);
    void rect(Buffer&, float, float, float, float, const Color&, const Color&, float);
    void rect(Buffer&, float, float, float, float, float, const Color&, const Color&, float);
    void roundRect(Buffer&, float, float, float, float, const Color&, const Color&, float, float);
    void roundRect(Buffer&, float, float, float, float, float, const Color&, const Color&, float, float);
    void circle(Buffer&, float, float, float, const Color&, const Color&, float);
    void ellipse(Buffer&, float, float, float, float, const Color&, const Color&, float);
    void ellipse(Buffer&, float, float, float, float, float, const Color&, const Color&, float);
    void sector(Buffer&, float, float, float, float, float, const Color&, const Color&, float, bool, bool);
    bool loadImage(Buffer&, const char*);
    bool loadImage(Buffer&, int);
    bool loadImage(Buffer&, void*, int);
    void drawScaled(Buffer&, const Buffer&, float, float, float, float);
    void drawScaledTo(Buffer&, const Buffer&, float, float, int, int);
    void drawScaled(Buffer&, const Buffer&, float, float, float);
    void drawRotated(Buffer&, const Buffer&, float, float, float);
    void drawTransformed(Buffer&, const Buffer&, float, float, float, float);
    void drawTransformed(Buffer&, const Buffer&, float, float, float, float, float);
    void copy(Buffer& dest, const Buffer& src);
    Buffer crop(const Buffer&, int, int, int, int);
    Buffer scaled(const Buffer&, float, float);
    Buffer scaledTo(const Buffer&, int, int);
    Buffer scaled(const Buffer&, float);
    Buffer rotated(const Buffer&, float);
    Buffer transformed(const Buffer&, float, float);
    Buffer transformed(const Buffer&, float, float, float);
    void alphaBlend(const Buffer&, Buffer&, int, int, int);
    void copyBlend(const Buffer&, Buffer&, int, int);
    void addBlend(const Buffer&, Buffer&, int, int, int);
    void multiplyBlend(const Buffer&, Buffer&, int, int, int);
    void screenBlend(const Buffer&, Buffer&, int, int, int);
    void overlayBlend(const Buffer&, Buffer&, int, int, int);
    void destAlphaBlend(const Buffer&, Buffer&, int, int, int);
    bool text(Buffer&, const std::wstring&, float, float, const Color&, int, const std::wstring&, const FontStyle&);
    bool text(Buffer&, const std::string&, float, float, const Color&, int, const std::string&, const FontStyle&);
    bool textInRect(Buffer&, const std::wstring&, float, float, float, float, const Color&, int, const std::wstring&, const FontStyle&);
    bool textInRect(Buffer&, const std::string&, float, float, float, float, const Color&, int, const std::string&, const FontStyle&);
    bool textFitRect(Buffer&, const std::wstring&, float, float, float, float, const Color&, int, const std::wstring&, const FontStyle&);
    bool textFitRect(Buffer&, const std::string&, float, float, float, float, const Color&, int, const std::string&, const FontStyle&);
    bool textCentered(Buffer&, const std::wstring&, float, float, const Color&, int, const std::wstring&, const FontStyle&);
    bool textCentered(Buffer&, const std::string&, float, float, const Color&, int, const std::string&, const FontStyle&);
}
#ifndef PA2D_DISABLE_LITERALS
inline pa2d::Style operator"" _fill(unsigned long long hex) { return pa2d::Style().fill((uint32_t)hex); }
inline pa2d::Style operator"" _stroke(unsigned long long hex) { return pa2d::Style().stroke((uint32_t)hex); }
inline pa2d::Style operator"" _w(long double w) { return pa2d::Style().width((float)w); }
inline pa2d::Style operator"" _w(unsigned long long w) { return pa2d::Style().width((float)w); }
inline pa2d::Style operator"" _r(long double r) { return pa2d::Style().radius((float)r); }
inline pa2d::Style operator"" _r(unsigned long long r) { return pa2d::Style().radius((float)r); }
namespace pa2d {extern const pa2d::Style
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
    // Parse color string to ARGB value
    // Supported formats: "#RRGGBB", "#AARRGGBB", "R,G,B", "A,R,G,B"
    // Note: No other formats (color names, rgb(), etc.) are supported
    uint32_t parseColorString(const char* str, size_t len);
}
inline pa2d::Style operator"" _fill(const char* str, size_t len) { return pa2d::Style().fill(pa2d::parseColorString(str, len)); }
inline pa2d::Style operator"" _stroke(const char* str, size_t len) { return pa2d::Style().stroke(pa2d::parseColorString(str, len)); }
#endif

#ifdef _WIN32
#pragma comment(lib, "ole32.lib")        // COM object creation (WIC factory initialization)
#pragma comment(lib, "WindowsCodecs.lib")// Windows Imaging Component (PNG/JPEG decoding)
#pragma comment(lib, "gdiplus.lib")      // High-quality font rendering (anti-aliasing, font caching)
#pragma comment(lib, "user32.lib")       // Window management, message processing, input events
#pragma comment(lib, "gdi32.lib")        // Screen rendering, device contexts, bitmap operations
#pragma comment(lib, "shell32.lib")      // File drag-drop, clipboard chain, Shell integration
#endif
#pragma comment(linker, "/ARCH:AVX2")

#ifdef _DEBUG
#pragma comment(lib, "pa2dd.lib")
#else
#pragma comment(lib, "pa2d.lib")
#endif