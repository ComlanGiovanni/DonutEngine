#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * ASCII Fire Animation - Simplified Version
 *
 * A condensed but readable implementation of the fire effect.
 * Easy to memorize while preserving the core algorithm.
 */
int main() {
    // Constants
    int w = 80;           // Screen width
    int h = 25;           // Screen height
    int disp = w * 23;    // Display zone
    int calc = w * h;     // Calculation zone
    char *chars = " .:*#$H@";  // Heat intensity levels

    // Fire buffer
    int fire[2080] = {0};
    int i;

    // Main loop
    while (1) {
        // Home cursor
        printf("\x1b[H");

        // Process each position
        for (i = 1; i < w * h + w; i++) {
            // Update heat values
            if (i < calc) {
                // Heat diffusion from 5 points
                fire[i] = (fire[i + w - 1] + fire[i + w] +
                          fire[i] + fire[i - 1] + fire[i + w + 1]) / 5;
            } else {
                // Random fire source (25% chance of high heat)
                fire[i] = (rand() % 4) ? 0 : 512;
            }

            // Display
            if (i < disp) {
                if ((i % w) == w - 1)
                    putchar('\n');
                else
                    putchar(chars[fire[i] >> 5]);
            }
        }

        // Frame delay
        usleep(20000);
    }
}
