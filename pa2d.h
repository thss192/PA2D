#pragma once
#include <windows.h>
#include <cmath>
#include <vector>
#include <cstdint>
#include <string>
#include <memory>
#include <future>
#pragma comment(lib, "gdiplus.lib")
namespace pa2d {
    // ==================== 基础颜色(ARGB) ====================
    struct Color {
        union { uint32_t data, argb; struct { uint8_t b, g, r, a; }; struct { uint32_t rgb : 24, _ : 8; }; };
        Color() :data(0) {} Color(uint32_t argb) :data(argb) {} Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) :a(a), r(r), g(g), b(b) {}
        Color(uint8_t alpha, const Color& base) : data((static_cast<uint32_t>(alpha) << 24) | (base.data & 0x00FFFFFF)) {}
        operator uint32_t() const { return data; }
    };
    const Color White = 0xFFFFFFFF, Black = 0xFF000000, None = 0x00000000;
    const Color Red = 0xFFFF0000, Green = 0xFF00FF00, Blue = 0xFF0000FF;
    const Color Cyan = 0xFF00FFFF, Magenta = 0xFFFF00FF, Yellow = 0xFFFFFF00;
    const Color Gray = 0xFF808080, LightGray = 0xFFC0C0C0, DarkGray = 0xFF404040;
    // ==================== Buffer 位图存储 ====================
    struct Buffer {
        Color* color;
        int width, height;
        Buffer(int width = 0, int height = 0, const Color& init_color = 0);
        Buffer(const Buffer& other);Buffer(Buffer&& other) noexcept;
        ~Buffer();
        size_t size() const { return static_cast<size_t>(width) * height; }
        Color& at(int x, int y);
        const Color& at(int x, int y) const;
        static void copy(Buffer& dest, const Buffer& src);
        void resize(int newWidth, int newHeight, const Color& clear_color = 0);
        void clear(const Color& clear_color = 0);
        Buffer& operator=(const Buffer& other);
        Buffer& operator=(Buffer&& other) noexcept;
        explicit operator bool() const { return color && width > 0 && height > 0;; }
    };
    // ==================== Point结构体 ====================
    struct Point {
        float x, y;
        Point(); Point(float x, float y);
        Point operator+(const Point& other) const; Point& operator+=(const Point& other);
        Point operator-(const Point& other) const; Point& operator-=(const Point& other);
        Point operator-() const; bool operator==(const Point& other) const; bool operator!=(const Point& other) const;
        Point& operator+=(float scalar); Point& operator-=(float scalar);
        Point& operator*=(float scalar); Point& operator/=(float scalar);
        friend Point operator+(const Point&, float); friend Point operator+(float, const Point&);
        friend Point operator-(const Point&, float); friend Point operator-(float, const Point&);
        friend Point operator*(const Point&, float); friend Point operator*(float, const Point&);
        friend Point operator/(const Point&, float); friend Point operator/(float, const Point&);
        // 变换
        Point& translate(float dx, float dy);
        Point& scale(float factorX, float factorY); Point& scale(float factor);
        Point& rotate(float angleDegrees, float centerX = 0, float centerY = 0);
    };
    class Points;class Line;class Ray;class Triangle;class Rect;class Polygon;class Circle;class Elliptic;class Sector;struct Style;
    // ==================== 文字样式系统 ====================
    enum class TextEncoding { ANSI, UTF8, UTF16, CURRENT };
    TextEncoding textEncoding(TextEncoding newEncoding = TextEncoding::CURRENT);
    void setTextAntiAliasing(bool enable);
    class FontStyle {
        int styleBits_; float italicAngle_ , rotationAngle_;
    public:
        static const FontStyle Regular, Bold,Italic,Underline,Strikeout;
        FontStyle italicAngle(float angle) const;
        FontStyle rotation(float angle) const;
        FontStyle operator|(const FontStyle& other) const;
        bool operator&(const FontStyle& other) const;
        bool operator==(const FontStyle& other) const;
    };
    bool measureText(const std::wstring& text, int fontSize, const std::wstring& fontName, const FontStyle& style, int& width, int& height);
    bool measureText(const std::string& text, int fontSize, const std::string& fontName, const FontStyle& style, int& width, int& height);
    int calculateFontSize(const std::wstring& text, float maxWidth, float maxHeight, int preferredFontSize = 12, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    int calculateFontSize(const std::string& text, float maxWidth, float maxHeight, int preferredFontSize = 12, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    // ==================== Canvas 画布系统 ====================
    class Canvas {
        Buffer buffer;
    public:
        // ==================== 构造和基础访问 ====================
        Canvas();
        Canvas(int width, int height, Color background = 0xFFFFFFFF);
        Canvas(const Buffer& buf); Canvas(Buffer&& buf);
        Canvas(const Canvas& other); Canvas(Canvas&& other) noexcept;
        Canvas(const char* filePath); Canvas(int resourceID);

        int width() const; int height() const;
        Color& at(int x, int y); const Color& at(int x, int y) const;
        const Buffer& getBuffer() const; Buffer& getBuffer();

        // ==================== 图像操作 ====================
        bool loadImage(const char* filePath); bool loadImage(int resourceID);
        Canvas& clear(Color color = 0xFFFFFFFF);
        Canvas& crop(int x, int y, int width, int height);
        Canvas& resize(int newWidth, int newHeight, uint32_t clearColor = 0xFFFFFFFF);

        // ==================== 基础图形 ====================
        // 线和多边形
        Canvas& line(float x0, float y0, float x1, float y1, const Color& color, float lineWidth = 1.0f);
        Canvas& polyline(const std::vector<Point>& points, const Color& color, float lineWidth = 1.0f, bool closed = false);
        Canvas& polygon(const std::vector<Point>& vertices, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        // 三角形
        Canvas& triangle(float ax, float ay, float bx, float by, float cx, float cy, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        // 矩形相关
        Canvas& rect(float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& rect(float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& roundRect(float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& roundRect(float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
        // 圆形和椭圆
        Canvas& circle(float centerX, float centerY, float radius, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& ellipse(float cx, float cy, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& ellipse(float cx, float cy, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        // 扇形
        Canvas& sector(float cx, float cy, float radius, float startAngleDeg, float endAngleDeg, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f, bool drawArc = true, bool drawRadialEdges = true);

        // ==================== 图像混合 ====================
        Canvas& alphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& addBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& multiplyBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& screenBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& overlayBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& destAlphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& copyBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);

        // ==================== 图像变换绘制 ====================
        Canvas& draw(const Canvas& other, int x = 0, int y = 0, int alpha = 255);
        Canvas& drawRotated(const Canvas& src, float centerX, float centerY, float rotation = 0.0f);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scaleX, float scaleY);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scale = 1.0f);
        Canvas& drawScaledRotated(const Canvas& src, float centerX, float centerY, float scale = 1.0f, float rotation = 0.0f);

        // ==================== 图像变换副本 ====================
        Canvas createCropped(int x, int y, int width, int height) const;
        Canvas createScaled(float scaleX, float scaleY) const;
        Canvas createRotated(float rotation) const;
        Canvas createScaledRotated(float scale = 1.0f, float rotation = 0.0f) const;

        // ==================== 文本绘制 ====================
        Canvas& text(const std::wstring& text, int x, int y, const Color& color = 0xFF000000, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::wstring& text, int centerX, int centerY, const Color& color = 0xFF000000, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::wstring& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::wstring& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int preferredFontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);

        Canvas& text(const std::string& text, int x, int y, const Color& color = 0xFF000000, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::string& text, int centerX, int centerY, const Color& color = 0xFF000000, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::string& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::string& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int preferredFontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
    
        // ==================== 面向对象图形绘制 ====================
        Canvas& draw(const Points&, const Style&);
        Canvas& draw(const Line&, const Style&);
        Canvas& draw(const Ray&, const Style&);
        Canvas& draw(const Rect&, const Style&);
        Canvas& draw(const Triangle&, const Style&);
        Canvas& draw(const Polygon&, const Style&);
        Canvas& draw(const Circle&, const Style&);
        Canvas& draw(const Elliptic&, const Style&);
        Canvas& draw(const Sector&, const Style&);
        // 数组批量绘制
        template<typename GeometryType> Canvas& drawBatch(const std::vector<GeometryType>& geometries, const Style& style);
        template<typename GeometryType> Canvas& drawBatch(const std::vector<GeometryType>& geometries, const std::vector<Style>& styles);
    };
    // ==================== 窗口系统 ====================
    struct KeyEvent {
        int keyCode;
        bool pressed;
    };
    struct MouseEvent {
        int x, y;
        int button;       // 0=左键, 1=右键, 2=中键, -1=滚轮, -2=移动, -3=离开
        bool pressed;     // 对于按键按下/释放
        int wheelDelta;  // 滚轮增量
    };
    // 事件回调类型定义
    using KeyCallback = std::function<void(const KeyEvent&)>;
    using MouseCallback = std::function<void(const MouseEvent&)>;
    using ResizeCallback = std::function<void(int, int)>;
    using CharCallback = std::function<void(wchar_t)>;
    using FocusCallback = std::function<void(bool)>;
    using CloseCallback = std::function<bool()>;
    using MenuCallback = std::function<void(int)>;
    using FileListCallback = std::function<void(const std::vector<std::string>&)>;

    class Window {
    public:
        // ==================== 常用功能 ====================
        // 构造/析构
        Window(int width, int height, const char* title);
        ~Window();

        // 公开成员变量
        HWND hwnd_ = nullptr;
        int width_ = 0;
        int height_ = 0;
        bool shouldClose_ = false;

        // 窗口状态查询
        bool isOpen() const { return !shouldClose_; }
        bool isVisible() const { return hwnd_ && IsWindowVisible(hwnd_); }
        bool isMaximized() const { return hwnd_ && IsZoomed(hwnd_); }
        bool isMinimized() const { return hwnd_ && IsIconic(hwnd_); }
        bool isFullscreen() const { return isFullscreen_; }

        // 窗口操作
        Window& show();
        Window& hide();
        Window& close();
        Window& setVisible(bool visible);
        Window& focus();

        // 窗口大小和位置
        Window& setPosition(int x, int y);
        Window& setClientSize(int width, int height);
        Window& setWindowSize(int width, int height);
        void getPosition(int& x, int& y) const;
        void getClientSize(int& width, int& height) const;
        void getWindowSize(int& width, int& height) const;

        // 渲染功能
        void render(const Canvas& canvas, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0, int width = -1, int height = -1, bool clearBackground = true, COLORREF bgColor = 0);
        void renderCentered(const Canvas& canvas, bool clearBackground = true, COLORREF bgColor = 0);
        void render(const Buffer& buffer, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0, int width = -1, int height = -1, bool clearBackground = true, COLORREF bgColor = 0);
        void renderCentered(const Buffer& buffer, bool clearBackground = true, COLORREF bgColor = 0);

        // ==================== 事件回调 ====================
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

        // ==================== 输入状态 ====================
        std::pair<int, int> getMousePosition() const;
        bool isMouseInWindow() const;
        bool isMouseButtonPressed(int button) const;
        bool isKeyPressed(int vkCode) const;
        bool isShiftPressed() const;
        bool isCtrlPressed() const;
        bool isAltPressed() const;

        // ==================== 高级窗口控制 ====================
        Window& maximize();
        Window& minimize();
        Window& restore();
        Window& flash(bool flashTitleBar = true);
        Window& setResizable(bool resizable);
        Window& setAlwaysOnTop(bool onTop);
        Window& setBorderless(bool borderless);
        Window& setFullscreen(bool fullscreen);
        Window& setMinSize(int minWidth, int minHeight);
        Window& setMaxSize(int maxWidth, int maxHeight);
        Window& setMinimizeButton(bool show);
        Window& setMaximizeButton(bool show);
        Window& setCloseButton(bool show);

        // ==================== 外观设置 ====================
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

        // ==================== 输入控制 ====================
        Window& setMouseCapture(bool capture);
        static std::pair<int, int> getGlobalMousePosition();

        // ==================== 剪贴板和文件 ====================
        bool setClipboardText(const std::string& text);
        std::string getClipboardText();
        bool setClipboardText(const std::wstring& text);
        std::wstring getClipboardTextW();
        bool hasClipboardText() const;
        std::vector<std::string> getClipboardFiles();
        bool hasClipboardFiles() const;
        Window& enableFileDrop(bool enable = true);

        // ==================== 菜单功能 ====================
        Window& setMenu(HMENU menu);
        HMENU createMenu();
        HMENU createPopupMenu();
        Window& appendMenuItem(HMENU menu, const char* text, int id, bool enabled = true);
        Window& appendMenuSeparator(HMENU menu);
        Window& appendMenuPopup(HMENU menu, const char* text, HMENU popupMenu);
        Window& destroyMenu(HMENU menu);

        // ==================== 系统信息 ====================
        static std::pair<int, int> getScreenSize();
        static std::pair<int, int> getWorkAreaSize();
        static double getDpiScale();

        // 禁止拷贝
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
   private:
       std::thread messageThread_; std::atomic<bool> running_{ false }; DWORD threadId_ = 0; std::promise<bool> initPromise_;
       LONG borderlessOriginalStyle_ = 0; LONG borderlessOriginalExStyle_ = 0; int borderlessOriginalClientWidth_ = 0; int borderlessOriginalClientHeight_ = 0; bool borderlessStateSaved_ = false; bool isBorderless_ = false;
       LONG fullscreenOriginalStyle_ = 0; LONG fullscreenOriginalExStyle_ = 0; RECT fullscreenOriginalRect_ = { 0 }; bool fullscreenStateSaved_ = false; bool isFullscreen_ = false;
       int minWidth_ = 0; int minHeight_ = 0; int maxWidth_ = 0; int maxHeight_ = 0; std::atomic<bool> trackingMouse_{ false };
       struct DirectBuffer { BITMAPINFO bmi = {}; } directBuffer_;
       int lastClientWidth_ = 0; int lastClientHeight_ = 0; int lastBufferWidth_ = 0; int lastBufferHeight_ = 0; bool sizeChanged_ = true;
       KeyCallback keyCb_; MouseCallback mouseCb_; ResizeCallback resizeCb_; CharCallback charCb_; FocusCallback focusCb_; CloseCallback closeCb_; MenuCallback menuCb_; FileListCallback dropCb_; FileListCallback clipboardFilesCb_;
       HWND nextClipboardViewer_ = nullptr; HDC persistentDC_ = nullptr;
    };
    // ==================== 几何样式 ====================
    struct Style {
        Style(Color fill = 0, Color stroke = 0, float width = 1.0f, float radius = 0.0f,
            float opacity = 1.0f, bool drawArc = true, bool drawRadialEdges = true);
        Color fill_;          Style& fill(Color v);
        Color stroke_;        Style& stroke(Color v);
        float width_;         Style& width(float v);
        float opacity_;       Style& opacity(float v);
        float radius_;        Style& radius(float v);
        bool drawArc_;        Style& drawArc(bool v);
        bool drawRadialEdges_; Style& drawRadialEdges(bool v);
    };
    // ==================== 几何对象 ====================
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
#define SHAPE_API(ClassName, PureVirtual) \
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
    virtual Point getCenter() const PureVirtual
#define TO_POINTS() \
    operator std::vector<Point>()&; \
    operator std::vector<Point>() const&; \
    operator std::vector<Point>()&&
    class Shape {
    public:
        enum class GeometryType {
            POINTS,
            LINE,
            POLYGON,
            RECT,
            TRIANGLE,
            CIRCLE,
            ELLIPTIC,
            SECTOR,
            RAY
        };
        virtual ~Shape() = default;
        GeometryType getType() const { return type; }
        SHAPE_API(Shape, = 0);
    private:
        GeometryType type = GeometryType::POINTS;
    };
    class Points : public Shape, public std::vector<Point> {
    public:
        Points();
        Points(int size);
        Points(const std::vector<Point>& points);
        Points(std::vector<Point>&& points);
        Points& operator=(const std::vector<Point>& points);
        Points& operator=(std::vector<Point>&& points);
        SHAPE_API(Points, override);
    };
    class Line : public Shape {
        Points points_;
    public:
        Line();
        Line(float x0, float y0, float x1, float y1);
        Line(const Point& start, const Point& end);
        Line& start(float x, float y);
        Line& start(const Point& start);
        Line& end(float x, float y);
        Line& end(const Point& end);
        Point& start();
        Point& end();
        const Point& start() const;
        const Point& end() const;
        SHAPE_API(Line, override);
        TO_POINTS();
    };
    class Polygon : public Shape {
    private:
        Points points_;
        static bool is_point_in_polygon_odd_even(const Point& P, const Points& vertices);
    public:
        Polygon();
        Polygon(const std::vector<Point>& points);
        Polygon(std::vector<Point>&& points);
        Points& getPoints();
        const Points& getPoints() const;
        Polygon& operator=(const std::vector<Point>& vec);
        Polygon& operator=(std::vector<Point>&& points);
        SHAPE_API(Polygon, override);
        TO_POINTS();
    };
    class Rect : public Shape {
        Points points_;
        Point center_{ 0, 0 };
        float width_ = 0.0f;
        float height_ = 0.0f;
        float rotation_ = 0.0f;
        bool verticesDirty_ = true;
    public:
        Rect();
        Rect(float centerX, float centerY, float width, float height, float rotation = 0.0f);
        Rect(const std::vector<Point>& points);
        Rect& center(const Point& center);
        Rect& center(float x, float y);
        Rect& width(float width);
        Rect& height(float height);
        Rect& rotation(float rotation);
        Point center() const;
        Point& center();
        float width() const;
        float height() const;
        float rotation() const;
        auto begin();
        auto end();
        auto begin() const;
        auto end() const;
        Rect& operator=(const std::vector<Point>& points);
        Point& operator[](size_t index);
        const Point& operator[](size_t index) const;
        SHAPE_API(Rect, override);
        TO_POINTS();
    };
    class Triangle : public Shape {
        Points points_;
    public:
        Triangle();
        Triangle(const Point& p0, const Point& p1, const Point& p2);
        Triangle(float px0, float py0, float px1, float py1, float px2, float py2);
        Triangle(const std::vector<Point>& points);
        auto begin();
        auto end();
        auto begin() const;
        auto end() const;
        Triangle& operator=(const std::vector<Point>& points);
        Point& operator[](size_t index);
        const Point& operator[](size_t index) const;
        SHAPE_API(Triangle, override);
        TO_POINTS();
    };
    class Elliptic : public Shape {
        Point center_;
        float width_;
        float height_;
        float rotation_;
    public:
        Elliptic();
        Elliptic(float centerX, float centerY, float width, float height, float rotation = 0.0f);

        Elliptic& x(float x);
        Elliptic& y(float y);
        Elliptic& center(const Point& center);
        Elliptic& center(float x, float y);
        Elliptic& width(float width);
        Elliptic& height(float height);
        Elliptic& rotation(float rotation);
        float x() const;
        float y() const;
        Point center() const;
        Point& center();
        float width() const;
        float height() const;
        float rotation() const;
        SHAPE_API(Elliptic, override);
        TO_POINTS();
        operator Point()&;
        operator Point() const&;
    };
    class Circle : public Shape {
        Point center_;
        float radius_;
    public:
        Circle();
        Circle(float centerX, float centerY, float radius);
        Circle(const Point& center, float radius);
        Circle& x(float x);
        Circle& y(float y);
        Circle& center(const Point& center);
        Circle& center(float x, float y);
        Circle& radius(float radius);
        float x() const;
        float y() const;
        Point center() const;
        Point& center();
        float radius() const;
        SHAPE_API(Circle, override);
        TO_POINTS();
        operator Point()&;
        operator Point() const&;
    };
    class Sector : public Shape {
        Point center_;
        float radius_;
        float startAngle_;
        float endAngle_;
    public:
        Sector();
        Sector(Point center, float radius, float startAngle = 0.0f, float endAngle = 360.0f);
        Sector(float centerX, float centerY, float radius, float startAngle = 0.0f, float endAngle = 360.0f);
        Sector& x(float x);
        Sector& y(float y);
        Sector& center(const Point& center);
        Sector& center(float x, float y);
        Sector& radius(float radius);
        Sector& startAngle(float startAngle);
        Sector& endAngle(float endAngle);
        float x() const;
        float y() const;
        Point center() const;
        Point& center();
        float radius() const;
        float startAngle() const;
        float endAngle() const;
        SHAPE_API(Sector, override);
        TO_POINTS();
        operator Point()&;
        operator Point() const&;
    };
    class Ray : public Shape {
        Points points_;
        float length_ = 0.0f;
        float angle_ = 0.0f;
    public:
        Ray();
        Ray(float x1, float y1, float x2, float y2);
        Ray(const Point& start, const Point& end);
        Ray(const Point& start, float length = 0.0f, float angle = 0.0f);
        Ray& start(float x, float y);
        Ray& start(const Point& start);
        Ray& end(float x, float y);
        Ray& end(const Point& end);
        Point& start();
        Point& end();
        const Point& start() const;
        const Point& end() const;
        Ray& angle(float angle);
        Ray& length(float length);
        float length() const;
        float angle() const;
        Ray& toEnd();
        Ray& stretch(float factor);
        Ray& spin(float degrees);
        SHAPE_API(Ray, override);
        TO_POINTS();
    };
#undef SHAPE_API
#undef TO_POINTS
    // ==================== 路径构造方法 ====================
    class Path {
    private:
        class Builder {
            std::vector<Point> points_;
        public:
            Builder(float startX, float startY);
            Builder(const Builder&) = delete;
            Builder& operator=(const Builder&) = delete;
            Builder(Builder&&) = default;
            Builder& operator=(Builder&&) = default;
            Builder& move(float dx, float dy);
            Builder& moveTo(float x, float y);
            Builder& translate(float dx, float dy);
            Builder& scale(float factor);
            Builder& scale(float factorX, float factorY);
            Builder& scaleOnSelf(float factor);
            Builder& scaleOnSelf(float factorX, float factorY);
            Builder& rotate(float angleDegrees);
            Builder& rotate(float angleDegrees, float centerX, float centerY);
            Builder& rotateOnSelf(float angleDegrees);
            operator std::vector<Point>()&&;
            operator std::vector<Point>()&;
            operator std::vector<Point>() const& = delete;
            template<typename T>
            operator T()&&;
            template<typename T>
            operator T()&;
            template<typename T>
            operator T() const& = delete;
        };
        Path() = delete;
        ~Path() = delete;
        Path(const Path&) = delete;
        Path& operator=(const Path&) = delete;
    public:
        static Builder from(float x, float y);
        static Builder from(const Point& start);
    };
    // ==================== 底层图层算法 ====================
    // 图形渲染
    void drawLine(Buffer& buffer, float fx0, float fy0, float fx1, float fy1, const Color& color, float lineWidth = 1.0f);
    void drawPolyline(Buffer& buffer, const std::vector<Point>& points, const Color& color, float lineWidth = 1.0f, bool closed = false);
    void drawPolygon(Buffer& buffer, const std::vector<Point>& vertices, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawTriangle(Buffer& buffer, float ax, float ay, float bx, float by, float cx, float cy, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRect(Buffer& buffer, float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRect(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRoundRect(Buffer& buffer, float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRoundRect(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawCircle(Buffer& buffer, float centerX, float centerY, float radius, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawEllipse(Buffer& buffer, float cx, float cy, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawEllipse(Buffer& buffer, float cx, float cy, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawSector(Buffer& buffer, float cx, float cy, float radius, float startAngleDeg, float endAngleDeg, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f, bool drawArc = true, bool drawRadialEdges = true);
    // ==================== 底层图像算法 ====================
    // 图像加载
    bool load_image(Buffer& buffer, const char* filePath);
    bool load_image(Buffer& buffer, int resourceID);
    bool load_image(Buffer& buffer, void* hInstance, int resourceID);
    // 图像变换
    void drawScaledBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float scaleX, float scaleY);
    void drawScaledBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float scale);
    void drawRotatedBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float rotation);
    void drawScaledRotatedBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float scale, float rotation);
    Buffer crop(const Buffer& src, int x, int y, int w, int h);
    Buffer scaleBuffer(const Buffer& src, float scaleX, float scaleY);
    Buffer scaleBuffer(const Buffer& src, float factor);
    Buffer rotatedBuffer(const Buffer& src, float rotation);
    Buffer scaledRotatedBuffer(const Buffer& src, float scale = 1.0f, float rotation = 0.0f);
    // 图像混合
    void CopyBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    void AlphaBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    void AddBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    void MultiplyBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    void ScreenBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    void OverlayBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    void DestAlphaBlend(const Buffer& src, Buffer& dst, int dstX = 0, int dstY = 0, int opacity = 255);
    // ==================== 底层文字算法 ====================
    //文字渲染函数
    bool drawText(Buffer& buffer, const std::string& text, float x, float y, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextInRect(Buffer& buffer, const std::string& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextFitRect(Buffer& buffer, const std::string& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int preferredFontSize = 12, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextCentered(Buffer& buffer, const std::string& text, float centerX, float centerY, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    bool drawText(Buffer& buffer, const std::wstring& text, float x, float y, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextInRect(Buffer& buffer, const std::wstring& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextFitRect(Buffer& buffer, const std::wstring& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int preferredFontSize = 12, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextCentered(Buffer& buffer, const std::wstring& text, float centerX, float centerY, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    // ==================== Style 字面量扩展(可关闭) ====================
#ifndef PA2D_DISABLE_LITERALS  // Style 字面量开关宏
    struct StyleBuilder;
    struct TagBase {
        virtual ~TagBase() = default;
        virtual void applyTo(Style& style) const = 0;
        virtual std::unique_ptr<TagBase> clone() const = 0;
    };
    struct StyleBuilder {
        std::vector<std::unique_ptr<TagBase>> tags;
        StyleBuilder();
        StyleBuilder(const StyleBuilder& other);
        StyleBuilder& operator=(const StyleBuilder& other);
        operator Style() const;
    };
#define TAG(Name, Type) \
    struct Name##Tag : public TagBase { \
        Type val_; \
        Name##Tag(Type val) : val_(val) {} \
        void applyTo(Style& style) const override; \
        std::unique_ptr<TagBase> clone() const override; \
        operator StyleBuilder() const; \
        operator Style() const;\
    };
    TAG(Fill, uint32_t)      // 填充颜色
    TAG(Stroke, uint32_t)    // 描边颜色
    TAG(Width, float)       // 线宽
    TAG(Radius, float)      // 圆角半径
    TAG(Opacity, float)     // 不透明度
    TAG(DrawArc, bool)      // 是否绘制弧线
    TAG(DrawRadialEdges, bool) // 是否绘制径向边
#undef TAG
    namespace detail {uint32_t parseColorString(const char* str, size_t len);}
    inline FillTag operator"" _fill(unsigned long long hex) { return FillTag(static_cast<uint32_t>(hex)); }
    inline StrokeTag operator"" _stroke(unsigned long long hex) { return StrokeTag(static_cast<uint32_t>(hex)); }
    inline WidthTag operator"" _w(long double w) { return WidthTag(static_cast<float>(w)); }
    inline WidthTag operator"" _w(unsigned long long w) { return WidthTag(static_cast<float>(w)); }
    inline RadiusTag operator"" _r(long double r) { return RadiusTag(static_cast<float>(r)); }
    inline RadiusTag operator"" _r(unsigned long long r) { return RadiusTag(static_cast<float>(r)); }
    inline OpacityTag operator"" _o(long double o) { return OpacityTag(static_cast<float>(o)); }
    inline FillTag operator"" _fill(const char* str, size_t len) { return FillTag(detail::parseColorString(str, len)); }
    inline StrokeTag operator"" _stroke(const char* str, size_t len) { return StrokeTag(detail::parseColorString(str, len)); }
    extern const DrawArcTag draw_arc;
    extern const DrawArcTag no_arc;
    extern const DrawRadialEdgesTag draw_edges;
    extern const DrawRadialEdgesTag no_edges;
    StyleBuilder operator+(const StyleBuilder& builder, const TagBase& newTag);
#endif // PA2D_DISABLE_LITERALS
    // ==================== 模板函数定义 ====================
    template<typename GeometryType>
    Canvas& Canvas::drawBatch(const std::vector<GeometryType>& geometries, const Style& style) {
        for (const auto& geometry : geometries)draw(geometry, style);
        return *this;
    }
    template<typename GeometryType>
    Canvas& Canvas::drawBatch(const std::vector<GeometryType>& geometries, const std::vector<Style>& styles) {
        for (size_t i = 0; i < geometries.size(); ++i)draw(geometries[i], (i < styles.size()) ? styles[i] : (!styles.empty()) ? styles.back() : Style());
        return *this;
    }
}
