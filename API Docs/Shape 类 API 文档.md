## 🚀 模块概览：Shape & Style 模块接口

此文档详细介绍了 pa2d 库中的几何图形系统，包含基础几何结构、图形类继承体系、变换操作和样式系统。该模块提供面向对象的几何图形表示和操作能力。

* 函数/类名 <code><span style="color:#8e44ad">(Shape, Point, Style): #8e44ad (紫色)</span></code>
* 类型/关键字 <code><span style="color:#2e86c1">(const, float, virtual): #2e86c1 (蓝色)</span></code>
* 参数名/变量名: <code><span style="color:#e74c3c">#e74c3c (红色)</span></code>

---

## 📑 目录

- [📍 基础几何结构](#-基础几何结构)
- [🎨 样式系统](#-样式系统)
- [📐 几何图形基类](#-几何图形基类)
- [🔹 点集与多段线](#-点集与多段线)
- [🟦 矩形与三角形](#-矩形与三角形)
- [⭕ 圆形与椭圆](#-圆形与椭圆)
- [📐 射线与扇形](#-射线与扇形)
- [🛤️ 路径构建器](#️-路径构建器)

---

## 📍 基础几何结构

### Point 结构
二维浮点坐标点，支持各种算术和几何变换操作。

| 操作类型 | 方法签名 | 功能说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Point</span>()</code><br><code><span style="color:#8e44ad">Point</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 默认/指定坐标构造 |
| **算术运算** | <code><span style="color:#8e44ad">operator+</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>&)</code><br><code><span style="color:#8e44ad">operator-</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>&)</code><br><code><span style="color:#8e44ad">operator*</span>(<span style="color:#2e86c1">float</span>)</code><br><code><span style="color:#8e44ad">operator/</span>(<span style="color:#2e86c1">float</span>)</code> | 点与点/标量运算 |
| **复合赋值** | <code><span style="color:#8e44ad">operator+=</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>&)</code><br><code><span style="color:#8e44ad">operator*=</span>(<span style="color:#2e86c1">float</span>)</code> 等 | 复合算术运算 |
| **几何变换** | <code><span style="color:#8e44ad">translate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dx</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dy</span>)</code><br><code><span style="color:#8e44ad">scale</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factor</span>)</code><br><code><span style="color:#8e44ad">rotate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>)</code> | 平移/缩放/旋转变换 |

### BoundingBox 结构
几何图形的边界框表示。

| 方法签名 | 返回值 | 功能说明 |
| :--- | :--- | :--- |
| <code><span style="color:#8e44ad">BoundingBox</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">height</span>)</code> | - | 构造边界框 |
| <code><span style="color:#8e44ad">left</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">right</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">top</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">bottom</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">float</span></code> | 获取边界位置 |
| <code><span style="color:#8e44ad">center</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#8e44ad">Point</span></code> | 获取中心点 |
| <code><span style="color:#8e44ad">contains</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">px</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">py</span>) <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 判断点是否在框内 |

---

## 🎨 样式系统

### Style 结构
几何图形的绘制样式配置。

| 属性 | 类型 | 设置方法 | 默认值 | 说明 |
| :--- | :--- | :--- | :--- | :--- |
| **fill_** | <code><span style="color:#8e44ad">Color</span></code> | <code><span style="color:#8e44ad">fill</span>(<span style="color:#8e44ad">Color</span>)</code> | <code>0</code> | 填充颜色 |
| **stroke_** | <code><span style="color:#8e44ad">Color</span></code> | <code><span style="color:#8e44ad">stroke</span>(<span style="color:#8e44ad">Color</span>)</code> | <code>0</code> | 描边颜色 |
| **width_** | <code><span style="color:#2e86c1">float</span></code> | <code><span style="color:#8e44ad">width</span>(<span style="color:#2e86c1">float</span>)</code> | <code>1.0f</code> | 线宽 |
| **radius_** | <code><span style="color:#2e86c1">float</span></code> | <code><span style="color:#8e44ad">radius</span>(<span style="color:#2e86c1">float</span>)</code> | <code>0.0f</code> | 圆角半径 |
| **opacity_** | <code><span style="color:#2e86c1">float</span></code> | <code><span style="color:#8e44ad">opacity</span>(<span style="color:#2e86c1">float</span>)</code> | <code>1.0f</code> | 不透明度 |
| **drawArc_** | <code><span style="color:#2e86c1">bool</span></code> | <code><span style="color:#8e44ad">drawArc</span>(<span style="color:#2e86c1">bool</span>)</code> | <code>true</code> | 是否绘制圆弧 |
| **drawRadialEdges_** | <code><span style="color:#2e86c1">bool</span></code> | <code><span style="color:#8e44ad">drawRadialEdges</span>(<span style="color:#2e86c1">bool</span>)</code> | <code>true</code> | 是否绘制径向边 |

**构造方式：**
```cpp
// 完整构造
Style style(fillColor, strokeColor, width, radius, opacity, drawArc, drawRadialEdges);

// 流式配置
Style style = Style().fill(0xFFFF0000).stroke(0xFF000000).width(2.0f);
```

提供直观的字面量语法来创建样式配置。

| 字面量 | 类型 | 示例 | 说明 |
| :--- | :--- | :--- | :--- |
| **颜色字面量** | <code><span style="color:#8e44ad">FillTag</span></code> <br> <code><span style="color:#8e44ad">StrokeTag</span></code> | <code>0xFFFF0000_fill</code><br><code>0xFF00FF00_stroke</code> | 十六进制或颜色名 |
| **线宽字面量** | <code><span style="color:#8e44ad">WidthTag</span></code> | <code>2.0_w</code><br><code>5_w</code> | 浮点或整数线宽 |
| **半径字面量** | <code><span style="color:#8e44ad">RadiusTag</span></code> | <code>10.5_r</code><br><code>8_r</code> | 圆角半径 |
| **透明度字面量** | <code><span style="color:#8e44ad">OpacityTag</span></code> | <code>0.5_o</code><br><code>0.75_o</code> | 不透明度(0.0-1.0) |
| **布尔标志** | <code><span style="color:#8e44ad">DrawArcTag</span></code> | <code>draw_arc</code><br><code>no_arc</code> | 圆弧绘制控制 |
| **布尔标志** | <code><span style="color:#8e44ad">DrawRadialEdgesTag</span></code> | <code>draw_edges</code><br><code>no_edges</code> | 径向边绘制控制 |

**使用示例：**
```cpp
// 基本字面量使用
auto fillStyle = 0xFF0000FF_fill + 2.0_w;

// 复杂样式组合
Style complexStyle = 0xFFFF0000_fill + 0xFF000000_stroke + 3.0_w + 10.0_r + 0.8_o;

// 扇形专用样式
Style sectorStyle = 0xFF8888FF_fill + no_arc + draw_edges;

// 圆角矩形样式  
Style roundRectStyle = 0xFFFFFFFF_fill + 0xFF333333_stroke + 2.0_w + 15.0_r;
```
---
## 📐 几何图形基类

### Shape 抽象基类
所有几何图形的基类，定义统一接口。

**几何类型枚举：**
```cpp
enum class GeometryType {
    POINTS, LINE, POLYGON, RECT, TRIANGLE, 
    CIRCLE, ELLIPTIC, SECTOR, RAY
};
```
| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **类型查询** | <code><span style="color:#8e44ad">getType</span>() <span style="color:#2e86c1">const</span></code> | 获取几何类型枚举值 |
| **平移变换** | <code><span style="color:#8e44ad">translate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dx</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dy</span>)</code> | 相对平移变换 |
| | <code><span style="color:#8e44ad">translate</span>(<span style="color:#8e44ad">Point</span> <span style="color:#e74c3c">delta</span>)</code> | 使用点向量平移 |
| **缩放变换** | <code><span style="color:#8e44ad">scale</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factor</span>)</code> | 等比例缩放 |
| | <code><span style="color:#8e44ad">scale</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factorX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factorY</span>)</code> | 非均匀缩放 |
| | <code><span style="color:#8e44ad">scaleOnSelf</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factor</span>)</code> | 以自身为中心缩放 |
| | <code><span style="color:#8e44ad">scaleOnSelf</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factorX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factorY</span>)</code> | 以自身为中心非均匀缩放 |
| **旋转变换** | <code><span style="color:#8e44ad">rotate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>)</code> | 绕指定点旋转 |
| | <code><span style="color:#8e44ad">rotate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>, <span style="color:#8e44ad">Point</span> <span style="color:#e74c3c">center</span>)</code> | 绕指定点旋转 |
| | <code><span style="color:#8e44ad">rotate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>)</code> | 绕默认中心旋转 |
| | <code><span style="color:#8e44ad">rotateOnSelf</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>)</code> | 以自身为中心旋转 |
| **几何查询** | <code><span style="color:#8e44ad">contains</span>(<span style="color:#8e44ad">Point</span> <span style="color:#e74c3c">point</span>) <span style="color:#2e86c1">const</span></code> | 判断点是否在图形内 |
| | <code><span style="color:#8e44ad">getBoundingBox</span>() <span style="color:#2e86c1">const</span></code> | 获取边界框 |
| | <code><span style="color:#8e44ad">getCenter</span>() <span style="color:#2e86c1">const</span></code> | 获取中心点 |

