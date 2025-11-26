#include "pa2d.h"
pa2d::Window window(600, 400, "Draw a circle"); // Create window object - 创建窗口对象
pa2d::Canvas canvas(600, 400);                  // Create canvas object - 创建画布对象

int main() {
    window.show(); // Display the window - 显示窗口
    canvas.circle(200, 200, 50, None, Red, 3); // Draw circle on canvas - 在画布上绘制圆
    
    while (window.isOpen()) {
        window.render(canvas); // Render canvas to window - 将画布渲染到窗口
    }
    return 0;
}
