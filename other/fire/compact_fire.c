#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Super compact yet readable ASCII fire animation
int main()
{
	int fire[2080] = {0}, i, w = 80;
	char *ch = " .:*#$H@";

	for(;;)
	{
		printf("\x1b[H");  // Home cursor
		for(i = 1; i < 2080; i++)
		{
			fire[i] = i < 2000
				? (fire[i+w-1] + fire[i+w] + fire[i] + fire[i-1] + fire[i+w+1]) / 5
				: (rand() % 4 ? 0 : 512);
			// Display if in visible area (top 23 rows)
			if(i < 1840) {
				putchar(i % w == w-1
					? '\n'               // End of row
					: ch[fire[i] >> 5]); // Character based on heat
			}
		}
		usleep(20000);// 20ms delay
	}
}
