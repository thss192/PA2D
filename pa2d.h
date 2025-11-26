#pragma once
#ifdef _WIN32
#define NOMINMAX  // 避免max,min冲突
#include <windows.h>
#endif
#include <cmath>
#include <vector>
#include <cstdint>
#include <string>
#include <memory>
#include <future>
#pragma comment(lib, "gdiplus.lib")

namespace pa2d {
    /* pa2d_math.h -- 几何库*/
    /* 宏定义 -- 用于简化多态代码*/
    namespace {
#define DECLARE_SHAPE_VIRTUAL_FUNCTIONS(ClassName, PureVirtual) \
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

#define DECLARE_POINT_CONVERSIONS() \
    operator std::vector<Point>()&; \
    operator std::vector<Point>() const&; \
    operator std::vector<Point>()&&
    }
    // ==================== 基础数学类型 ====================
    struct Point {
        float x, y;
        Point();
        Point(float x, float y);
        Point operator+(const Point& other) const;
        Point operator-(const Point& other) const;
        Point& operator+=(const Point& other);
        Point& operator-=(const Point& other);
        Point operator-() const;
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        Point& operator+=(float scalar);
        Point& operator-=(float scalar);
        Point& operator*=(float scalar);
        Point& operator/=(float scalar);
        friend Point operator+(const Point& point, float scalar);
        friend Point operator+(float scalar, const Point& point);
        friend Point operator-(const Point& point, float scalar);
        friend Point operator-(float scalar, const Point& point);
        friend Point operator*(const Point& point, float scalar);
        friend Point operator*(float scalar, const Point& point);
        friend Point operator/(const Point& point, float scalar);
        friend Point operator/(float scalar, const Point& point);
        Point& translate(float dx, float dy);
        Point& scale(float factor);
        Point& scale(float factorX, float factorY);
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
    // ==================== 图形基类 ====================
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
        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Shape, = 0);
    private:
        GeometryType type = GeometryType::POINTS;
    };
    // ==================== 图形对象 ====================
    class Points : public Shape, public std::vector<Point> {
    public:
        Points();
        Points(int size);
        Points(const std::vector<Point>& points);
        Points(std::vector<Point>&& points);

        Points& operator=(const std::vector<Point>& points);
        Points& operator=(std::vector<Point>&& points);

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Points, override);
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Line, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Polygon, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Rect, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Triangle, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Elliptic, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Circle, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Sector, override);
        DECLARE_POINT_CONVERSIONS();
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

        DECLARE_SHAPE_VIRTUAL_FUNCTIONS(Ray, override);
        DECLARE_POINT_CONVERSIONS();
    };

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
    // ==================== 颜色系统 ====================
    struct Color {
        union { uint32_t data, argb; struct { uint8_t b, g, r, a; }; struct { uint32_t rgb : 24, _ : 8; }; };
        Color() :data(0) {} Color(uint32_t argb) :data(argb) {} Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) :a(a), r(r), g(g), b(b) {}
        Color(uint8_t alpha, const Color& base) : data((static_cast<uint32_t>(alpha) << 24) | (base.data & 0x00FFFFFF)) {}
        operator uint32_t() const { return data; }
    };
    // 基础颜色
    namespace {
        const Color Red = 0xFFFF0000;
        const Color Green = 0xFF00FF00;
        const Color Blue = 0xFF0000FF;
        const Color White = 0xFFFFFFFF;
        const Color Black = 0xFF000000;
        const Color Yellow = 0xFFFFFF00;
        const Color Cyan = 0xFF00FFFF;
        const Color Magenta = 0xFFFF00FF;
        const Color Gray = 0xFF808080;
        const Color LightGray = 0xFFC0C0C0;
        const Color DarkGray = 0xFF404040;
        const Color Orange = 0xFFFFA500;
        const Color Pink = 0xFFFFC0CB;
        const Color Purple = 0xFF800080;
        const Color Brown = 0xFFA52A2A;
        const Color None = 0x00000000;
        const Color DarkBlue = 0xFF000080;
        const Color DarkGreen = 0xFF006400;
        const Color DarkRed = 0xFF8B0000;
        const Color LightBlue = 0xFFADD8E6;
        const Color LightGreen = 0xFF90EE90;
    }
    // ==================== 位图存储 ====================
    struct Buffer {
        Color* color;
        int width, height;

        explicit Buffer(int width = 0, int height = 0, const Color& init_color = 0x0);
        Buffer(const Buffer& other);
        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(const Buffer& other);
        Buffer& operator=(Buffer&& other) noexcept;
        ~Buffer();

        size_t size() const { return static_cast<size_t>(width) * height; }
        bool isValid() const { return color && width > 0 && height > 0; }
        Color& at(int x, int y);
        const Color& at(int x, int y) const;
        Color* getRow(int y);
        const Color* getRow(int y) const;

        static void copy(Buffer& dest, const Buffer& src);
        void resize(int newWidth, int newHeight, const Color& clear_color = 0x0);
        void clear(const Color& clear_color = 0x0);

        explicit operator bool() const { return isValid(); }
    };
    // ==================== 渲染算法 ====================
    // 图像加载
    bool load_image(Buffer& buffer, const char* filePath);
    bool load_image(Buffer& buffer, int resourceID);
    bool load_image(Buffer& buffer, void* hInstance, int resourceID);
    // 图像变换
    Buffer crop(const Buffer& src, int x, int y, int w, int h);
    void drawScaledBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float scaleX, float scaleY);
    void drawScaledBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float scale);
    void drawRotatedBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float rotation);
    void drawScaledRotatedBuffer(Buffer& dest, const Buffer& src, float centerX, float centerY, float scale, float rotation);
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
    // 图形渲染
    void drawLine(Buffer& buffer, float fx0, float fy0, float fx1, float fy1, const Color& color, float lineWidth = 1.0f);
    void drawPolyline(Buffer& buffer, const std::vector<Point>& points, const Color& color, float lineWidth = 1.0f, bool closed = false);
    void drawRect(Buffer& buffer, float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRect(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRoundRect(Buffer& buffer, float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawRoundRect(Buffer& buffer, float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawCircle(Buffer& buffer, float centerX, float centerY, float radius, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawTriangle(Buffer& buffer, float ax, float ay, float bx, float by, float cx, float cy, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawEllipse(Buffer& buffer, float cx, float cy, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawEllipse(Buffer& buffer, float cx, float cy, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    void drawSector(Buffer& buffer, float cx, float cy, float radius, float startAngleDeg, float endAngleDeg, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f, bool drawArc = true, bool drawRadialEdges = true);
    void drawPolygon(Buffer& buffer, const std::vector<Point>& vertices, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
    // 文字渲染
    /* --------- 文字编码设置 start --------*/
    enum class TextEncoding { ANSI, UTF8, UTF16, CURRENT };
    TextEncoding textEncoding(TextEncoding newEncoding = TextEncoding::CURRENT);
    /* --------- 文字编码设置  end  --------*/
    void setTextAntiAliasing(bool enable);
    // 文字样式结构体
    class FontStyle {
    private:
        int m_styleBits = 0;
        float m_italicAngle = 0.0f;
        float m_rotationAngle = 0.0f;
    public:
        static const FontStyle Regular;
        static const FontStyle Bold;
        static const FontStyle Italic;
        static const FontStyle Underline;
        static const FontStyle Strikeout;

        FontStyle italicAngle(float angle) const;
        FontStyle rotation(float angle) const;

        FontStyle operator|(const FontStyle& other) const;
        bool operator&(const FontStyle& other) const;
        bool operator==(const FontStyle& other) const;
    };
    // 文字测量函数
    bool measureText(const std::wstring& text, int fontSize, const std::wstring& fontName, const FontStyle& style, int& width, int& height);
    bool measureText(const std::string& text, int fontSize, const std::string& fontName, const FontStyle& style, int& width, int& height);
    int calculateFontSize(const std::wstring& text, float maxWidth, float maxHeight, int preferredFontSize = 12, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    int calculateFontSize(const std::string& text, float maxWidth, float maxHeight, int preferredFontSize = 12, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    //文字渲染函数（string版）
    bool drawText(Buffer& buffer, const std::string& text, float x, float y, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextInRect(Buffer& buffer, const std::string& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextFitRect(Buffer& buffer, const std::string& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int preferredFontSize = 12, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextCentered(Buffer& buffer, const std::string& text, float centerX, float centerY, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::string& fontName = "Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    //文字渲染函数（wstring版）
    bool drawText(Buffer& buffer, const std::wstring& text, float x, float y, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextInRect(Buffer& buffer, const std::wstring& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextFitRect(Buffer& buffer, const std::wstring& text, float rectX, float rectY, float rectWidth, float rectHeight, const Color& color = Color(255, 255, 255, 255), int preferredFontSize = 12, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    void drawTextCentered(Buffer& buffer, const std::wstring& text, float centerX, float centerY, const Color& color = Color(255, 255, 255, 255), int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", const FontStyle& style = FontStyle::Regular);
    // ==================== 图形样式 ====================
    struct Style {
        Color fillColor_;
        Color strokeColor_;
        float strokeWidth_;
        float opacity_;
        float radius_;
        bool drawArc_;
        bool drawRadialEdges_;

        Style(Color fill = 0, Color stroke = 0, float width = 1.0f, float radius = 0.0f, float opacity = 1.0f, bool drawArc = true, bool drawRadialEdges = true);

        Style& fill(Color v);
        Style& stroke(Color v);
        Style& width(float v);
        Style& opacity(float v);
        Style& radius(float v);
        Style& drawArc(bool v);
        Style& drawRadialEdges(bool v);
        Style& fill(uint32_t v);
        Style& stroke(uint32_t v);
    };
    struct TagBase;
    struct StyleBuilder {
        std::vector<std::unique_ptr<TagBase>> tags;
        StyleBuilder();
        StyleBuilder(const StyleBuilder& other);
        StyleBuilder& operator=(const StyleBuilder& other);
        operator Style() const;
    };

    struct TagBase {
        virtual ~TagBase() = default;
        virtual void applyTo(Style& style) const = 0;
        virtual std::unique_ptr<TagBase> clone() const = 0;
    };

    struct FillTag : public TagBase {
        uint32_t argb;
        FillTag(uint32_t val) : argb(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    struct StrokeTag : public TagBase {
        uint32_t argb;
        StrokeTag(uint32_t val) : argb(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    struct WidthTag : public TagBase {
        float value;
        WidthTag(float val) : value(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    struct RadiusTag : public TagBase {
        float value;
        RadiusTag(float val) : value(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    struct OpacityTag : public TagBase {
        float value;
        OpacityTag(float val) : value(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    struct DrawArcTag : public TagBase {
        bool value;
        DrawArcTag(bool val) : value(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    struct DrawRadialEdgesTag : public TagBase {
        bool value;
        DrawRadialEdgesTag(bool val) : value(val) {}
        void applyTo(Style& style) const override;
        std::unique_ptr<TagBase> clone() const override;
        operator StyleBuilder() const;
    };

    // 字面量开关宏
#ifndef PA2D_DISABLE_LITERALS
    namespace detail {
        uint32_t parseColorString(const char* str, size_t len);
    }
    // 数字字面量操作符
    inline FillTag operator"" _fill(unsigned long long hex) { return FillTag(static_cast<uint32_t>(hex)); }
    inline StrokeTag operator"" _stroke(unsigned long long hex) { return StrokeTag(static_cast<uint32_t>(hex)); }
    inline WidthTag operator"" _w(long double w) { return WidthTag(static_cast<float>(w)); }
    inline WidthTag operator"" _w(unsigned long long w) { return WidthTag(static_cast<float>(w)); }
    inline RadiusTag operator"" _r(long double r) { return RadiusTag(static_cast<float>(r)); }
    inline RadiusTag operator"" _r(unsigned long long r) { return RadiusTag(static_cast<float>(r)); }
    inline OpacityTag operator"" _o(long double o) { return OpacityTag(static_cast<float>(o)); }

    // 字符串字面量操作符
    inline FillTag operator"" _fill(const char* str, size_t len) { return FillTag(detail::parseColorString(str, len)); }
    inline StrokeTag operator"" _stroke(const char* str, size_t len) { return StrokeTag(detail::parseColorString(str, len)); }
#endif // PA2D_DISABLE_LITERALS

    // 常量定义
    extern const DrawArcTag draw_arc;
    extern const DrawArcTag no_arc;
    extern const DrawRadialEdgesTag draw_edges;
    extern const DrawRadialEdgesTag no_edges;

    StyleBuilder operator+(const StyleBuilder& builder, const TagBase& newTag);
    // ==================== 渲染系统 ====================
    class Canvas {
        Buffer buffer;
    public:
        // 构造函数
        Canvas();
        Canvas(int width, int height, Color background = 0xFFFFFFFF);
        Canvas(const Buffer& buf);
        Canvas(Buffer&& buf);
        Canvas(const Canvas& other);
        Canvas(Canvas&& other) noexcept;
        Canvas(const char* filePath);
        Canvas(int resourceID);

        // 基础属性访问
        int width() const;
        int height() const;
        bool isValid() const;
        const Buffer& getBuffer() const;
        Buffer& getBuffer();

        // 像素访问
        Color& at(int x, int y);
        const Color& at(int x, int y) const;

        // 图像操作
        bool loadImage(const char* filePath);
        bool loadImage(int resourceID);
        Canvas& clear(Color color = 0xFFFFFFFF);
        Canvas& crop(int x, int y, int width, int height);
        Canvas& resize(int newWidth, int newHeight, uint32_t clearColor = 0xFFFFFFFF);

        // 混合操作
        Canvas& alphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& addBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& multiplyBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& screenBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& overlayBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& destAlphaBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);
        Canvas& copyBlend(const Canvas& src, int dstX = 0, int dstY = 0, int alpha = 255);

        // 变换操作
        Canvas& draw(const Canvas& other, int x = 0, int y = 0, int alpha = 255);
        Canvas& drawRotated(const Canvas& src, float centerX, float centerY, float rotation = 0.0f);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scaleX, float scaleY);
        Canvas& drawScaled(const Canvas& src, float centerX, float centerY, float scale = 1.0f);
        Canvas& drawScaledRotated(const Canvas& src, float centerX, float centerY, float scale = 1.0f, float rotation = 0.0f);

        // 创建变换后的副本
        Canvas createCropped(int x, int y, int width, int height) const;
        Canvas createScaled(float scaleX, float scaleY) const;
        Canvas createRotated(float rotation) const;
        Canvas createScaledRotated(float scale = 1.0f, float rotation = 0.0f) const;

        // 基础绘制方法
        Canvas& rect(float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& rect(float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& roundRect(float x, float y, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& roundRect(float centerX, float centerY, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float cornerRadius = 0.0f, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& circle(float centerX, float centerY, float radius, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& ellipse(float cx, float cy, float width, float height, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& ellipse(float cx, float cy, float width, float height, float angle, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& triangle(float ax, float ay, float bx, float by, float cx, float cy, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);
        Canvas& sector(float cx, float cy, float radius, float startAngleDeg, float endAngleDeg, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f, bool drawArc = true, bool drawRadialEdges = true);
        Canvas& line(float x0, float y0, float x1, float y1, const Color& color, float lineWidth = 1.0f);
        Canvas& polyline(const std::vector<Point>& points, const Color& color, float lineWidth = 1.0f, bool closed = false);
        Canvas& polygon(const std::vector<Point>& vertices, const Color& fillColor = 0, const Color& strokeColor = 0, float strokeWidth = 1.0f, float opacity = 1.0f);

        // 智能绘制函数
        Canvas& draw(const Line& line, const Style& style);
        Canvas& draw(const Ray& ray, const Style& style);
        Canvas& draw(const Triangle& triangle, const Style& style);
        Canvas& draw(const Rect& rect, const Style& style);
        Canvas& draw(const Circle& circle, const Style& style);
        Canvas& draw(const Elliptic& ellipse, const Style& style);
        Canvas& draw(const Sector& sector, const Style& style);
        Canvas& draw(const Points& points, const Style& style);
        Canvas& draw(const Polygon& polygon, const Style& style);

        // 批量绘制
        template<typename GeometryType>
        Canvas& drawBatch(const std::vector<GeometryType>& geometries, const Style& style) {
            for (const auto& geometry : geometries)draw(geometry, style);
            return *this;
        }

        template<typename GeometryType>
        Canvas& drawBatch(const std::vector<GeometryType>& geometries, const std::vector<Style>& styles) {
            for (size_t i = 0; i < geometries.size(); ++i) {
                const Style& style = (i < styles.size()) ? styles[i] :
                    (!styles.empty()) ? styles.back() : Style();
                draw(geometries[i], style);
            }
            return *this;
        }

        // 文本绘制方法
        Canvas& text(const std::wstring& text, int x, int y, const Color& color = 0xFF000000, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::wstring& text, int centerX, int centerY, const Color& color = 0xFF000000, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::wstring& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int fontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::wstring& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int preferredFontSize = 16, const std::wstring& fontName = L"Microsoft YaHei", FontStyle style = FontStyle::Regular);

        Canvas& text(const std::string& text, int x, int y, const Color& color = 0xFF000000, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textCentered(const std::string& text, int centerX, int centerY, const Color& color = 0xFF000000, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textInRect(const std::string& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int fontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
        Canvas& textFitRect(const std::string& text, int rectX, int rectY, int rectWidth, int rectHeight, const Color& color = 0xFF000000, int preferredFontSize = 16, const std::string& fontName = "Microsoft YaHei", FontStyle style = FontStyle::Regular);
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

    class Window {
    public:
        // 构造/析构
        Window(int width, int height, const char* title);
        ~Window();

        // 禁止拷贝
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // 事件回调
        using KeyCallback = std::function<void(const KeyEvent&)>;
        using MouseCallback = std::function<void(const MouseEvent&)>;
        using ResizeCallback = std::function<void(int, int)>;
        using CharCallback = std::function<void(wchar_t)>;
        using FocusCallback = std::function<void(bool)>;
        using CloseCallback = std::function<bool()>;
        using MenuCallback = std::function<void(int)>;
        using FileListCallback = std::function<void(const std::vector<std::string>&)>;

        // 链式调用的回调设置方法
        Window& onKey(KeyCallback cb);
        Window& onMouse(MouseCallback cb);
        Window& onResize(ResizeCallback cb);
        Window& onChar(CharCallback cb);
        Window& onFocus(FocusCallback cb);
        Window& onClose(CloseCallback cb);
        Window& onMenu(MenuCallback cb);
        Window& onFileDrop(FileListCallback cb);
        Window& onClipboardFiles(FileListCallback cb);

        Window& disableClipboardFiles();

        // 窗口状态
        bool isOpen() const { return !shouldClose_; }
        Window& close();

        bool isMaximized() const { return hwnd_ && IsZoomed(hwnd_); }
        bool isMinimized() const { return hwnd_ && IsIconic(hwnd_); }
        bool isVisible() const { return hwnd_ && IsWindowVisible(hwnd_); }
        bool isFullscreen() const { return isFullscreen_; }

        // 窗口大小限制
        Window& setMinSize(int minWidth, int minHeight);
        Window& setMaxSize(int maxWidth, int maxHeight);

        // 窗口样式控制
        Window& setResizable(bool resizable);
        Window& setAlwaysOnTop(bool onTop);
        Window& setBorderless(bool borderless);
        Window& setFullscreen(bool fullscreen);

        // 控制右上角按钮
        Window& setMinimizeButton(bool show);
        Window& setMaximizeButton(bool show);
        Window& setCloseButton(bool show);

        // 鼠标状态查询
        std::pair<int, int> getMousePosition() const;
        bool isMouseInWindow() const;
        static std::pair<int, int> getGlobalMousePosition();
        bool isMouseButtonPressed(int button) const;

        // 鼠标捕获与光标控制
        Window& setMouseCapture(bool capture);
        Window& setCursorVisibility(bool visible);
        Window& setCursorPosition(int x, int y);

        // 按键状态查询
        bool isKeyPressed(int vkCode) const;
        bool isShiftPressed() const;
        bool isCtrlPressed() const;
        bool isAltPressed() const;

        // 剪贴板
        bool setClipboardText(const std::string& text);
        std::string getClipboardText();
        bool setClipboardText(const std::wstring& text);
        std::wstring getClipboardTextW();
        bool hasClipboardText() const;

        // 文件拖放方法
        Window& enableFileDrop(bool enable = true);

        // 文件剪贴板支持
        std::vector<std::string> getClipboardFiles();
        bool hasClipboardFiles() const;

        // 窗口操作 - 链式调用
        Window& show();
        Window& hide();
        Window& maximize();
        Window& minimize();
        Window& restore();
        Window& setVisible(bool visible);
        Window& focus();
        Window& flash(bool flashTitleBar = true);

        // 窗口大小和位置 - 链式调用
        Window& setPosition(int x, int y);
        Window& setClientSize(int width, int height);
        Window& setWindowSize(int width, int height);

        void getPosition(int& x, int& y) const;
        void getClientSize(int& width, int& height) const;
        void getWindowSize(int& width, int& height) const;

        // 标题设置 - 链式调用
        Window& setTitle(const char* title);
        Window& setTitle(const wchar_t* title);
        std::string getTitle() const;

        // 光标设置 - 链式调用
        Window& setCursor(HCURSOR cursor);
        Window& setCursorDefault();
        Window& setCursorWait();
        Window& setCursorCross();
        Window& setCursorHand();
        Window& setCursorText();

        // 图标设置 - 链式调用
        Window& setIcon(HICON icon);
        Window& setIconFromResource(int resourceId);

        // 菜单功能 - 链式调用
        Window& setMenu(HMENU menu);
        HMENU createMenu();
        HMENU createPopupMenu();
        Window& appendMenuItem(HMENU menu, const char* text, int id, bool enabled = true);
        Window& appendMenuSeparator(HMENU menu);
        Window& appendMenuPopup(HMENU menu, const char* text, HMENU popupMenu);
        Window& destroyMenu(HMENU menu);

        // 渲染功能
        void render(const Buffer& buffer, int destX = 0, int destY = 0,
            int srcX = 0, int srcY = 0, int width = -1, int height = -1,
            bool clearBackground = true, COLORREF bgColor = 0);
        void renderCentered(const Buffer& buffer, bool clearBackground = true, COLORREF bgColor = 0);
        void render(const Canvas& canvas, int destX = 0, int destY = 0,
            int srcX = 0, int srcY = 0, int width = -1, int height = -1,
            bool clearBackground = true, COLORREF bgColor = 0);
        void renderCentered(const Canvas& canvas, bool clearBackground = true, COLORREF bgColor = 0);

        // 系统信息（静态方法）
        static std::pair<int, int> getScreenSize();
        static std::pair<int, int> getWorkAreaSize();
        static double getDpiScale();

        // 公开成员变量（保持简单访问）
        HWND hwnd_ = nullptr;
        int width_ = 0;
        int height_ = 0;
        bool shouldClose_ = false;

    private:
        // 线程控制
        std::thread messageThread_;
        std::atomic<bool> running_{ false };
        DWORD threadId_ = 0;
        std::promise<bool> initPromise_;

        // 窗口样式
        // 无边框状态
        LONG borderlessOriginalStyle_ = 0;
        LONG borderlessOriginalExStyle_ = 0;
        int borderlessOriginalClientWidth_ = 0;
        int borderlessOriginalClientHeight_ = 0;
        bool borderlessStateSaved_ = false;
        bool isBorderless_ = false;

        // 全屏状态
        LONG fullscreenOriginalStyle_ = 0;
        LONG fullscreenOriginalExStyle_ = 0;
        RECT fullscreenOriginalRect_ = { 0 };
        bool fullscreenStateSaved_ = false;
        bool isFullscreen_ = false;

        // 窗口大小限制
        int minWidth_ = 0;
        int minHeight_ = 0;
        int maxWidth_ = 0;
        int maxHeight_ = 0;

        // 鼠标跟踪状态
        std::atomic<bool> trackingMouse_{ false };

        // 渲染相关成员
        struct DirectBuffer {
            BITMAPINFO bmi = {};
        } directBuffer_;

        // 渲染优化相关
        int lastClientWidth_ = 0;
        int lastClientHeight_ = 0;
        int lastBufferWidth_ = 0;
        int lastBufferHeight_ = 0;
        bool sizeChanged_ = true;

        // 回调函数
        KeyCallback keyCb_;
        MouseCallback mouseCb_;
        ResizeCallback resizeCb_;
        CharCallback charCb_;
        FocusCallback focusCb_;
        CloseCallback closeCb_;
        MenuCallback menuCb_;
        FileListCallback dropCb_;
        FileListCallback clipboardFilesCb_; // 文件剪贴板回调

        HWND nextClipboardViewer_ = nullptr;  // 剪贴板查看器链

        HDC persistentDC_ = nullptr;
    };
}

#ifdef _DEBUG
#pragma comment(lib, "pa2dd.lib")
#else
#pragma comment(lib, "pa2d.lib")
#endif