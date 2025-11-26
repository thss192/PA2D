#include "pa2d.h"
#include <chrono>

using namespace pa2d;

int main() {
    Window window(600, 400, "PA2D Clock Demo");

    // Canvas objects
    Canvas canvas(600, 400);      // For dynamic drawing (hands animation)
    Canvas background(600, 400);  // For static elements (dial, marks, numbers)

    // Main clock face circle
    Circle clockFace(300, 200, 120);

    background.clear(White);

    // Draw clock marks and numbers
    for (int i = 5; i < 65; ++i) {
        // Create mark line: from center, rotated to position
        Ray mark = Ray(clockFace, clockFace.radius(), 90.0f)
            .toEnd()                       // Move start to end
            .length(-10)                   // Set length to -10px (inward)
            .rotate(i * 6.0f, clockFace);  // Rotate i*6 degrees

        background.draw(mark, i % 5 ? "#ff787878"_stroke + 1_w : "#ff464646"_stroke + 3_w);
        if (i % 5 == 0) {
            Point pos = mark.length(30).end(); // Extend to 30px for number position
            background.textCentered(std::to_string(i / 5), pos.x, pos.y, 0xff3c3c64, 16);
        }
    }

    background.draw(clockFace, "#ff5a5a5a"_stroke + 4_w); // Outer border
    background.textCentered("PA2D Clock", clockFace.x(), 50, 0xff505078, 20, "Microsoft YaHei", FontStyle::Bold);

    // Clock hands and styles
    std::vector<Ray> hands = {
        Ray(clockFace, clockFace.radius() * 0.5f),   // Hour hand (shortest)
        Ray(clockFace, clockFace.radius() * 0.7f),   // Minute hand
        Ray(clockFace, clockFace.radius() * 0.85f)   // Second hand (longest)
    };
    std::vector<Style> handStyles = {
        "#ff1e1e1e"_stroke + 8_w,           // Hour hand style
        "#ff505050"_stroke + 5_w + 0.8_o,   // Minute hand style  
        "#ffdc0000"_stroke + 2_w            // Second hand style
    };

    window.show();

    // Main render loop
    while (window.isOpen()) {
        // Get current system time
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
        localtime_s(&tm, &t);

        // Format time as HH:MM:SS string
        char timeStr[9];
        sprintf_s(timeStr, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

        // Update hand angles based on current time
        hands[0].angle(90.0f - (tm.tm_hour % 12 * 30.0f + tm.tm_min * 0.5f));
        hands[1].angle(90.0f - (tm.tm_min * 6.0f + tm.tm_sec * 0.1f));
        hands[2].angle(90.0f - tm.tm_sec * 6.0f);

        // Draw frame
        canvas.copyBlend(background)      // Copy static background
            .drawBatch(hands, handStyles) // Draw clock hands
            .draw(Circle(300, 200, 4), "#ffffffff"_fill + "#ff1e1e1e"_stroke + 4.5_w) // Center dot
            .textCentered(timeStr, clockFace.x(), clockFace.y() + clockFace.radius() + 30, 0xff505078, 20); // Time text

        window.renderCentered(canvas);
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    return 0;
}