---

## 🔹 点集与多段线

### Points 类
点集合，继承自 `std::vector<Point>` 和 `Shape`。

| 构造方式 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **默认构造** | <code><span style="color:#8e44ad">Points</span>()</code> | 创建空点集 |
| **数量构造** | <code><span style="color:#8e44ad">Points</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">size</span>)</code> | 创建指定数量点集 |
| **向量构造** | <code><span style="color:#8e44ad">Points</span>(<span style="color:#2e86c1">const</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;& <span style="color:#e74c3c">points</span>)</code> | 从向量构造 |
| **移动构造** | <code><span style="color:#8e44ad">Points</span>(std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;&& <span style="color:#e74c3c">points</span>)</code> | 移动构造 |

**赋值操作：**
- <code><span style="color:#8e44ad">operator=</span>(<span style="color:#2e86c1">const</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;&)</code>
- <code><span style="color:#8e44ad">operator=</span>(std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;&&)</code>

### Line 类
直线段，由起点和终点定义。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Line</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Line</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x0</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y0</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x1</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y1</span>)</code> | 坐标构造 |
| | <code><span style="color:#8e44ad">Line</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">start</span>, <span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">end</span>)</code> | 点构造 |
| **端点设置** | <code><span style="color:#8e44ad">start</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置起点坐标 |
| | <code><span style="color:#8e44ad">start</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">start</span>)</code> | 设置起点 |
| | <code><span style="color:#8e44ad">end</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置终点坐标 |
| | <code><span style="color:#8e44ad">end</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">end</span>)</code> | 设置终点 |
| **端点访问** | <code><span style="color:#8e44ad">start</span>()</code><br><code><span style="color:#8e44ad">start</span>() <span style="color:#2e86c1">const</span></code> | 获取起点(可变/常量) |
| | <code><span style="color:#8e44ad">end</span>()</code><br><code><span style="color:#8e44ad">end</span>() <span style="color:#2e86c1">const</span></code> | 获取终点(可变/常量) |
| **类型转换** | <code><span style="color:#2e86c1">operator</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;()</code> | 转换为点向量 |

