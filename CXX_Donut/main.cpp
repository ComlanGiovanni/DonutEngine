#include "ft_donut.hpp"
#include <chrono>
#include <thread>

int main() {
    using namespace DonutAnimation;

    Donut donut;
    clearScreen();

    // Animation loop with consistent frame rate
    const std::chrono::milliseconds frame_delay(30); // ~33 FPS

    while (true) {
        auto start_time = std::chrono::steady_clock::now();

        donut.renderFrame();
        donut.printFrame();
        donut.updateRotation();

        // Control frame rate
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);

        if (elapsed < frame_delay) {
            std::this_thread::sleep_for(frame_delay - elapsed);
        }
    }

    return 0;
}
