# PA2D

## 📖 1. 什么是 PA2D？ | What is PA2D?

**中文：**  
在编程创作过程中，我接触了 EasyX，这个能让人快速开发窗口界面的库，并开始痴迷于图形化创作。  
当时我需要绘制带有透明度的贴图，而 EasyX 本身并不支持透明度渲染。我从网上找到了通过操控缓冲区进行颜色混合的函数，从而实现了想要的效果。  
理解这个原理后，我开始尝试各种效果：将图片从暗到亮显式、对图片进行切割等。

**英文 | English:**  
In my programming journey, I encountered EasyX, a library that allows quick window interface development, and became fascinated with graphical creation.  
At the time, I needed to draw textures with transparency, but EasyX itself did not support alpha rendering. I found functions online for color blending by manipulating the buffer, achieving the desired effect.  
After understanding this principle, I began experimenting with various effects: fading images from dark to bright, slicing images, etc.

---

**中文：**  
手动操控像素带我进入了一个不同的世界。面对已有的函数，我时常思考：**我是否可以做一个更好、更高性能的实现方案？**  
在以游戏为目的、优化绘制效果的过程中，我意识到了软件渲染的瓶颈，也萌生了深入研究 Shader 渲染的想法。  
但我不忍心放弃研究了几个月的心血，于是决定将原来的游戏项目重构为一个图形库。  
PA2D 并非为某个具体目标而设计，只是希望让我的工作更有价值一些。

**英文 | English:**  
Manually manipulating pixels brought me into a different world. Facing existing functions, I often wondered: **Could I create a better, higher-performance implementation?**  
While optimizing drawing effects for game development, I recognized the limitations of software rendering and developed an interest in studying shader rendering.  
However, I couldn't bear to abandon months of research effort, so I decided to refactor the original game project into a graphics library.  
PA2D wasn't designed for a specific purpose—I simply wanted my work to have more value.

---

**中文：**  
因此，PA2D 是一个从游戏项目演变为图形库的项目。重构过程中，我注重 API 的便捷性，倾向于提供直接操控缓冲区的接口，并完全暴露图像渲染的全过程。  
它的方向可能与其他图形库有所不同，这源于以下几点：

**英文 | English:**  
Thus, PA2D is a project that evolved from a game into a graphics library. During refactoring, I focused on API convenience, preferring to provide direct buffer manipulation interfaces while fully exposing the entire image rendering process.  
Its direction may differ from other graphics libraries, stemming from the following reasons:

---

### 🔧 设计理念与特点 | Design Philosophy & Features

#### 1. 技术实现自主性 | Independent Technical Implementation
**中文：**  
由于对 GDI 等传统绘图底层实现不太了解，我选择自己实现 `Color`、`Buffer` 等存储结构。在底层，我只想将 `Buffer` 直接投放到窗口上，展示手动操控像素之美。这样的实现不经意间带来了与具体窗口解耦、离屏渲染、多画布支持、易于扩展等特点。我明白这个库的实现是站在巨人的肩膀上——得益于更快的 CPU、更大的传输带宽、SIMD 技术的支持，以及 AI 的辅助，让我能够快速迭代与测试。

**英文 | English:**  
Due to limited understanding of traditional graphics implementations like GDI, I chose to implement storage structures like `Color` and `Buffer` myself. At the low level, I simply wanted to display the `Buffer` directly onto windows, showcasing the beauty of manual pixel manipulation. This implementation inadvertently enabled features like window decoupling, off-screen rendering, multi-canvas support, and easy extensibility. I understand this library stands on the shoulders of giants—benefiting from faster CPUs, greater bandwidth, SIMD technology, and AI assistance, allowing rapid iteration and testing.

#### 2. 性能优先的现代设计 | Performance-First Modern Design
**中文：**  
面对我在配置一般的笔记本电脑上仅能达到 90FPS 的游戏画面，以及多次优化仍无法稳定提升效率的困境，我选择不受向前兼容的约束，尽可能使用较新且应用广泛的 C++ 语法、SIMD 支持等技术，以获取更好的性能。API 设计仍在进行中，可能会持续迭代，目标是让创作更便捷、体验更流畅。

**英文 | English:**  
Facing game visuals that only reached 90FPS on my average laptop and optimization efforts that couldn't consistently improve efficiency, I chose not to be constrained by backward compatibility. Instead, I opted to use newer, widely adopted C++ features, SIMD support, and other technologies for better performance. API design is ongoing and may continue evolving, aiming to make creation easier and experience smoother.

#### 3. 学习与实践并重 | Balancing Learning and Practice
**中文：**  
PA2D 涉及现代 C++ 语法、并行优化技术、API 设计哲学等方面。它从工程实践出发，伴随一个初学者逐步优化的学习路径，或许能提供一些独特的学习意义。

**英文 | English:**  
PA2D encompasses modern C++ syntax, parallel optimization techniques, API design philosophy, and more. Starting from engineering practice, it follows a beginner's progressive optimization learning path, potentially offering unique educational value.

#### 4. 面向特定爱好者 | Targeting Specific Enthusiasts
**中文：**  
对于一些偏冷门的兴趣爱好者，或许能在 PA2D 中找到共鸣——例如想要设计优雅的 API 语法、使用 SIMD 进行并行优化实践、手动操控像素等。PA2D 也许能为这些实践提供一个平台。

