# PA2D Graphics Library
<a id="english"></a>
[English](#english) | [中文](#chinese)
## ⚡ 1. Quick Overview
PA2D is a CPU pipeline-based, high-performance, lightweight, and process-transparent graphics library. As its name suggests:
1. **PrismArch** - Focus on interface and overall architecture design philosophy
2. **Pixel Accelerated** - CPU-side operations on pixel bitmaps
3. **Procedural Algorithm** - Fully transparent process, supporting user branching and experimentation

## 📁 Project File Structure
Current simplified project structure:

| File Type | Description |
|-----------|-------------|
| `pa2d.h` | Main header file |
| `pa2d.lib` | Release library |
| `pa2dd.lib` | Debug library |
| `pa2d_install.exe` | Visual Studio installer |

### 🔍 Reasons for This Simplification:
1. At the current project stage, providing the most direct creative approach rather than exposing implementation details
2. To understand the latest features and API interfaces, users can directly view the organized pa2d.h and example code
3. The API is still in rapid iteration, and the file organization is not yet perfect

### 📦 Currently Implemented Features:
1. **Window Class** - Background thread, decoupled from rendering logic, non-blocking main logic
2. **Canvas Class** - Buffer storage structure and rendering algorithm function proxy layer, providing friendly chain-style API
3. **Shape Geometry Objects** - Temporary geometric transformations designed to facilitate drawing (needs improvement)
4. **Style Geometry Styles** - With the Shape class design, style parameters were encapsulated, coinciding with learning about literals which provide a convenient solution
5. **Color, Buffer, etc.** - Basic structures to facilitate user branching and experimentation

## 🔮 Future Plans
I will open-source this project when it gains some recognition or after code organization is complete, and provide contribution methods.

## 📖 Origin and Characteristics of PA2D
During programming and creative work, I encountered EasyX, a library that allows rapid development of window interfaces, and became fascinated with graphical creation.

At that time, I wanted to render images with transparency. EasyX itself didn't support alpha blending, so I found functions online for color blending by manipulating buffers to achieve the desired visual effects.

Understanding this principle led me to experiment with various effects: gradually revealing images from dark to light, slicing images, etc.

Manually controlling individual pixels opened up a new world for me. Facing existing functions, I began wondering: could I create better, higher-performance implementations?

While optimizing drawing functions for game development purposes, I recognized the bottlenecks of software rendering and developed an interest in studying shader rendering.

Unwilling to completely abandon months of work, I decided to refactor the original game project into a graphics library. This library wasn't created for a specific purpose but rather to give more value to my efforts.

Thus, PA2D is a project transformed from a game into a graphics library. During refactoring, API convenience was prioritized, favoring interfaces for direct buffer manipulation and fully exposing the image rendering process.

Its direction may differ from other graphics libraries for several reasons:
1. Without deep knowledge of traditional graphics APIs like GDI, I chose to create my own Color and Buffer structures for storing information. At the lowest level, I simply want to directly output my Buffer to the window, showcasing the beauty of manually manipulated pixels. This approach unintentionally resulted in features like decoupling from specific windows, off-screen rendering, multi-canvas support, and easy extensibility. I recognize this library stands on the shoulders of giants - faster CPU processing, greater bandwidth, SIMD technology, and AI assistance for rapid iteration and testing.

2. Facing 90FPS game performance (on my mediocre laptop) and repeated optimizations that still couldn't consistently improve efficiency, I chose not to be constrained by backward compatibility. I aim to use the latest widely-adopted C++ syntax, SIMD support, and other technologies for optimal results. API design remains in progress, likely to continue iterating, but always with the goal of facilitating creation and enhancing the creative experience.

3. The library will involve modern C++ syntax, parallel optimization techniques, API design philosophy, etc. Being engineering-focused and following a beginner's optimization learning path may provide unique educational value.

4. For niche enthusiasts - those interested in designing elegant API syntax, practicing SIMD parallel optimization, or manually controlling pixels - PA2D might offer a suitable platform.


# PA2D 图形库
<a id="chinese"></a>
[English](#english) | [中文](#chinese)
## ⚡ 1. 快速了解
PA2D 是一个基于CPU管道的、高性能且轻量、过程透明的图形库，如同它的名字一样：
1. **PrismArch** - 注重接口与整体架构的设计理念
2. **Pixel Accelerated** - CPU端对像素位图进行操作
3. **Procedural Algorithm** - 全过程透明，支持用户自己做分支和实验

## 📁 项目文件结构
目前我将项目文件简化为：

| 文件类型 | 说明 |
|----------|------|
| `pa2d.h` | 主头文件 |
| `pa2d.lib` | 发布时库 |
| `pa2dd.lib` | 调试时库 |
| `pa2d_install.exe` | 针对于Visual Studio的安装包 |

### 🔍 这样简化的原因：
1. 在项目当前阶段，提供最直接的创作方式，而并非暴露实现原理
2. 想要了解最新版本的功能和API接口，可以直接查看我组织好的pa2d.h以及示例代码
3. 目前API仍然在快速迭代过程中，且其文件组织方式并不完美

### 📦 目前已实现的功能：
1. **Window 窗口类** - 后台线程、与渲染逻辑解耦、不强占主逻辑
2. **Canvas 画布类** - Buffer存储结构 与 渲染算法函数 的代理层 提供友好的链式API
3. **Shape 几何对象** - 临时做出来的几何变换，希望能够给绘图提供便利(有待完善)
4. **Style 几何样式** - 由于设计了Shape类，我考虑到把样式参数也封装起来，恰巧了解到字面量，这是一个很便捷的方案
5. **Color、Buffer等** - 基础结构，方便用户自己做分支和实验

## 🔮 未来规划
我会在此项目有一定知名度或项目代码组织完毕后进行开源，且提供贡献方式。

## 📖 PA2D来源与特点
在编程创作过程中，我接触了EasyX，这个能让人快速开发一个窗口界面的库，我就开始痴迷于图形化的创作。

届时我想要绘制带有透明度的贴图，EasyX本身并不支持透明度渲染，我在网上找到了通过操控缓冲区进行颜色混合的函数，从而获得我想要的画面效果。

懂得了这个原理之后，我就开始尝试各种效果：将图片从暗到亮进行显式、对图片进行切割等。

手动操控对应的像素，使我进入不一样的世界，我面对那些已有的函数，我会在想：我是否可以做一个更好的更高性能的实现方案。

在以做游戏为目的，优化函数绘制效果的过程中，我认识到了使用软件渲染的瓶颈，我有了想要去多研究研究shader渲染的想法。

但不忍我研究了几个月的心血被完全废弃，我打算将原来的游戏项目重构为一个图形库，并不明确带有某个目的而实现的这个库，仅仅是因为我想让我做的事情更有价值一些。

所以对于PA2D，它是一个从游戏转换为图形库的一个项目，其重构的过程中考虑了API的便捷性，倾向于提供直接操控缓冲区的接口，且完全暴露出图像渲染的全过程。

同时，它可能会在方向上与其他图形库有所不同，这又源于多个方面的原因：
1. 因为不怎么了解GDI等传统绘图的底层实现，我选择自己做Color,Buffer这些存储信息的结构，并且对于底层，我只想把我的Buffer直接投放到窗口上，展示手搓像素之美，这个实现同时导致了它不经意间拥有与具体窗口解耦、离屏渲染、多画布支持，方便扩展等特点。且我明白这个库的实现是站在巨人的肩膀上，有了快的cpu处理速度，更大的传输宽带，SIMD技术的加持，以及AI的辅助作用，方便我快速迭代与测试。

2. 再者，面对我90FPS的游戏画面(还是在我这个配置差不多的笔记本电脑上)，以及优化了很多次，仍然不能稳定提升效率的窘境。我选择不被向前兼容所约束，最好用上最新的应用还算比较广泛的C++语法、SIMD支持等技术，以获取尽可能好的效果。对于API的设计，我仍然在设计中，或许仍然会迭代，但是目的是为了更方便创作和体验创作的过程。

3. 其对于现代C++语法、并行优化技术、API设计哲学等方面会有一些涉及，且其是基于工程出发，且伴随着一个初学者渐渐优化的学习路径，或许会提供一些独特的学习意义。

4. 对于一些偏于冷门的兴趣爱好者，或许可能会找到？例如想要设计优雅API语法、使用SIMD并行优化进行实践、手动操控像素等需求的实践，或许PA2D有机会提供一个平台。
