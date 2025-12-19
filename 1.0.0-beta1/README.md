# PA2D 1.0.0-beta1 版本
  
**关于 1.0.0-beta1 ：**  

此项目已经做了2个半月了，我经常重构以及更改接口，以及前段时间做了一些测试，认为这个版本已经可以用于实验性地做一些小的作品了。  
    
---
  
## 如何使用这个库
对Visual Studio安装十分友好，有自动化安装程序  
📦 快速安装：[点击跳转](#installation)

###  **Step 1** : 使用Window类管理窗口
#### 创建一个窗口  
```cpp
#include<pa2d.h>
using namepsace pa2d;
int main(){
  // 创建一个 640*480 的窗口
  Window window(640, 480，"My first PA2D Window");
  // 显式这个窗口
  window.show();
  // 等待窗口关闭
  window.waitForClose();
}

// Note:
// 事实上，初次创建窗口并不会立即显示，因为初始化并不代表着显示
// 我提供了 waitForClose() 方法方便展示窗口，防止程序立即退出
```  
  
  运行后，我们就会获得以下的窗口      
<img width="640" height="480" alt="QQ_1766144139681" src="https://github.com/user-attachments/assets/ef4dcf9e-82d8-46b6-a809-be4d50f531a5" />  
  
  *图：第一个窗口示例*  
  
#### 多个窗口
PA2D 是基于面向对象的，你会在使用过程中探索到一些有趣的功能:  
```cpp
#include <pa2d.h>
using namespace pa2d;

int main() {
    Window window(640, 480, "Original Window");

    // 显式初始窗口
    window.show()
        .setPosition(100, 100);
    // 拷贝构造(复制所有窗口状态)
    Window clonedWindow = window;  

    clonedWindow
        .setPosition(800, 100)
        .setTitle("Cloned Window");

    // 等待原始窗口关闭
    window.waitForClose();
}
```
<img width="640" height="480" alt="QQ_1766149996782" src="https://github.com/user-attachments/assets/ea8c6c8c-4983-4bf8-8f11-2a704d7ec496" />  
  
*图：多窗口示例*  
	
###  Step 2: 在Canvas类上绘制图形
#### 绘制一个圆
```cpp
#include<pa2d.h>
// 创建一个 640*480 的窗口
using namespace pa2d;
Window window(640, 480, "My first PA2D Window");
int main() {
	window.show();
	// 创建一个画布
	Canvas canvas(640, 480);
	// 在画布上画一个圆
	canvas.circle(100, 100, 60, Green_fill + Red_stroke);
	// 让窗口去渲染画布
	window.render(canvas)
		.waitForClose();
}
```  
<img width="640" height="480" alt="QQ_1766145245946" src="https://github.com/user-attachments/assets/5334ceda-f323-45ea-bf28-594636179fe6" />
  
---
  
## 关于 PA2D 的语法
PA2D 采用了一些现代C++的语法特性，让代码更简洁直观。  
如果你第一次见到这些"**黑魔法**"，不用担心，它们其实很简单！  
  
### 🔤 字面量样式
```cpp
  // 传统方式
  // Style style{};
  // style.fill_ = 0xFF00FF00;    // 不透明绿色(填充)
  // style.stroke_ = 0xFFFF0000;  // 不透明红色(线框)
  // style.width_ = 3;            // 3像素线宽

  // PA2D的字面量语法(一行解决！)
  Style style = 0xFF00FF00_fill + 0xFFFF0000_stroke + 3_w;

  canvas.circle(100, 100, 60, style);

  // 支持多种语法
  Style Red_fill = "255,255,0,0"_fill;
  Style Green_stroke = "#00FF00"_stroke;  //自动补充为不透明
  Style newStyle = Red_fill + Green_stroke;
```
  
原理：通过后缀 _fill、_w 等将数字直接转换为对象。  
  
### 🔗链式调用
```cpp
	// 半透明颜色
	Style style = 0x800000FF_fill + 0x80FF0000_stroke ;

	// 传统方式（需要重复对象名）
	// canvas.circle(100, 100, 60, style + 2_w);
    // canvas.rect(100, 100, 120, 80, style + 4_w);

	// 链式调用（更流畅！）
	canvas.circle(100, 100, 60, style + 2_w) // 组合不同宽度
		.rect(100, 100, 120, 80, style + 4_w);
```
  
原理：每个方法都返回对象自身的引用，可以连续调用。  
<img width="640" height="480" alt="QQ_1766146318998" src="https://github.com/user-attachments/assets/a35bd2f2-5255-4912-9609-c69100ca82cd" />

💡 为什么这样设计？  
· 代码更简洁：减少重复  
· 可读性更高：操作顺序一目了然  
· 符合直觉：像自然语言一样表达  

这些语法都是可选的，你也可以使用传统写法。  
但一旦习惯，你会发现它们让图形编程变得更加愉快！ 
  
---
  
## PA2D 当前的功能
  
PA2D 内部做了许多AVX2的优化，为图形绘制优化提升了效率  
相信相较于普通的标量版本，其可以提升近16倍的效率  
PA2D的离屏渲染、画布预处理等框架，我认为可以优化更多  

当前的v1.0.0-beta1 版本  
已经实现了许多功能：  
### 🎨 **图形绘制**
| 功能 | 说明 |
|------|------|
| 基础形状 | 点、线、矩形、圆形、椭圆、三角形 |
| 圆角矩形 | 可自定义圆角半径 |
| 多边形绘制 | 任意顶点多边形 |
| 扇形绘制  | 支持弧线和边线控制 |
| 抗锯齿 | 所有几何图形默认抗锯齿 |
| 样式系统  | 填充+描边+宽度+圆角控制 |
| 透明度  | ARGB颜色格式，Alpha混合 |

### 🪟 **窗口系统**
| 功能 | 说明 |
|------|------|
| 多窗口支持  | 独立的窗口线程 |
| 事件回调 | 键盘、鼠标、调整大小等 |
| 窗口控制  | 最大化/最小化/置顶等 |
| 剪贴板  | 文本和文件操作 |
| 菜单系统 | 创建和管理菜单 |

### 🖼️ **图像处理**
| 功能 | 说明 |
|------|------|
| 图像加载 | PNG/JPG/BMP格式支持 |
| 图像变换  | 缩放、旋转、裁剪 |
| 混合模式  | Alpha/Add/Multiply/Screen/Overlay等 |
| 离屏渲染  | Canvas缓冲 |

### 📝**文本绘制**
| 功能 | 说明 |
|------|------|
| 字体选择 | 系统字体支持 |
| 文本对齐 | 居中、矩形内布局 |
| 文本样式 | 粗体、斜体、旋转等 |
| 抗锯齿 | GDI文字抗锯齿 |
| 多编码 | ANSI/UTF8支持 |

### 🛠️**易用性**
| 功能 | 说明 |
|------|------|
| 字面量支持 | `0xFF0000_fill + 2.0_w` |
| 几何对象系统 | 统一变换接口 |
| 链式调用  | 流畅API设计 |
| 内存管理  | RAII自动管理 |

PA2D的工作量实在太大，我目前还未做退回版本  
当前版本能够支持2013+年代的电脑，可以覆盖大多数环境下的创作  
对于硬件不支持的电脑，我也做了友好提示(自动检测AVX2支持，以下为pa2d.h中的代码)  
```cpp
    // ==================== CPU REQUIREMENT ====================
    // AVX2 hardware requirement check - executes at program startup
    // If CPU lacks AVX2 support, displays error message and terminates
    static const struct AVX2_Verifier {
        AVX2_Verifier();
    }AVX2_CHECK_INSTANCE;
```
  
---
  
<a id="installation"></a>
## 📦 安装指南

### 1. 下载安装程序
点击下载：[pa2d-1.0.0-beta1-setup.exe](https://github.com/thss192/PA2D/1.0.0-beta1/pa2d-1.0.0-beta1.exe)  
文件大小：约 4.02 MB  

### 2. 运行安装向导
<img width="640" height="480" alt="QQ_1766147865981" src="https://github.com/user-attachments/assets/99000044-5381-4e22-9e91-425c1d1f055b" />  
  
*图：安装程序欢迎界面*  

### 3. 自动检测Visual Studio
<img width="640" height="480" alt="QQ_1766147903306" src="https://github.com/user-attachments/assets/5e2750fd-def1-4611-962b-9c06033a61f0" />  
  
*图：自动检测已安装的Visual Studio版本*  

### 4. 安装进指定目录
<img width="640" height="480" alt="QQ_1766147920349" src="https://github.com/user-attachments/assets/72db1af4-3c7e-4dc8-b6e3-ebb618d29828" />  
  
*图：安装完成后，PA2D的安装位置*  

### 5. 在Visual Studio中使用
安装完成后，在Visual Studio项目中：  
```cpp
#include <pa2d.h>
using namespace pa2d;

// 现在可以开始使用了！  
```
### 注册表中提供了卸载方式
<img width="640" height="350" alt="QQ_1766148349939" src="https://github.com/user-attachments/assets/eed86699-3061-4966-90b3-109710c1e667" />

### 手动安装
  
有经验的用户可选择github仓库下载库文件手动安装
仓库地址：https://github.com/thss192/PA2D/
  
---

**PA2D** - 让图形编程更简单！ ✨