### Polygon 类
多边形，支持奇偶填充规则。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Polygon</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Polygon</span>(<span style="color:#2e86c1">const</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;& <span style="color:#e74c3c">points</span>)</code> | 从点集构造 |
| | <code><span style="color:#8e44ad">Polygon</span>(std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;&& <span style="color:#e74c3c">points</span>)</code> | 移动构造 |
| **点集访问** | <code><span style="color:#8e44ad">getPoints</span>()</code><br><code><span style="color:#8e44ad">getPoints</span>() <span style="color:#2e86c1">const</span></code> | 获取顶点集合 |
| **赋值操作** | <code><span style="color:#8e44ad">operator=</span>(<span style="color:#2e86c1">const</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;&)</code> | 拷贝赋值 |
| | <code><span style="color:#8e44ad">operator=</span>(std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;&&)</code> | 移动赋值 |

---

## 🟦 矩形与三角形

### Rect 类
矩形，支持旋转和中心点操作。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Rect</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Rect</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">height</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">rotation</span>)</code> | 中心点构造 |
| | <code><span style="color:#8e44ad">Rect</span>(<span style="color:#2e86c1">const</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;& <span style="color:#e74c3c">points</span>)</code> | 从顶点构造 |
| **属性设置** | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">center</span>)</code> | 设置中心点 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心坐标 |
| | <code><span style="color:#8e44ad">width</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">width</span>)</code> | 设置宽度 |
| | <code><span style="color:#8e44ad">height</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">height</span>)</code> | 设置高度 |
| | <code><span style="color:#8e44ad">rotation</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">rotation</span>)</code> | 设置旋转角度 |
| **属性访问** | <code><span style="color:#8e44ad">center</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">center</span>()</code> | 获取中心点 |
| | <code><span style="color:#8e44ad">width</span>() <span style="color:#2e86c1">const</span></code> | 获取宽度 |
| | <code><span style="color:#8e44ad">height</span>() <span style="color:#2e86c1">const</span></code> | 获取高度 |
| | <code><span style="color:#8e44ad">rotation</span>() <span style="color:#2e86c1">const</span></code> | 获取旋转角度 |
| **迭代器** | <code><span style="color:#8e44ad">begin</span>()</code><br><code><span style="color:#8e44ad">end</span>()</code> | 顶点迭代器 |
| | <code><span style="color:#8e44ad">begin</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">end</span>() <span style="color:#2e86c1">const</span></code> | 常量迭代器 |
| **顶点访问** | <code><span style="color:#8e44ad">operator[]</span>(<span style="color:#2e86c1">size_t</span> <span style="color:#e74c3c">index</span>)</code> | 访问顶点 |

