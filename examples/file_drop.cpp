// PA2D 文件拖放功能示例
// 版本：1.0.0.beta1 配套示例
//
// 功能说明：
// 1. 演示PA2D的文件拖放支持
// 2. 展示如何注册和处理文件拖放事件
// 3. 展示回调函数的使用和文件路径处理
// 4. 演示控制台输出与图形界面的结合

#include "pa2d.h"
#include <windows.h>
#include <iostream>

using namespace pa2d;

int main() {
    // ==================== 窗口和画布初始化 ====================
    Window window(800, 600, "文件拖放演示 - File Drop Demo");
    Canvas canvas(800, 600);

    // ==================== 文件拖放回调设置 ====================
    // 注册文件拖放事件回调（使用lambda表达式）
    window.onFileDrop([](const std::vector<std::string>& files) {
        // 当用户拖放文件到窗口时，此回调会被触发
        std::cout << "收到 " << files.size() << " 个文件：" << std::endl;

        // 遍历并输出所有文件路径
        for (const auto& file : files) {
            std::cout << "  - " << file << std::endl;
        }

        });

    // ==================== 窗口显示 ====================
    window.show();  // 显示窗口（文件拖放功能自动启用）

    // ==================== 主渲染循环 ====================
    while (window.isOpen()) {
        // 清空画布并绘制提示信息
        canvas.clear(White)  // 白色背景
            .text(300, 280, L"拖放文件到这里", 24, Black)  // 中文提示
            .text(300, 310, L"Drag files here", 20, Black);  // 英文提示

        // 渲染到窗口
        window.render(canvas);

        // 控制渲染频率（约16.67 FPS）
        Sleep(60);
    }

    return 0;
}

// 示例说明：
// 1. 文件拖放功能：
//    - PA2D自动处理Windows文件拖放消息
//    - 用户只需调用onFileDrop()注册回调函数
//    - 支持多文件同时拖放（files向量包含所有文件路径）
//
// 2. 回调函数设计：
//    - 使用lambda表达式定义内联回调
//    - 回调接收std::vector<std::string>，包含完整的文件路径
//
// 3. 文件路径格式：
//    - Windows系统：完整路径，如"C:\Users\Name\Documents\file.txt"
//    - 支持长路径和Unicode文件名
//    - 路径使用反斜杠分隔符
//
// 4. 实际应用扩展：
//    - 图像查看器：拖放图片文件并显示
//    - 批量处理器：拖放多个文件进行批量操作
//    - 文件管理器：拖放实现文件移动/复制
//
// 使用步骤：
// 1. 编译运行此程序
// 2. 从资源管理器选择文件
// 3. 拖放到程序窗口
// 4. 查看控制台输出的文件路径
