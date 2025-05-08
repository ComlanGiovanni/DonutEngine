#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Definition of dimensions
#define WIDTH 80
#define HEIGHT 25
#define BUFFER_SIZE (WIDTH * HEIGHT + WIDTH)

// Display area and fire generation area
#define DISPLAY_ZONE (WIDTH * 23)       // 1840
#define CALCULATION_ZONE (WIDTH * 25)   // 2000

int main() {
    // Array to store "heat" values
    int fire[BUFFER_SIZE] = {0};
    int i;

    // Characters used to represent different fire intensities
    const char *intensity = " .:*#$H@";

    // Main animation loop
    for (;;) {
        // Clear screen (ANSI escape sequence)
        printf("\x1b[H");

        // Calculate and display each point
        for (i = 1; i < BUFFER_SIZE; i++) {
            // Update "heat" values
            if (i < CALCULATION_ZONE) {
                // Calculate new value as average of neighboring cells
                fire[i] = (fire[i + WIDTH - 1] +  // Bottom left diagonal
                           fire[i + WIDTH] +      // Bottom
                           fire[i] +              // Current cell
                           fire[i - 1] +          // Left
                           fire[i + WIDTH + 1])   // Bottom right diagonal
                           / 5;
            } else {
                // Randomly generate the "fire" source at the bottom
                fire[i] = (rand() % 4) ? 0 : 512;
            }

            // Display only the visible part (without the last line used as source)
            if (i < DISPLAY_ZONE) {
                // At the end of each line, add a line break
                if ((i % WIDTH) == WIDTH - 1) {
                    putchar('\n');
                } else {
                    // Otherwise display the character corresponding to the intensity
                    putchar(intensity[fire[i] >> 5]);
                }
            }
        }

        // Pause to slow down the animation (20 ms)
        usleep(20000);
    }

    return 0;
}
