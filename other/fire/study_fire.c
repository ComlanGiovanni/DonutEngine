#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Dimensions constants
#define WIDTH 80          // Width of the screen
#define HEIGHT 25         // Height of the screen
#define BUFFER_SIZE (WIDTH * HEIGHT + WIDTH)

// Zones for display and calculation
#define DISPLAY_HEIGHT 23                     // Number of rows to display
#define DISPLAY_ZONE (WIDTH * DISPLAY_HEIGHT) // Total cells in display
#define CALCULATION_ZONE (WIDTH * HEIGHT)     // Zone for fire propagation calculation
#define FIRE_SOURCE_ROW (HEIGHT)              // Bottom row index for fire source

// ASCII intensity levels
#define MAX_INTENSITY 7                       // Maximum intensity index
#define INTENSITY_DIVISOR 5                   // Divisor for intensity calculation

/**
 * @brief ASCII Fire Animation
 *
 * Creates a mesmerizing ASCII-based fire animation in the terminal.
 *
 * Algorithm explanation:
 * 1. Heat propagation:
 *    - Each cell's heat is calculated from its neighbors below
 *    - We average adjacent cells (bottom left, bottom, current, left, bottom right)
 *    - This simulates heat rising and spreading, creating fluid motion
 *
 * 2. Fire source generation:
 *    - Random heat is generated at the bottom row
 *    - Occasionally creates "sparks" (value 512) for realistic flame variation
 *    - Most positions (75%) remain cool (value 0) to create gaps in the fire
 *
 * 3. Heat to ASCII conversion:
 *    - Heat values (0-512) are mapped to ASCII characters
 *    - Division by 32 (bit shift >> 5) converts to 8 intensity levels
 *    - Characters from space (cool) to @ (hottest) represent the flame
 *
 * 4. Display technique:
 *    - ANSI escape sequence \x1b[H resets cursor to home position
 *    - Characters are printed directly to terminal without buffer
 *    - Line breaks are inserted at the end of each row
 *    - Only the top DISPLAY_HEIGHT rows are shown (the source is hidden)
 *
 * Visual effect:
 * The result is an upward-flowing fire effect where flames dance,
 * brighten, dim and spread realistically, creating a hypnotic pattern
 * that resembles actual fire behavior.
 *
 * @return int Program exit status (never reached due to infinite loop)
 */
int main()
{
	// Array of ASCII characters representing different heat intensities
	const char *intensity_chars = " .:*#$H@";

	// Buffer to store heat values for each position
	int fire[BUFFER_SIZE] = {0};

	// Position index
	int i;

	// Animation loop
	for (;;)
	{
		// Move cursor to home position (top-left corner)
		printf("\x1b[H");

		// Process each cell in the buffer
		for (i = 1; i < BUFFER_SIZE; i++)
		{
			// Calculate fire propagation for all except the source row
			if (i < CALCULATION_ZONE)
			{
				// Average the heat from 5 positions (current + neighbors)
				fire[i] = (
					fire[i + WIDTH - 1] +  // bottom-left
					fire[i + WIDTH] +      // directly below
					fire[i] +              // current position
					fire[i - 1] +          // left
					fire[i + WIDTH + 1]    // bottom-right
				) / INTENSITY_DIVISOR;     // average heat
			}
			// Generate random fire source at the bottom
			else
			{
				// 25% chance of high heat (spark), otherwise no heat
				fire[i] = (rand() % 4) ? 0 : 512;
			}

			// Display only within the visible zone
			if (i < DISPLAY_ZONE)
			{
				// Add newline at the end of each row
				if ((i % WIDTH) == WIDTH - 1)
					putchar('\n');
				// Display the appropriate intensity character
				else
					putchar(intensity_chars[fire[i] >> 5]); // Divide by 32 to get intensity level
			}
		}

		// Pause between frames (20ms)
		usleep(20000);
	}

	return 0;
}
