#include "pa2d.h"
using namespace pa2d;

Window w_1(600, 400, "Circle Window");
Window w_2(600, 400, "Rectangle Window");

void keyEvent(KeyEvent key) {
    if (key.keyCode == 32 && key.pressed) {  // Space bar to toggle windows
        if (w_1.isVisible()) w_1.hide();
        else w_1.show().focus();
        
        if (w_2.isVisible()) w_2.hide();
        else w_2.show().focus();
    }
}

int main() {
    Canvas canvas1(600, 400), canvas2(600, 400);

    // Initialize canvas content
    canvas1.clear(Black)
        .circle(200, 200, 50, None, Red, 5)
        .textCentered(L"Press SPACE to toggle", 300, 300, White, 16);
    canvas2.clear(White)
        .rect(100, 100, 200, 100, None, Blue, 5)
        .textCentered(L"Press SPACE to toggle", 300, 300, Black, 16);

    // Window setup
    w_1.setPosition(100, 100).onKey(keyEvent).show().focus();
    w_2.setPosition(750, 100).onKey(keyEvent);

    // Main loop
    while (w_1.isOpen() && w_2.isOpen()) {
        if (w_1.isVisible()) w_1.render(canvas1);
        if (w_2.isVisible()) w_2.render(canvas2);
        Sleep(16);  // ~60 FPS
    }

    return 0;
}
