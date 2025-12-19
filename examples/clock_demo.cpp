// PA2D 时钟示例 - 展示PA2D图形库的实时渲染能力
// 版本：1.0.0.beta1 配套示例
// 
// 功能说明：
// 1. 创建一个模拟时钟，显示实时时间
// 2. 使用PA2D的几何图形(Ray)绘制表盘刻度和指针
// 3. 演示实时动画、图形变换和文本渲染
// 4. 展示Canvas复制、渲染和窗口事件处理

#include "pa2d.h"
#include <windows.h>
#include <iostream>

using namespace pa2d;

// 时钟常量定义
const float ClockX(300), ClockY(200), Radius(120);  // 时钟中心位置和半径
Window window(600, 400, "PA2D Clock");              // 创建600x400窗口
Canvas canvas(600, 400),                           // 主画布（每帧更新）
background(600, 400, 0xffffffff);           // 背景画布（静态表盘，白色背景）

int main() {
    // ==================== 初始化静态表盘 ====================
    // 绘制60个刻度（每6度一个）
    for (int i = 5; i < 65; ++i) {
        // 创建刻度线段（从表盘边缘向内10像素）
        Ray mark(ClockX, ClockY - Radius, ClockX, ClockY - Radius + 10);

        // 旋转到对应位置：i*6度（一圈360度/60刻度=6度）
        background.draw(mark.rotate(i * 6.0f, ClockX, ClockY),
            i % 5 ? "#ff787878"_stroke + 1_w      // 小刻度：灰色1像素
            : "#ff464646"_stroke + 3_w);    // 大刻度：深灰色3像素

        // 每5个刻度（小时位置）添加数字
        if (i % 5 == 0) {
            auto pos = mark.stretch(3).end();  // 拉伸刻度获取数字位置
            background.textCentered(std::to_string(i / 5),  // 小时数字（1-12）
                pos.x, pos.y,
                0xff3c3c64);             // 深蓝色文字
        }
    }

    // 绘制表盘外圈
    background.circle(ClockX, ClockY, Radius,
        None_fill + 0xff5a5a5a_stroke + 4_w);

    // 添加标题
    background.textCentered("PA2D Clock", ClockX, 50,
        0xff505078, 20, "Microsoft YaHei", FontStyle::Bold);

    // ==================== 主循环（实时动画） ====================
    window.show();  // 显示窗口

    while (window.isOpen()) {
        // 获取当前系统时间
        SYSTEMTIME st;
        GetLocalTime(&st);

        // 仅在秒数变化时重绘（避免每帧都重绘）
        static int lastSecond = -1;
        if (st.wSecond != std::exchange(lastSecond, st.wSecond)) {
            // 格式化时间字符串 HH:MM:SS
            char timeStr[9];
            sprintf_s(timeStr, "%02d:%02d:%02d",
                st.wHour, st.wMinute, st.wSecond);

            // 创建基础指针（从中心指向12点方向，长度0.5倍半径）
            Ray hand(ClockX, ClockY, ClockX, ClockY - Radius * 0.5f);

            // 计算各指针角度：
            // 时针：每小时30度 + 每分钟0.5度
            float h_angle = st.wHour % 12 * 30.0f + st.wMinute * 0.5f;
            // 分针：每分钟6度 + 每秒0.1度（平滑移动）
            float m_angle = st.wMinute * 6.0f + st.wSecond * 0.1f;
            // 秒针：每秒6度
            float s_angle = st.wSecond * 6.0f;

            // 绘制动态部分（使用链式调用）
            canvas.copy(background)  // 复制静态表盘
                .draw(Ray(hand).spin(h_angle), "#ff1e1e1e"_stroke + 8_w)   // 时针
                .draw(Ray(hand).stretch(1.4).spin(m_angle), "#ff505050"_stroke + 5_w)  // 分针
                .draw(Ray(hand).stretch(1.7).spin(s_angle), "#ffdc0000"_stroke + 2_w)  // 秒针（红色）
                .circle(ClockX, ClockY, 4, White_fill + 0xff1e1e1e_stroke + 4.5_w)  // 中心点
                .textCentered(timeStr, ClockX, ClockY + Radius + 30,  // 底部时间显示
                    0xff505078, 20);
        }

        // 渲染到窗口（居中显示）
        window.renderCentered(canvas);

        // 控制帧率（约60FPS）
        Sleep(16);
    }

    return 0;
}