### Triangle 类
三角形，由三个顶点定义。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Triangle</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Triangle</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">p0</span>, <span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">p1</span>, <span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">p2</span>)</code> | 点构造 |
| | <code><span style="color:#8e44ad">Triangle</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">px0</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">py0</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">px1</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">py1</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">px2</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">py2</span>)</code> | 坐标构造 |
| | <code><span style="color:#8e44ad">Triangle</span>(<span style="color:#2e86c1">const</span> std::vector&lt;<span style="color:#8e44ad">Point</span>&gt;& <span style="color:#e74c3c">points</span>)</code> | 向量构造 |
| **迭代器** | <code><span style="color:#8e44ad">begin</span>()</code><br><code><span style="color:#8e44ad">end</span>()</code> | 顶点迭代器 |
| | <code><span style="color:#8e44ad">begin</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">end</span>() <span style="color:#2e86c1">const</span></code> | 常量迭代器 |
| **顶点访问** | <code><span style="color:#8e44ad">operator[]</span>(<span style="color:#2e86c1">size_t</span> <span style="color:#e74c3c">index</span>)</code> | 访问顶点 |

---

## ⭕ 圆形与椭圆

### Circle 类
圆形，由中心和半径定义。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Circle</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Circle</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">radius</span>)</code> | 坐标构造 |
| | <code><span style="color:#8e44ad">Circle</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">center</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">radius</span>)</code> | 点构造 |
| **属性设置** | <code><span style="color:#8e44ad">x</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>)</code> | 设置中心X坐标 |
| | <code><span style="color:#8e44ad">y</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心Y坐标 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">center</span>)</code> | 设置中心点 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心坐标 |
| | <code><span style="color:#8e44ad">radius</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">radius</span>)</code> | 设置半径 |
| **属性访问** | <code><span style="color:#8e44ad">x</span>() <span style="color:#2e86c1">const</span></code> | 获取中心X坐标 |
| | <code><span style="color:#8e44ad">y</span>() <span style="color:#2e86c1">const</span></code> | 获取中心Y坐标 |
| | <code><span style="color:#8e44ad">center</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">center</span>()</code> | 获取中心点 |
| | <code><span style="color:#8e44ad">radius</span>() <span style="color:#2e86c1">const</span></code> | 获取半径 |
| **类型转换** | <code><span style="color:#2e86c1">operator</span> <span style="color:#8e44ad">Point</span>()</code> | 转换为中心点 |

