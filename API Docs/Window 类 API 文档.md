## 🚀 模块概览：Window 类接口

此文档详细介绍了 Window 类的所有函数接口，包含完整的窗口管理、渲染、事件处理、输入控制等功能。该类负责创建和管理应用程序窗口，处理用户交互，并提供丰富的窗口操作能力。

* 函数/类名 <code><span style="color:#8e44ad">(Window, Canvas): #8e44ad (紫色)</span></code>
* 类型/关键字 <code><span style="color:#2e86c1">(const, int, bool, HWND): #2e86c1 (蓝色)</span></code>
* 参数名/变量名: <code><span style="color:#e74c3c">#e74c3c (红色)</span></code>

---

## 📑 目录

- [� 模块概览：Window 类接口](#-模块概览window-类接口)
- [📑 目录](#-目录)
- [🛠️ 构造与析构](#️-构造与析构)
- [🔍 窗口状态查询](#-窗口状态查询)
- [👁️ 窗口显示控制](#️-窗口显示控制)
- [📏 窗口尺寸与位置](#-窗口尺寸与位置)
- [🎨 渲染功能](#-渲染功能)
- [🎯 事件回调系统](#-事件回调系统)
- [⌨️ 输入状态查询](#️-输入状态查询)
- [⚙️ 高级窗口控制](#️-高级窗口控制)
- [🎭 外观与光标](#-外观与光标)
- [📋 剪贴板与文件拖放](#-剪贴板与文件拖放)
- [🍔 菜单功能](#-菜单功能)
- [📊 系统信息](#-系统信息)
- [💡 使用示例](#-使用示例)

---

## 🛠️ 构造与析构

| 方法 | 方法签名 | 功能说明 |
| :--- | :--- | :--- |
| **构造** | <code><span style="color:#8e44ad">Window</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">height</span>, <span style="color:#2e86c1">const</span> <span style="color:#2e86c1">char</span>* <span style="color:#e74c3c">title</span>)</code> | 创建指定尺寸和标题的窗口 |
| **析构** | <code>~<span style="color:#8e44ad">Window</span>()</code> | 销毁窗口并释放资源 |

**公开成员变量：**
- <code><span style="color:#8e44ad">HWND</span> <span style="color:#e74c3c">hwnd_</span></code> - 窗口句柄
- <code><span style="color:#2e86c1">int</span> <span style="color:#e74c3c">width_</span>, <span style="color:#e74c3c">height_</span></code> - 窗口尺寸
- <code><span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">shouldClose_</span></code> - 窗口关闭标志

---

## 🔍 窗口状态查询

| 查询类型 | 方法签名 | 返回值 | 功能说明 |
| :-------- | :--- | :--- | :--- |
| **窗口开启** | <code><span style="color:#8e44ad">isOpen</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 窗口是否处于开启状态 |
| **窗口可见** | <code><span style="color:#8e44ad">isVisible</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 窗口是否可见 |
| **最大化** | <code><span style="color:#8e44ad">isMaximized</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 窗口是否最大化 |
| **最小化** | <code><span style="color:#8e44ad">isMinimized</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 窗口是否最小化 |
| **全屏状态** | <code><span style="color:#8e44ad">isFullscreen</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 窗口是否处于全屏模式 |

---

## 👁️ 窗口显示控制

| 控制类型 | 方法签名 | 返回值 | 功能说明 |
| :-------- | :--- | :--- | :--- |
| **显示窗口** | <code><span style="color:#8e44ad">show</span>()</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 显示窗口 |
| **隐藏窗口** | <code><span style="color:#8e44ad">hide</span>()</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 隐藏窗口 |
| **关闭窗口** | <code><span style="color:#8e44ad">close</span>()</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 请求关闭窗口 |
| **设置可见性** | <code><span style="color:#8e44ad">setVisible</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">visible</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 设置窗口可见性 |
| **获取焦点** | <code><span style="color:#8e44ad">focus</span>()</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 使窗口获得输入焦点 |

---

## 📏 窗口尺寸与位置

| 操作类型 | 方法签名 | 功能说明 |
| :-------- | :--- | :--- |
| **设置位置** | <code><span style="color:#8e44ad">setPosition</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">y</span>)</code> | 设置窗口屏幕位置 |
| **设置客户区尺寸** | <code><span style="color:#8e44ad">setClientSize</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">height</span>)</code> | 设置客户区尺寸 |
| **设置窗口尺寸** | <code><span style="color:#8e44ad">setWindowSize</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">height</span>)</code> | 设置整个窗口尺寸 |
| **获取位置** | <code><span style="color:#8e44ad">getPosition</span>(<span style="color:#2e86c1">int</span>& <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">int</span>& <span style="color:#e74c3c">y</span>) <span style="color:#2e86c1">const</span></code> | 获取窗口屏幕位置 |
| **获取客户区尺寸** | <code><span style="color:#8e44ad">getClientSize</span>(<span style="color:#2e86c1">int</span>& <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">int</span>& <span style="color:#e74c3c">height</span>) <span style="color:#2e86c1">const</span></code> | 获取客户区尺寸 |
| **获取窗口尺寸** | <code><span style="color:#8e44ad">getWindowSize</span>(<span style="color:#2e86c1">int</span>& <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">int</span>& <span style="color:#e74c3c">height</span>) <span style="color:#2e86c1">const</span></code> | 获取整个窗口尺寸 |

---

## 🎨 渲染功能

将 Canvas 或 Buffer 内容渲染到窗口客户区。

| 渲染方式 | 方法签名 | 功能说明 |
| :-------- | :--- | :--- |
| **基础渲染** | <code><span style="color:#8e44ad">render</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Canvas</span>& <span style="color:#e74c3c">canvas</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">destX</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">destY</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">srcX</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">srcY</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">width</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">height</span>, <span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">clearBackground</span>, <span style="color:#8e44ad">COLORREF</span> <span style="color:#e74c3c">bgColor</span>)</code> | 渲染 Canvas 到指定位置 |
| **居中渲染** | <code><span style="color:#8e44ad">renderCentered</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Canvas</span>& <span style="color:#e74c3c">canvas</span>, <span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">clearBackground</span>, <span style="color:#8e44ad">COLORREF</span> <span style="color:#e74c3c">bgColor</span>)</code> | 居中渲染 Canvas |
| **Buffer渲染** | <code><span style="color:#8e44ad">render</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Buffer</span>& <span style="color:#e74c3c">buffer</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">destX</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">destY</span>, ...)</code> | 直接渲染 Buffer |
| **Buffer居中** | <code><span style="color:#8e44ad">renderCentered</span>(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">Buffer</span>& <span style="color:#e74c3c">buffer</span>, ...)</code> | 居中渲染 Buffer |

**参数说明：**
- <code><span style="color:#e74c3c">destX</span>, <span style="color:#e74c3c">destY</span></code>: 目标位置
- <code><span style="color:#e74c3c">srcX</span>, <span style="color:#e74c3c">srcY</span></code>: 源图像起始位置
- <code><span style="color:#e74c3c">width</span>, <span style="color:#e74c3c">height</span></code>: 渲染区域尺寸(-1表示自动)
- <code><span style="color:#e74c3c">clearBackground</span></code>: 是否清除背景
- <code><span style="color:#e74c3c">bgColor</span></code>: 背景颜色

---

## 🎯 事件回调系统

注册各种窗口事件的处理函数。

| 事件类型 | 方法签名 | 回调类型 | 功能说明 |
| :-------- | :--- | :--- | :--- |
| **键盘事件** | <code><span style="color:#8e44ad">onKey</span>(<span style="color:#8e44ad">KeyCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">KeyEvent</span>&)&gt;</code> | 键盘按键按下/释放 |
| **鼠标事件** | <code><span style="color:#8e44ad">onMouse</span>(<span style="color:#8e44ad">MouseCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">const</span> <span style="color:#8e44ad">MouseEvent</span>&)&gt;</code> | 鼠标移动、点击、滚轮 |
| **尺寸改变** | <code><span style="color:#8e44ad">onResize</span>(<span style="color:#8e44ad">ResizeCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">int</span>, <span style="color:#2e86c1">int</span>)&gt;</code> | 窗口尺寸改变 |
| **关闭事件** | <code><span style="color:#8e44ad">onClose</span>(<span style="color:#8e44ad">CloseCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;<span style="color:#2e86c1">bool</span>()&gt;</code> | 窗口关闭请求 |
| **字符输入** | <code><span style="color:#8e44ad">onChar</span>(<span style="color:#8e44ad">CharCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">wchar_t</span>)&gt;</code> | 字符输入事件 |
| **焦点事件** | <code><span style="color:#8e44ad">onFocus</span>(<span style="color:#8e44ad">FocusCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">bool</span>)&gt;</code> | 窗口获得/失去焦点 |
| **菜单事件** | <code><span style="color:#8e44ad">onMenu</span>(<span style="color:#8e44ad">MenuCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">int</span>)&gt;</code> | 菜单项选择 |
| **文件拖放** | <code><span style="color:#8e44ad">onFileDrop</span>(<span style="color:#8e44ad">FileListCallback</span> <span style="color:#e74c3c">cb</span>)</code> | <code>std::function&lt;void(<span style="color:#2e86c1">const</span> std::vector&lt;std::string&gt;&)&gt;</code> | 文件拖放到窗口 |
| **剪贴板文件** | <code><span style="color:#8e44ad">onClipboardFiles</span>(<span style="color:#8e44ad">FileListCallback</span> <span style="color:#e74c3c">cb</span>)</code> | 同上 | 剪贴板文件变化 |
| **禁用剪贴板** | <code><span style="color:#8e44ad">disableClipboardFiles</span>()</code> | - | 禁用剪贴板文件监听 |

**事件数据结构：**
```cpp
struct KeyEvent {
    int keyCode;    // 虚拟键码
    bool pressed;   // true=按下, false=释放
};

struct MouseEvent {
    int x, y;       // 鼠标位置
    int button;     // 0=左键, 1=右键, 2=中键, -1=滚轮, -2=移动, -3=离开
    bool pressed;   // 按键状态
    int wheelDelta; // 滚轮增量
};
```
## ⌨️ 输入状态查询

实时查询键盘和鼠标的当前状态。

| 查询类型 | 方法签名 | 返回值 | 功能说明 |
| :-------- | :--- | :--- | :--- |
| **鼠标位置** | <code><span style="color:#8e44ad">getMousePosition</span>() <span style="color:#2e86c1">const</span></code> | <code>std::pair&lt;<span style="color:#2e86c1">int</span>, <span style="color:#2e86c1">int</span>&gt;</code> | 获取窗口内鼠标位置 |
| **鼠标在窗口内** | <code><span style="color:#8e44ad">isMouseInWindow</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 鼠标是否在窗口内 |
| **鼠标按键** | <code><span style="color:#8e44ad">isMouseButtonPressed</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">button</span>) <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 鼠标按键是否按下 |
| **键盘按键** | <code><span style="color:#8e44ad">isKeyPressed</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">vkCode</span>) <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 键盘按键是否按下 |
| **修饰键** | <code><span style="color:#8e44ad">isShiftPressed</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">isCtrlPressed</span>() <span style="color:#2e86c1">const</span></code><br><code><span style="color:#8e44ad">isAltPressed</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 修饰键状态 |

## ⚙️ 高级窗口控制

提供窗口状态管理和高级特性控制。

| 控制类型 | 方法签名 | 功能说明 |
| :-------- | :--- | :--- |
| **窗口状态** | <code><span style="color:#8e44ad">maximize</span>()</code><br><code><span style="color:#8e44ad">minimize</span>()</code><br><code><span style="color:#8e44ad">restore</span>()</code> | 最大化/最小化/恢复窗口 |
| **窗口闪烁** | <code><span style="color:#8e44ad">flash</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">flashTitleBar</span>)</code> | 闪烁窗口吸引注意 |
| **可调整尺寸** | <code><span style="color:#8e44ad">setResizable</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">resizable</span>)</code> | 设置窗口是否可调整大小 |
| **置顶窗口** | <code><span style="color:#8e44ad">setAlwaysOnTop</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">onTop</span>)</code> | 设置窗口始终置顶 |
| **无边框** | <code><span style="color:#8e44ad">setBorderless</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">borderless</span>)</code> | 设置无边框窗口 |
| **全屏模式** | <code><span style="color:#8e44ad">setFullscreen</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">fullscreen</span>)</code> | 切换全屏模式 |
| **尺寸限制** | <code><span style="color:#8e44ad">setMinSize</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">minWidth</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">minHeight</span>)</code><br><code><span style="color:#8e44ad">setMaxSize</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">maxWidth</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">maxHeight</span>)</code> | 设置窗口最小/最大尺寸 |
| **标题栏按钮** | <code><span style="color:#8e44ad">setMinimizeButton</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">show</span>)</code><br><code><span style="color:#8e44ad">setMaximizeButton</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">show</span>)</code><br><code><span style="color:#8e44ad">setCloseButton</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">show</span>)</code> | 显示/隐藏标题栏按钮 |

## 🎭 外观与光标

控制窗口外观和光标样式。

| 控制类型 | 方法签名 | 功能说明 |
| :-------- | :--- | :--- |
| **窗口标题** | <code><span style="color:#8e44ad">setTitle</span>(<span style="color:#2e86c1">const</span> <span style="color:#2e86c1">char</span>* <span style="color:#e74c3c">title</span>)</code><br><code><span style="color:#8e44ad">setTitle</span>(<span style="color:#2e86c1">const</span> <span style="color:#2e86c1">wchar_t</span>* <span style="color:#e74c3c">title</span>)</code><br><code><span style="color:#8e44ad">getTitle</span>() <span style="color:#2e86c1">const</span></code> | 设置/获取窗口标题 |
| **自定义光标** | <code><span style="color:#8e44ad">setCursor</span>(<span style="color:#8e44ad">HCURSOR</span> <span style="color:#e74c3c">cursor</span>)</code> | 设置自定义光标 |
| **预设光标** | <code><span style="color:#8e44ad">setCursorDefault</span>()</code><br><code><span style="color:#8e44ad">setCursorWait</span>()</code><br><code><span style="color:#8e44ad">setCursorCross</span>()</code><br><code><span style="color:#8e44ad">setCursorHand</span>()</code><br><code><span style="color:#8e44ad">setCursorText</span>()</code> | 设置预设光标样式 |
| **光标控制** | <code><span style="color:#8e44ad">setCursorVisibility</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">visible</span>)</code><br><code><span style="color:#8e44ad">setCursorPosition</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">x</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">y</span>)</code> | 光标可见性和位置 |
| **窗口图标** | <code><span style="color:#8e44ad">setIcon</span>(<span style="color:#8e44ad">HICON</span> <span style="color:#e74c3c">icon</span>)</code><br><code><span style="color:#8e44ad">setIconFromResource</span>(<span style="color:#2e86c1">int</span> <span style="color:#e74c3c">resourceId</span>)</code> | 设置窗口图标 |

## 📋 剪贴板与文件拖放

剪贴板操作和文件拖放支持。

| 操作类型 | 方法签名 | 返回值 | 功能说明 |
| :-------- | :--- | :--- | :--- |
| **文本操作** | <code><span style="color:#8e44ad">setClipboardText</span>(<span style="color:#2e86c1">const</span> std::string& <span style="color:#e74c3c">text</span>)</code><br><code><span style="color:#8e44ad">getClipboardText</span>()</code> | <code><span style="color:#2e86c1">bool</span></code><br><code>std::string</code> | 剪贴板文本操作(ANSI) |
| **宽文本操作** | <code><span style="color:#8e44ad">setClipboardText</span>(<span style="color:#2e86c1">const</span> std::wstring& <span style="color:#e74c3c">text</span>)</code><br><code><span style="color:#8e44ad">getClipboardTextW</span>()</code> | <code><span style="color:#2e86c1">bool</span></code><br><code>std::wstring</code> | 剪贴板文本操作(Unicode) |
| **文本检测** | <code><span style="color:#8e44ad">hasClipboardText</span>() <span style="color:#2e86c1">const</span></code> | <code><span style="color:#2e86c1">bool</span></code> | 剪贴板是否有文本 |
| **文件操作** | <code><span style="color:#8e44ad">getClipboardFiles</span>()</code><br><code><span style="color:#8e44ad">hasClipboardFiles</span>() <span style="color:#2e86c1">const</span></code> | <code>std::vector&lt;std::string&gt;</code><br><code><span style="color:#2e86c1">bool</span></code> | 剪贴板文件操作 |
| **文件拖放** | <code><span style="color:#8e44ad">enableFileDrop</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">enable</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 启用/禁用文件拖放 |

## 🍔 菜单功能

窗口菜单的创建和管理。

| 功能 | 方法签名 | 返回值 | 功能说明 |
| :--- | :--- | :--- | :--- |
| **设置菜单** | <code><span style="color:#8e44ad">setMenu</span>(<span style="color:#8e44ad">HMENU</span> <span style="color:#e74c3c">menu</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 设置窗口菜单 |
| **创建菜单** | <code><span style="color:#8e44ad">createMenu</span>()</code><br><code><span style="color:#8e44ad">createPopupMenu</span>()</code> | <code><span style="color:#8e44ad">HMENU</span></code> | 创建主菜单/弹出菜单 |
| **添加菜单项** | <code><span style="color:#8e44ad">appendMenuItem</span>(<span style="color:#8e44ad">HMENU</span> <span style="color:#e74c3c">menu</span>, <span style="color:#2e86c1">const</span> <span style="color:#2e86c1">char</span>* <span style="color:#e74c3c">text</span>, <span style="color:#2e86c1">int</span> <span style="color:#e74c3c">id</span>, <span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">enabled</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 添加菜单项 |
| **添加分隔符** | <code><span style="color:#8e44ad">appendMenuSeparator</span>(<span style="color:#8e44ad">HMENU</span> <span style="color:#e74c3c">menu</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 添加菜单分隔符 |
| **添加子菜单** | <code><span style="color:#8e44ad">appendMenuPopup</span>(<span style="color:#8e44ad">HMENU</span> <span style="color:#e74c3c">menu</span>, <span style="color:#2e86c1">const</span> <span style="color:#2e86c1">char</span>* <span style="color:#e74c3c">text</span>, <span style="color:#8e44ad">HMENU</span> <span style="color:#e74c3c">popupMenu</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 添加弹出子菜单 |
| **销毁菜单** | <code><span style="color:#8e44ad">destroyMenu</span>(<span style="color:#8e44ad">HMENU</span> <span style="color:#e74c3c">menu</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 销毁菜单 |

## 📊 系统信息

获取显示器和系统相关信息。

| 信息类型 | 方法签名 | 返回值 | 功能说明 |
| :-------- | :--- | :--- | :--- |
| **屏幕尺寸** | <code><span style="color:#8e44ad">getScreenSize</span>()</code> | <code>std::pair&lt;<span style="color:#2e86c1">int</span>, <span style="color:#2e86c1">int</span>&gt;</code> | 获取屏幕分辨率 |
| **工作区尺寸** | <code><span style="color:#8e44ad">getWorkAreaSize</span>()</code> | <code>std::pair&lt;<span style="color:#2e86c1">int</span>, <span style="color:#2e86c1">int</span>&gt;</code> | 获取工作区尺寸(排除任务栏) |
| **DPI缩放** | <code><span style="color:#8e44ad">getDpiScale</span>()</code> | <code><span style="color:#2e86c1">double</span></code> | 获取系统DPI缩放比例 |
| **全局鼠标** | <code><span style="color:#8e44ad">getGlobalMousePosition</span>()</code> | <code>std::pair&lt;<span style="color:#2e86c1">int</span>, <span style="color:#2e86c1">int</span>&gt;</code> | 获取全局鼠标位置 |
| **鼠标捕获** | <code><span style="color:#8e44ad">setMouseCapture</span>(<span style="color:#2e86c1">bool</span> <span style="color:#e74c3c">capture</span>)</code> | <code><span style="color:#8e44ad">Window</span>&</code> | 设置鼠标捕获 |


## 💡 使用示例
```cpp
#include "pa2d.h"

int main() {
    // 创建窗口
    pa2d::Window window(800, 600, "My Application");
    
    // 设置事件回调
    window.onKey([](const pa2d::KeyEvent& e) {
        if (e.keyCode == VK_ESCAPE && e.pressed)
            window.close();
    });
    
    window.onMouse([](const pa2d::MouseEvent& e) {
        if (e.button == 0 && e.pressed)
            printf("Mouse clicked at (%d, %d)\n", e.x, e.y);
    });
    
    // 创建画布并绘制
    pa2d::Canvas canvas(400, 300);
    canvas.rect(50, 50, 300, 200, 0xFFFF0000, 0xFF000000, 2.0f);
    canvas.text("Hello World!", 150, 150, 0xFF000000);
    
    // 主循环
    while (window.isOpen()) {
        // 渲染到窗口
        window.renderCentered(canvas);
        
        // 处理消息
        // (消息循环在内部线程中自动处理)
    }
    
    return 0;
}
```