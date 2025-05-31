#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    // Screen setup
    char screen[22][80];  // 22 rows, 80 columns (like terminal)

    printf("Simple Donut - Step by Step\n\n");

    // STEP 1: Just make a circle first
    printf("STEP 1: Making a simple circle\n");

    // Clear screen
    for(int row = 0; row < 22; row++) {
        for(int col = 0; col < 80; col++) {
            screen[row][col] = ' ';  // Fill with spaces
        }
    }

    // Draw a circle using simple math
    for(float angle = 0; angle < 6.28; angle += 0.3) {  // 6.28 = 2*PI (full circle)
        int x = 40 + 20 * cos(angle);  // Center at column 40, radius 20
        int y = 11 + 8 * sin(angle);   // Center at row 11, radius 8

        // Make sure we're within screen bounds
        if(x >= 0 && x < 80 && y >= 0 && y < 22) {
            screen[y][x] = '*';  // Put a star there
        }
    }

    // Print the circle
    for(int row = 0; row < 22; row++) {
        for(int col = 0; col < 80; col++) {
            putchar(screen[row][col]);
        }
        putchar('\n');
    }

    printf("\nPress Enter to continue to STEP 2...");
    getchar();

    // STEP 2: Now make it look 3D with different characters
    printf("\nSTEP 2: Making it look 3D with shading\n");

    // Clear screen again
    for(int row = 0; row < 22; row++) {
        for(int col = 0; col < 80; col++) {
            screen[row][col] = ' ';
        }
    }

    // Same circle, but with "lighting"
    char shades[] = ".,-*#@";  // Different brightness levels

    for(float angle = 0; angle < 6.28; angle += 0.2) {
        int x = 40 + 20 * cos(angle);
        int y = 11 + 8 * sin(angle);

        if(x >= 0 && x < 80 && y >= 0 && y < 22) {
            // Simple "lighting" - left side darker, right side brighter
            int brightness = (int)(2.5 * (cos(angle) + 1));  // 0 to 5
            if(brightness > 4) brightness = 4;
            screen[y][x] = shades[brightness];
        }
    }

    // Print the "3D" circle
    for(int row = 0; row < 22; row++) {
        for(int col = 0; col < 80; col++) {
            putchar(screen[row][col]);
        }
        putchar('\n');
    }

    printf("\nPress Enter to continue to STEP 3...");
    getchar();

    // STEP 3: Make it a donut (torus) shape
    printf("\nSTEP 3: Making it a donut shape\n");

    // Clear screen
    for(int row = 0; row < 22; row++) {
        for(int col = 0; col < 80; col++) {
            screen[row][col] = ' ';
        }
    }

    // Now we make TWO circles:
    // - One small circle (the tube)
    // - That goes around a big circle (the main ring)

    for(float big_angle = 0; big_angle < 6.28; big_angle += 0.4) {      // Around the main ring
        for(float small_angle = 0; small_angle < 6.28; small_angle += 0.8) {  // Around the tube

            // First, make the tube (small circle)
            float tube_x = 2 * cos(small_angle);  // Small circle, radius 2
            float tube_y = 1 * sin(small_angle);  // Flattened vertically

            // Then move this tube around the big circle
            float final_x = (15 + tube_x) * cos(big_angle);  // 15 = main ring radius
            float final_y = (15 + tube_x) * sin(big_angle);
            float final_z = tube_y;  // Height of the tube

            // Convert 3D to 2D (simple projection)
            int screen_x = 40 + (int)(final_x * 0.8);  // Scale and center
            int screen_y = 11 + (int)(final_y * 0.4) + (int)(final_z * 0.8);

            if(screen_x >= 0 && screen_x < 80 && screen_y >= 0 && screen_y < 22) {
                screen[screen_y][screen_x] = '#';
            }
        }
    }

    // Print the donut
    for(int row = 0; row < 22; row++) {
        for(int col = 0; col < 80; col++) {
            putchar(screen[row][col]);
        }
        putchar('\n');
    }

    printf("\nThis is the basic donut shape!\n");
    printf("The real code does this same thing but:\n");
    printf("- With much finer detail (smaller steps)\n");
    printf("- With proper 3D rotation\n");
    printf("- With realistic lighting\n");
    printf("- With animation (changing rotation over time)\n");
    printf("- With z-buffering (so front parts hide back parts)\n");

    return 0;
}
