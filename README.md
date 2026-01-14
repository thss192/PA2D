<a id="chinese"></a>
# PA2D 图形库
[English](#english) | [中文](#chinese)

您可以通过访问官网 <https://PrismArch.cn> 了解更多信息

PA2D 是一个基于CPU管道的、高性能且轻量、过程透明的图形库，如同它的名字一样：  
1. **PrismArch** - 注重接口与整体架构的设计理念  
2. **Pixel Accelerated** - CPU端对像素位图进行操作  
3. **Procedural Algorithm** - 全过程透明，搭建整个渲染管线  

它的不同之处：  
1. **技术独特** ：基于位图的软渲染管道，CPU端图形绘制(SIMD优化)
2. **学习友好** ：不沿用旧范式，有着像素渲染的纯粹性、接口极简的易用性
3. **架构解耦** ：渲染逻辑与窗口逻辑解耦，提高了灵活性和扩展性
4. **接口易用** ：使用统一的接口风格，智能提示友好，无状态机、极少枚举
5. **功能精简** ：默认透明度、抗锯齿，坚持C++风格，支持各种图像操作与混合模式等常用功能
6. **简洁头文件** ：整合制作了外部头文件，impl隐藏内部实现，易于查阅API，注释对AI友好
7. **性能充足** ：可用于2D游戏、UI应用、(也可以自主实现3D)，位图预处理与SIMD可使效率优化十几倍

以下是简单的示例代码
```cpp
#include<pa2d.h>
using namespace pa2d;

int main(){
  // 创建一个画布
  Canvas canvas(640, 480);
  // 构造样式： 半透明红色填充 + 半透明绿色线框 + 3像素线宽 + 25弧度圆角
  Style style = 0x80FF0000_fill + 0x800000FF_stroke + 3_w + 25_r;
  // 绘制圆角矩形
  canvas.rect(100, 100, 200, 100, style);
  // 创建窗口
  Window window(640, 480, "My window");
  // 显式窗口 -> 渲染画布 -> 堵塞线程
  window.show()
    .render(canvas)
    .waitForClose();
```
  
本项目采用MIT许可

<a id="english"></a>
# PA2D Graphics Library
[English](#english) | [中文](#chinese)

You can visit the official website <https://PrismArch.cn> for more information.

PA2D is a CPU pipeline-based, high-performance, lightweight, and process-transparent graphics library. As its name suggests:
1. **PrismArch** - Focus on interface and overall architecture design philosophy
2. **Pixel Accelerated** - CPU-side operations on pixel bitmaps
3. **Procedural Algorithm** - Fully transparent process, building the entire rendering pipeline

Its distinctive features:
1. **Unique Technology**: Bitmap-based software rendering pipeline, CPU-side graphics drawing (SIMD optimized)
2. **Learning-Friendly**: Doesn't follow old paradigms, offers the purity of pixel rendering and minimalist interface ease-of-use
3. **Architecture Decoupling**: Rendering logic is decoupled from window logic, improving flexibility and extensibility
4. **User-Friendly Interface**: Uses a unified interface style, IDE-intelligent suggestion friendly, no state machines, minimal enumerations
5. **Streamlined Features**: Default transparency, anti-aliasing, adheres to C++ style, supports various image operations and blend modes
6. **Concise Header File**: Integrated external header file, impl hides internal implementation, easy to browse API, comments are AI-friendly
7. **Adequate Performance**: Can be used for 2D games, UI applications, (also supports custom 3D implementation), bitmap preprocessing and SIMD can optimize efficiency by over ten times

Here's a simple example code:

```cpp
#include<pa2d.h>
using namespace pa2d;

int main(){
    // Create a canvas
    Canvas canvas(640, 480);
    // Construct style: semi-transparent red fill + semi-transparent green stroke + 3px width + 25 radius rounded corners
    Style style = 0x80FF0000_fill + 0x800000FF_stroke + 3_w + 25_r;
    // Draw rounded rectangle
    canvas.rect(100, 100, 200, 100, style);
    // Create window
    Window window(640, 480, "My window");
    // Show window -> Render canvas -> Block thread
    window.show()
        .render(canvas)
        .waitForClose();
    return 0;
}
```

This project is licensed under MIT.
