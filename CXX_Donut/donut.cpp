#include "ft_donut.hpp"

namespace DonutAnimation {

/**
 * @brief Constructor - Initialize the donut animation state
 */
Donut::Donut() : rot(0.0, 0.0) {
    // Everything initialized by default constructors
}

/**
 * @brief Calculate the projected 2D position of a 3D point
 */
int Donut::calculatePosition(double tube_angle, double main_angle, float& depth) const {
    double radius = std::cos(main_angle) + DONUT_DIST;

    depth = 1.0 / (std::sin(tube_angle) * radius * std::sin(rot.x)
            + std::sin(main_angle) * std::cos(rot.x) + VIEW_DIST);

    double temp = std::sin(tube_angle) * radius * std::cos(rot.x)
                - std::sin(main_angle) * std::sin(rot.x);

    double x_proj = 40 + 30 * depth * (std::cos(tube_angle) * radius * std::cos(rot.y)
                 - temp * std::sin(rot.y));
    double y_proj = 12 + 15 * depth * (std::cos(tube_angle) * radius * std::sin(rot.y)
                 + temp * std::cos(rot.y));

    if (y_proj > 0 && y_proj < SCREEN_HEIGHT
        && x_proj > 0 && x_proj < SCREEN_WIDTH) {
        return static_cast<int>(x_proj) + SCREEN_WIDTH * static_cast<int>(y_proj);
    }

    return -1;
}

/**
 * @brief Calculate lighting value for a point on the donut
 */
int Donut::calculateLight(double tube_angle, double main_angle) const {
    double light = 8.0 * ((std::sin(main_angle) * std::sin(rot.x)
                    - std::sin(tube_angle) * std::cos(main_angle) * std::cos(rot.x))
                * std::cos(rot.y) - std::sin(tube_angle) * std::cos(main_angle) * std::sin(rot.x)
                - std::sin(main_angle) * std::cos(rot.x)
                - std::cos(tube_angle) * std::cos(main_angle) * std::sin(rot.y));

    int light_level = static_cast<int>(light);
    return (light_level < 0) ? 0 : light_level;
}

/**
 * @brief Render a single point on the donut
 */
void Donut::renderPoint(double tube_angle, double main_angle) {
    float point_depth;
    int position = calculatePosition(tube_angle, main_angle, point_depth);

    if (position != -1) {
        int light = calculateLight(tube_angle, main_angle);

        if (point_depth > buf.depth[position]) {
            buf.depth[position] = point_depth;
            buf.output[position] = render.shades[light];
        }
    }
}

/**
 * @brief Render a complete frame of the donut
 */
void Donut::renderFrame() {
    buf.clear();

    // Outer loop: iterate around the main circle of the torus
    for (double main_angle = 0; main_angle < FULL_CIRCLE; main_angle += render.main_circle_step) {
        // Inner loop: iterate around the tube cross-section
        for (double tube_angle = 0; tube_angle < FULL_CIRCLE; tube_angle += render.tube_step) {
            renderPoint(tube_angle, main_angle);
        }
    }
}

/**
 * @brief Print the current frame to the terminal
 */
void Donut::printFrame() const {
    cursorHome();

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (i % SCREEN_WIDTH == 0 && i > 0) {
            std::cout << '\n';
        } else {
            std::cout << buf.output[i];
        }
    }
}

/**
 * @brief Update rotation angles for animation
 */
void Donut::updateRotation() {
    rot.x += 0.04; // X rotation speed
    rot.y += 0.02; // Y rotation speed
}

/**
 * @brief Move cursor to home position (top-left corner)
 */
void cursorHome() {
    std::cout << "\x1b[H";
}

/**
 * @brief Clear the terminal screen
 */
void clearScreen() {
    std::cout << "\x1b[2J";
}

} // namespace DonutAnimation