**英文 | English:**  
For enthusiasts with niche interests, PA2D might resonate—such as those wanting to design elegant API syntax, practice parallel optimization with SIMD, or manually manipulate pixels. PA2D could provide a platform for such practices.

---

## ⚡ 2. PA2D 现在可以做什么？ | What can PA2D currently do?

**中文：**  
目前的这个库，并没有包含它起源游戏的所有功能，比如径向渐变的粒子效果、某些特殊的图案绘制函数等。  
因为库正在设计和不断完善中，它提供的是最基础的实现方案，而不是"开箱即用"的成品。  
当前库直接暴露 `Buffer` 的 `Color*`，鼓励开发者自己去实现更出色的效果。  
我不知道现在是否存在其他完美的库，我只想创造带有我思考痕迹的作品。  
**技术力决定想象力和创造力，从无到有离不开实践。**

**英文 | English:**  
The current library doesn't include all features from its originating game, such as radial gradient particle effects or certain specialized pattern drawing functions.  
As the library is still being designed and continuously improved, it offers foundational implementations rather than "out-of-the-box" complete solutions.  
Currently, the library directly exposes `Buffer`'s `Color*`, encouraging developers to implement more impressive effects themselves.  
I don't know if other perfect libraries exist; I simply want to create work that bears my thought process.  
**Technical capability determines imagination and creativity; creating from nothing requires practice.**

---

### 📦 目前已实现的功能 | Currently Implemented Features:

| 功能模块 | 中文说明 | English Description |
|----------|----------|---------------------|
| **Window 窗口类** | 后台线程运行、与渲染逻辑解耦、不抢占主逻辑 | Runs in background threads, decoupled from rendering logic, non-blocking for main logic |
| **Canvas 画布类** | `Buffer` 存储结构与渲染算法函数的代理层，提供友好的链式 API | Proxy layer for `Buffer` storage structure and rendering algorithm functions, providing friendly chained API |
| **Shape 几何对象** | 临时实现的几何变换，旨在为绘图提供便利（我认为其设计还有提升空间） | Temporarily implemented geometric transformations aimed at facilitating drawing (I believe its design has room for improvement) |
| **Style 几何样式** | 因设计 `Shape` 类而考虑将样式参数封装起来，恰巧了解到字面量，这是一个便捷的方案 | Considering encapsulation of style parameters due to designing the `Shape` class; coincidentally learned about literals, which provide a convenient solution |
| **Color、Buffer 等** | 基础结构，方便用户自行进行分支实验 | Fundamental structures allowing users to conduct branching experiments independently |

---

## 📁 项目文件结构 | Project File Structure

**中文：**  
目前我将项目简化为以下文件：

**英文 | English:**  
Currently, I've simplified the project to the following files:

| 文件类型 | 中文说明 | English Description |
|----------|----------|---------------------|
| `pa2d.h` | 主头文件 | Main header file |
| `pa2d.lib` | 发布版本库文件 | Release version library file |
| `pa2dd.lib` | 调试版本库文件 | Debug version library file |
| `pa2d_install.exe` | 针对 Visual Studio 的安装包 | Installation package for Visual Studio |

---

### 🔍 这样简化的原因 | Reasons for This Simplification:

**中文：**  
1. 在项目当前阶段，希望提供最直接的创作方式，而非过早暴露实现细节。  
2. 想要了解最新功能与 API 接口，可直接查看组织好的 `pa2d.h` 以及示例代码。  
3. 目前 API 仍处于快速迭代中，且文件组织方式尚未达到理想状态。

**英文 | English:**  
1. At the current project stage, we aim to provide the most direct creative approach rather than prematurely exposing implementation details.  
2. To understand the latest features and API interfaces, directly refer to the organized `pa2d.h` and example code.  
3. Currently, the API is still in rapid iteration, and the file organization hasn't reached an ideal state.

---

**中文：**  
我会在项目有一定知名度或代码组织完善后进行开源，并提供贡献指南。

**英文 | English:**  
I will open-source the project when it gains some recognition or when the code organization is refined, along with providing contribution guidelines.
<a id= pa2d---modern-c-2d-graphics-programming-library></a>

# PA2D - Modern C++ 2D Graphics Programming Library

English | [简体中文](#pa2d---轻量级-c-2d-图形库)

## 🎯 Project Overview

PA2D is a lightweight 2D graphics programming library designed for modern C++, providing developers with simple yet powerful graphics drawing solutions. It perfectly balances beginner-friendliness and professional development needs, making graphics programming more intuitive and efficient.

## 📦 Release Contents

**Current Status**: This version is provided as closed-source freeware. We plan to open-source it in future releases.

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

<a id= pa2d---轻量级-c-2d-图形库></a>

# PA2D - 轻量级 C++ 图形库

简体中文 | [English](#pa2d---modern-c-2d-graphics-programming-library) 

## 🎯 项目简介

PA2D 是一个专为现代 C++ 设计的轻量级 2D 图形编程库，旨在为开发者提供简单易用且功能强大的图形绘制解决方案。它完美平衡了初学者友好性和专业开发需求，让图形编程变得更加直观和高效。

## 📦 发布内容

**当前状态**: 当前版本为闭源免费使用，计划在未来版本中开源。

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

