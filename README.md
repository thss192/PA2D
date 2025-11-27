<a id= pa2d---modern-c-2d-graphics-programming-library></a>

# PA2D - Modern C++ 2D Graphics Programming Library

[English](#pa2d---modern-c-2d-graphics-programming-library) | [简体中文](#pa2d---轻量级-c-2d-图形库)

## 🎯 Project Overview

PA2D is a lightweight 2D graphics programming library designed for modern C++, providing developers with simple yet powerful graphics drawing solutions. It perfectly balances beginner-friendliness and professional development needs, making graphics programming more intuitive and efficient.

## 📦 Release Contents

Current version provides:
- **Header file** (`pa2d.h`) - Complete API interface
- **Pre-compiled libraries** - Debug and Release versions
- **Example code** - Practical examples for quick start

## ✨ Core Features

### 🏗️ Layered Architecture Design
- **Low-level**: High-performance rendering core with zero-cost abstraction
- **Mid-level**: Unified geometric transformation system
- **High-level**: Fluent chainable API for rapid development

### 🎨 Rich Graphics Support
- Basic shapes: Points, lines, rectangles, circles, ellipses, triangles, polygons
- Advanced shapes: Sectors, rays, path building
- Text rendering: Support for Chinese/English, multiple fonts and styles
- Image processing: Loading, transformation, blending, cropping

### 🖼️ Flexible Drawing System
- Multiple abstraction levels: From low-level bitmap operations to high-level OOP interfaces
- Unified styling system: Support for fill, stroke, opacity, etc.
- Geometric transformations: Unified interface for translation, rotation, scaling

### 🪟 Powerful Window Management
- Multi-window support
- Complete event system (keyboard, mouse, file drop, etc.)
- Thread-safe window message handling
- Custom menus and cursors

## 📁 Project Structure

```txt
PA2D/
├── pa2d.h # Main header file
├── pa2d.lib # Release version library
├── pa2dd.lib # Debug version library
├── examples/ # Example code
└── README.md
```


## Project Configuration

Download PA2D library files

Add the include/ directory to header search paths

Link the appropriate library files (pa2d.lib or pa2dd.lib)

Include the header in your code: `#include "pa2d.h"`

## Requirements

- Windows 7 or higher
- Visual Studio 2019 or higher
- C++14 or higher standard

## 🎮 Usage Examples

### Basic Drawing Example

```cpp
#include "pa2d.h"
using namespace pa2d;

int main() {
    Window window(600, 400, "PA2D Example");
    Canvas canvas(600, 400);
    
    window.show();
    
    // Draw graphics
    canvas.clear(White)
          .circle(200, 200, 50, None, Red, 3)
          .rect(100, 100, 200, 100, LightBlue, Blue, 2)
          .textCentered(L"Hello PA2D!", 300, 300, Black, 20);
    
    while (window.isOpen()) {
        window.render(canvas);
    }
    return 0;
}
```

### Multi-Window Application

```cpp
#include "pa2d.h"
using namespace pa2d;

int main() {
    Window w1(600, 400, "Window 1");
    Window w2(600, 400, "Window 2");
    Canvas canvas1(600, 400), canvas2(600, 400);
    
    // Draw content separately
    canvas1.clear(Black).circle(200, 200, 50, None, Red, 5);
    canvas2.clear(White).rect(100, 100, 200, 100, None, Blue, 5);
    
    w1.setPosition(100, 100).show();
    w2.setPosition(750, 100).show();
    
    while (w1.isOpen() && w2.isOpen()) {
        w1.render(canvas1);
        w2.render(canvas2);
        Sleep(16);
    }
    return 0;
}
```
## 🔧 API Design Philosophy
### Fluent Interface Design
```cpp
// All geometric objects share unified interface
circle.translate(10, 20).rotate(45).scale(2.0);
rect.translate(10, 20).rotate(45).scale(2.0);

// Chainable drawing calls
canvas.clear(Black)
     .rect(10, 10, 100, 50, LightBlue)
     .circle(50, 50, 30, Red)
     .text("Hello", 20, 20, White);
```
### Explicit Control Flow
```cpp
Window window(800, 600);     // Explicitly create window
window.show();               // Explicitly show window
Canvas canvas(800, 600);     // Explicitly create canvas
canvas.circle(...);          // Explicitly draw graphics
window.render(canvas);       // Explicitly execute rendering
```
## 📚 Example Code
The project includes multiple practical examples:

· basic_demo.cpp - Basic graphics drawing

· multi_window.cpp - Multi-window management

· clock_app.cpp - Real-time clock application

· file_drop.cpp - File drop functionality
## 🐛 Issue Reporting
If you encounter any issues, please report them by:

1. Creating a new issue in GitHub Issues

2. Describing detailed reproduction steps

3. Providing relevant code snippets and error messages

## License

This project uses a permissive open source license.

**Main Rights**:

· ✅ Free to use

· ✅ Use in commercial projects

**Only Requirement**:

📝 Retain original copyright notice when distributing

## 🙏 Acknowledgments

Thanks to all developers who contributed to this project, with special thanks to EasyX graphics library for inspiration.

<a id= pa2d---轻量级-c-2d-图形库></a>

# PA2D - 轻量级 C++ 图形库

[简体中文](#pa2d---轻量级-c-2d-图形库) | [English](#pa2d---modern-c-2d-graphics-programming-library) 

## 🎯 项目简介

PA2D 是一个专为现代 C++ 设计的轻量级 2D 图形编程库，旨在为开发者提供简单易用且功能强大的图形绘制解决方案。它完美平衡了初学者友好性和专业开发需求，让图形编程变得更加直观和高效。

## 📦 发布内容

当前版本提供：
- **头文件** (`pa2d.h`) - 完整的 API 接口
- **预编译库** - 支持调试和发布版本
- **示例代码** - 快速上手的实用示例

## ✨ 核心特性

### 🏗️ 分层架构设计
- **底层**: 高性能渲染核心，零成本抽象开销
- **中间层**: 统一的几何变换系统
- **应用层**: 流畅的链式 API，快速上手

### 🎨 丰富的图形支持
- 基础图形：点、线、矩形、圆形、椭圆、三角形、多边形
- 高级图形：扇形、射线、路径构建
- 文字渲染：支持中英文，多种字体和样式
- 图像处理：加载、变换、混合、裁剪

### 🖼️ 灵活的绘制系统
- 多重抽象层级：从底层位图操作到高级面向对象接口
- 统一的样式系统：支持填充、描边、透明度等
- 几何变换：平移、旋转、缩放等统一接口

### 🪟 强大的窗口管理
- 多窗口支持
- 完整的事件系统（键盘、鼠标、文件拖放等）
- 线程安全的窗口消息处理
- 自定义菜单和光标

## 📁 项目结构
```txt
PA2D/
├── pa2d.h          # 主头文件
├── pa2d.lib        # 发布版库文件
├── pa2dd.lib       # 调试版库文件
├── examples/           # 示例代码
└── README.md
```

## 配置项目

下载 PA2D 库文件

将 include/ 目录添加到头文件搜索路径

链接相应的库文件 (pa2d.lib 或 pa2dd.lib)

在代码中包含头文件：#include "pa2d.h"

## 环境要求

Windows 7 或更高版本

Visual Studio 2019 或更高版本

C++14 或更高标准

## 🎮 使用示例

### 基本绘制示例

```cpp
#include "pa2d.h"
using namespace pa2d;

int main() {
    Window window(600, 400, "PA2D 示例");
    Canvas canvas(600, 400);
    
    window.show();
    
    // 绘制图形
    canvas.clear(White)
          .circle(200, 200, 50, None, Red, 3)
          .rect(100, 100, 200, 100, LightBlue, Blue, 2)
          .textCentered(L"Hello PA2D!", 300, 300, Black, 20);
    
    while (window.isOpen()) {
        window.render(canvas);
    }
    return 0;
}
```
### 多窗口应用

```cpp
#include "pa2d.h"
using namespace pa2d;

int main() {
    Window w1(600, 400, "窗口1");
    Window w2(600, 400, "窗口2");
    Canvas canvas1(600, 400), canvas2(600, 400);
    
    // 分别绘制内容
    canvas1.clear(Black).circle(200, 200, 50, None, Red, 5);
    canvas2.clear(White).rect(100, 100, 200, 100, None, Blue, 5);
    
    w1.setPosition(100, 100).show();
    w2.setPosition(750, 100).show();
    
    while (w1.isOpen() && w2.isOpen()) {
        w1.render(canvas1);
        w2.render(canvas2);
        Sleep(16);
    }
    return 0;
}
```

## 🔧 API 设计理念

### 流畅接口设计

```cpp
// 所有几何对象共享统一接口
circle.translate(10, 20).rotate(45).scale(2.0);
rect.translate(10, 20).rotate(45).scale(2.0);

// 链式绘制调用
canvas.clear(Black)
     .rect(10, 10, 100, 50, LightBlue)
     .circle(50, 50, 30, Red)
     .text("Hello", 20, 20, White);
```

### 显式控制流程

```cpp
Window window(800, 600);     // 显式创建窗口
window.show();               // 显式显示窗口
Canvas canvas(800, 600);     // 显式创建画布
canvas.circle(...);          // 显式绘制图形
window.render(canvas);       // 显式执行渲染
```

## 📚 示例代码

项目包含多个实用示例：

· basic_demo.cpp - 基础图形绘制

· multi_window.cpp - 多窗口管理

· clock_app.cpp - 实时时钟应用

· file_drop.cpp - 文件拖放功能

## 🐛 问题反馈

如果你遇到任何问题，请通过以下方式反馈：

1. 在 GitHub Issues 中创建新问题

2. 描述详细的重现步骤

3. 提供相关的代码片段和错误信息


**主要权利**：

· ✅ 自由使用

· ✅ 用于商业项目

**唯一要求**：

📝 在分发时保留原始的版权声明

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者，特别感谢 EasyX 图形库的启发。
