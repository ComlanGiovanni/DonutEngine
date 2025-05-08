#pragma once

#include <cmath>
#include <iostream>
#include <array>
#include <string>

namespace DonutAnimation {

// Constants
constexpr int SCREEN_WIDTH = 80;
constexpr int SCREEN_HEIGHT = 22;
constexpr int BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;
constexpr double FULL_CIRCLE = 6.28;
constexpr double DONUT_DIST = 2.0;
constexpr double VIEW_DIST = 5.0;

/**
 * @brief Stores rotation angles for the donut
 */
class Rotation {
public:
    Rotation(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double x;  // Rotation around X axis
    double y;  // Rotation around Y axis
};

/**
 * @brief Stores the output and depth buffers
 */
class Buffer {
public:
    Buffer() {
        output.fill(' ');
        depth.fill(0.0f);
    }

    void clear() {
        output.fill(' ');
        depth.fill(0.0f);
    }

    std::array<char, BUFFER_SIZE> output;  // ASCII character screen buffer
    std::array<float, BUFFER_SIZE> depth;   // Z-buffer for depth testing
};

/**
 * @brief Stores rendering parameters
 */
class RenderConfig {
public:
    RenderConfig(
        const std::string& shades = ".,-~:;=!*#$@",
        double tube_step = 0.02,
        double main_circle_step = 0.07
    ) : shades(shades), tube_step(tube_step), main_circle_step(main_circle_step) {}

    std::string shades;        // ASCII characters for different light levels
    double tube_step;         // Angular step for tube cross-section
    double main_circle_step;  // Angular step for main circle
};

/**
 * @brief Main donut animation class
 */
class Donut {
public:
    Donut();

    // Core animation methods
    void renderFrame();
    void printFrame() const;
    void updateRotation();

private:
    // Helper methods
    int calculatePosition(double tube_angle, double main_angle, float& depth) const;
    int calculateLight(double tube_angle, double main_angle) const;
    void renderPoint(double tube_angle, double main_angle);

    // Instance data
    Rotation rot;
    Buffer buf;
    RenderConfig render;
};

// Utility functions
void cursorHome();
void clearScreen();

} // namespace DonutAnimation