### Elliptic 类
椭圆，支持旋转。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Elliptic</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Elliptic</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">height</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">rotation</span>)</code> | 完整构造 |
| **属性设置** | <code><span style="color:#8e44ad">x</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>)</code> | 设置中心X坐标 |
| | <code><span style="color:#8e44ad">y</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心Y坐标 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">center</span>)</code> | 设置中心点 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心坐标 |
| | <code><span style="color:#8e44ad">width</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">width</span>)</code> | 设置宽度 |
| | <code><span style="color:#8e44ad">height</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">height</span>)</code> | 设置高度 |
| | <code><span style="color:#8e44ad">rotation</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">rotation</span>)</code> | 设置旋转角度 |
| **属性访问** | <code><span style="color:#8e44ad">x</span>() <span style="color:#2e86c1">const</span></code> | 获取中心X坐标 |
| | <code><span style="color:#8e44ad">y</span>() <span style="color:#2e86c1">const</span></code> | 获取中心Y坐标 |
| | <code><span style="color:#8e44ad">center</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">center</span>()</code> | 获取中心点 |
| | <code><span style="color:#8e44ad">width</span>() <span style="color:#2e86c1">const</span></code> | 获取宽度 |
| | <code><span style="color:#8e44ad">height</span>() <span style="color:#2e86c1">const</span></code> | 获取高度 |
| | <code><span style="color:#8e44ad">rotation</span>() <span style="color:#2e86c1">const</span></code> | 获取旋转角度 |

---

## 📐 射线与扇形

### Ray 类
射线，由起点、长度和角度定义。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Ray</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Ray</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x1</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y1</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x2</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y2</span>)</code> | 两点构造 |
| | <code><span style="color:#8e44ad">Ray</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">start</span>, <span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">end</span>)</code> | 点构造 |
| | <code><span style="color:#8e44ad">Ray</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">start</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">length</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angle</span>)</code> | 极坐标构造 |
| **端点设置** | <code><span style="color:#8e44ad">start</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置起点坐标 |
| | <code><span style="color:#8e44ad">start</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">start</span>)</code> | 设置起点 |
| | <code><span style="color:#8e44ad">end</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置终点坐标 |
| | <code><span style="color:#8e44ad">end</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">end</span>)</code> | 设置终点 |
| **端点访问** | <code><span style="color:#8e44ad">start</span>()</code><br><code><span style="color:#8e44ad">start</span>() <span style="color:#2e86c1">const</span></code> | 获取起点 |
| | <code><span style="color:#8e44ad">end</span>()</code><br><code><span style="color:#8e44ad">end</span>() <span style="color:#2e86c1">const</span></code> | 获取终点 |
| **极坐标操作** | <code><span style="color:#8e44ad">angle</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angle</span>)</code> | 设置角度 |
| | <code><span style="color:#8e44ad">length</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">length</span>)</code> | 设置长度 |
| | <code><span style="color:#8e44ad">length</span>() <span style="color:#2e86c1">const</span></code> | 获取长度 |
| | <code><span style="color:#8e44ad">angle</span>() <span style="color:#2e86c1">const</span></code> | 获取角度 |
| **动态操作** | <code><span style="color:#8e44ad">toEnd</span>()</code> | 更新终点位置 |
| | <code><span style="color:#8e44ad">stretch</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factor</span>)</code> | 拉伸长度 |
| | <code><span style="color:#8e44ad">spin</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">degrees</span>)</code> | 旋转角度 |

