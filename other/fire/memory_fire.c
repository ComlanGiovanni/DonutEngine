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

/**
 * @brief ASCII Fire Animation
 *
 * Creates an ASCII-based fire animation in the terminal.
 * The algorithm works by:
 * - Maintaining a buffer of "heat" values
 * - Calculating new values by averaging neighboring cells
 * - Randomly generating heat at the bottom as the fire source
 * - Mapping heat intensity values to ASCII characters for display
 *
 * The animation runs in an infinite loop with a 20ms delay between frames.
 * The display uses ANSI escape sequences to clear the screen between frames.
 *
 * @return int Program exit status (never reached due to infinite loop)
 */
int main()
{
	const char	*intensity = " .:*#$H@";
	int			fire[BUFFER_SIZE] = {0};
	int			i;
	for (;;)
	{
		printf("\x1b[H");

		for (i = 1; i < BUFFER_SIZE; i++)
		{
			if (i < CALCULATION_ZONE)
				fire[i] = (fire[i + WIDTH - 1] + fire[i + WIDTH] + fire[i] + fire[i - 1] + fire[i + WIDTH + 1]) / 5;
			else
				fire[i] = (rand() % 4) ? 0 : 512;
			if (i < DISPLAY_ZONE)
			{
				if ((i % WIDTH) == WIDTH - 1)
					putchar('\n');
				else
					putchar(intensity[fire[i] >> 5]);
			}
		}
		usleep(20000);
	}
	return 0;
}
