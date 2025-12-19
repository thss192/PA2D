# PA2D 1.0.0-beta1 版本

## 关于 **1.0.0-beta1**
此项目已经做了2个半月了，我经常重构以及更改接口，以及前段时间做了一些测试，认为这个版本已经可以用于实验性地做一些小的作品了。  

## 如何使用这个库(对Visual Studio安装十分友好，文章末尾会有安装方式)

###  Step 1: 实验性地使用一下 Window 类
引入头文件后，尝试创建一个窗口  
```cpp
#include<pa2d.h>
using namepsace pa2d;
// 创建一个 640*480 的窗口
Window window(640, 480，"My first PA2D Window");
```
事实上，初次创建窗口并不会立即显示，因为初始化并不代表着显示  

让我们在main函数中，调用窗口的`show()`方法  
```cpp
int main(){
  window.show();
  // 我提供了 waitForClose() 方法方便展示窗口
  // 防止程序立即退出
  window.waitForClose();
}
```

运行后，我们就会获得以下的窗口    
<img width="640" height="480" alt="QQ_1766144139681" src="https://github.com/user-attachments/assets/ef4dcf9e-82d8-46b6-a809-be4d50f531a5" />
  
事实上，我们可以通过Window对象，去查找相关的方法  

<img width="250" height="260" alt="QQ_1766144296586" src="https://github.com/user-attachments/assets/9e4b38af-9adc-4ffc-8adb-858d27738de3" />
  
PA2D库大部分常用方法都在对象的方法里，很方便用户平时预览  

你或许会探索到一些有趣的功能  
例如：让我们"**克隆**"一个窗口  
```cpp
#include<pa2d.h>
// 创建一个 640*480 的窗口
using namespace pa2d;
Window window(640, 480, "My first PA2D Window");
int main() {
	window.show();
	// 克隆一个窗口
	Window(window).show()
		.waitForClose(); // 链式调用
}
```
会获得以下效果  
<img width="640" height="480" alt="image" src="https://github.com/user-attachments/assets/8127eee5-66ec-4f37-9a84-11f54eaca888" />

###  Step 2: 尝试用PA2D来绘画
PA2D 的框架会方便你做出许多有趣的效果  
不过当下之急，让我们在窗口上绘制上一些东西  
这才是图形库的核心功能  
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
  
我理解这里会出现一些"**黑魔法**"的语法  
但我希望用户会喜欢这些方便灵活的语法  

#### 字面量样式
我们使用加号将几个`Style`样式拼接起来，以实现不同的效果
```cpp
  // 字面量语法
  // 不透明绿色(填充) +  不透明红色(线框) + 3像素线宽
	Style style = 0xFF00FF00_fill + 0xFFFF0000_stroke + 3_w;
	canvas.circle(100, 100, 60, style);
  // 也支持字符串的字面量
  Style Red_fill = "255,255,0,0"_fill;
  Style Green_stroke = "#00FF00"_stroke;  //自动补充为不透明
  Style newStyle = Red_fill + Green_stroke;
```
PA2D默认支持透明度和抗锯齿，颜色使用"ARGB"  
其内存布局为`struct { uint8_t b, g, r, a; };`  

#### 链式调用
```cpp
	// 半透明颜色
	Style style = 0x800000FF_fill + 0x80FF0000_stroke ;
	canvas.circle(100, 100, 60, style + 2_w) // 不同宽度
		.rect(100, 100, 120, 80, style + 4_w);
```
<img width="640" height="480" alt="QQ_1766146318998" src="https://github.com/user-attachments/assets/a35bd2f2-5255-4912-9609-c69100ca82cd" />

我相信这种语法会在处理多个画布和窗口对象时  
会让代码非常清晰和结构化  

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

### 📦 安装指南

#### 1. 下载安装程序
点击下载：[pa2d-1.0.0-beta1-setup.exe](https://github.com/thss192/PA2D/1.0.0-beta1/pa2d-1.0.0-beta1.exe)  
文件大小：约 4.02 MB  

#### 2. 运行安装向导
<img width="640" height="480" alt="QQ_1766147865981" src="https://github.com/user-attachments/assets/99000044-5381-4e22-9e91-425c1d1f055b" />  
*图：安装程序欢迎界面*  

#### 3. 自动检测Visual Studio
<img width="640" height="480" alt="QQ_1766147903306" src="https://github.com/user-attachments/assets/5e2750fd-def1-4611-962b-9c06033a61f0" />  
*图：自动检测已安装的Visual Studio版本*  

#### 4. 安装进指定目录
<img width="640" height="480" alt="QQ_1766147920349" src="https://github.com/user-attachments/assets/72db1af4-3c7e-4dc8-b6e3-ebb618d29828" />  
*图：安装完成后，PA2D的安装位置*  

#### 5. 在Visual Studio中使用
安装完成后，在Visual Studio项目中：  
```cpp
#include <pa2d.h>
using namespace pa2d;

// 现在可以开始使用了！  
```

#### 有经验的用户可选择github仓库下载库文件手动安装

#### 提供了卸载方式
<img width="640" height="350" alt="QQ_1766148349939" src="https://github.com/user-attachments/assets/eed86699-3061-4966-90b3-109710c1e667" />

---

**PA2D** - 让图形编程更简单！ ✨