### Sector 类
扇形，由中心、半径和角度范围定义。

| 方法类别 | 方法签名 | 说明 |
| :-------- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Sector</span>()</code> | 默认构造 |
| | <code><span style="color:#8e44ad">Sector</span>(<span style="color:#8e44ad">Point</span> <span style="color:#e74c3c">center</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">radius</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">startAngle</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">endAngle</span>)</code> | 点构造 |
| | <code><span style="color:#8e44ad">Sector</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">radius</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">startAngle</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">endAngle</span>)</code> | 坐标构造 |
| **属性设置** | <code><span style="color:#8e44ad">x</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>)</code> | 设置中心X坐标 |
| | <code><span style="color:#8e44ad">y</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心Y坐标 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">center</span>)</code> | 设置中心点 |
| | <code><span style="color:#8e44ad">center</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 设置中心坐标 |
| | <code><span style="color:#8e44ad">radius</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">radius</span>)</code> | 设置半径 |
| | <code><span style="color:#8e44ad">startAngle</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">startAngle</span>)</code> | 设置起始角度 |
| | <code><span style="color:#8e44ad">endAngle</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">endAngle</span>)</code> | 设置结束角度 |
| **属性访问** | <code><span style="color:#8e44ad">x</span>() <span style="color:#2e86c1">const</span></code> | 获取中心X坐标 |
| | <code><span style="color:#8e44ad">y</span>() <span style="color:#2e86c1">const</span></code> | 获取中心Y坐标 |
| | <code><span style="color:#8e44ad">center</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">center</span>()</code> | 获取中心点 |
| | <code><span style="color:#8e44ad">radius</span>() <span style="color:#2e86c1">const</span></code> | 获取半径 |
| | <code><span style="color:#8e44ad">startAngle</span>() <span style="color:#2e86c1">const</span></code> | 获取起始角度 |
| | <code><span style="color:#8e44ad">endAngle</span>() <span style="color:#2e86c1">const</span></code> | 获取结束角度 |

---

## 🛤️ 路径构建器

### Path 类
路径构建工具，支持链式操作创建复杂路径。

**静态构造方法：**
- <code><span style="color:#8e44ad">Path::from</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> - 从坐标开始
- <code><span style="color:#8e44ad">Path::from</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Point</span>& <span style="color:#e74c3c">start</span>)</code> - 从点开始

**Builder 方法：**
| 方法 | 说明 |
| :--- | :--- |
| <code><span style="color:#8e44ad">move</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dx</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dy</span>)</code> | 相对移动 |
| <code><span style="color:#8e44ad">moveTo</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">y</span>)</code> | 绝对移动 |
| <code><span style="color:#8e44ad">translate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dx</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">dy</span>)</code> | 平移变换 |
| <code><span style="color:#8e44ad">scale</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factor</span>)</code> | 等比例缩放 |
| <code><span style="color:#8e44ad">scale</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factorX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">factorY</span>)</code> | 非均匀缩放 |
| <code><span style="color:#8e44ad">rotate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>)</code> | 绕原点旋转 |
| <code><span style="color:#8e44ad">rotate</span>(<span style="color:#2e86c1">float</span> <span style="color:#e74c3c">angleDegrees</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerX</span>, <span style="color:#2e86c1">float</span> <span style="color:#e74c3c">centerY</span>)</code> | 绕指定点旋转 |

**使用示例：**
```cpp
// 创建复杂路径
auto points = Path::from(0, 0)
    .moveTo(100, 100)
    .move(50, 0)
    .rotate(45)
    .move(0, 50);
    
// 转换为几何对象
Polygon polygon = Path::from(0, 0)
    .moveTo(100, 0)
    .moveTo(100, 100)
    .moveTo(0, 100);
```