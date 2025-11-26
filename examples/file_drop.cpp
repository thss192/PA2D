#include "pa2d.h"
#include <iostream>

using namespace pa2d;

int main() {
    Window window(800, 600, "File Drop Demo");
    Canvas canvas(800, 600);

    // Set file drop callback
    window.onFileDrop([](const std::vector<std::string>& files) {
        std::cout << "Received " << files.size() << " files:" << std::endl;
        for (const auto& file : files) {
            std::cout << "  - " << file << std::endl;
        }
    });
    
    window.show();

    // Main loop
    while (window.isOpen()) {
        canvas.clear(White)
            .text(L"Drag files here", 300, 300, Black, 24);
        window.render(canvas);
        Sleep(60);
    }

    return 0;
}
