#include <string.h>  // For memset function
#include <stdio.h>   // For printf and putchar functions
#include <math.h>    // For sin() and cos() trigonometric functions
// #include <stdbool.h> or while (true)
#include <stdlib.h> // system("clear"); or printf("\x1b[2J");
//#include <curses.h> initscr(); move(0, 0); refresh();
#include <unistd.h>  // For usleep function

/*
	Full circle in radians (2π) 3.14159265358979323846
	Screen dimensions width 80 height 22
	buffer size 1760 80 x 22 [width x heigh]
	Clear the terminal screen using ANSI escape code printf("\x1b[2J");
	// z[] Z-buffer (depth buffer)
	// b[] Screen buffer (characters to display)
*/

int main()
{
	const char *SHADE = ".,-~:;=!*#$@";
	const int W = 80, H = 22, S = W * H, INTENSITY = 8, \
		COL_CENTER = 40, ROW_CENTER = 12, COL_SCALE = 30, ROW_SCALE_Y = 15;
	const float PI2 = 6.28, CAM_DIST = 5, \
		TORUS_SIZE = 3, RING_STEP = 0.07, TUBE_STEP = 0.02;
	float pitch = 0, yaw = 0;
	float z[S];
	char b[S];
	system("clear");
	while(";;")
	{
		memset(b, ' ', 1760);
		memset(z, 0, sizeof(z));
		for(float ring = 0; ring < PI2; ring += RING_STEP)
		{
			for(float tube = 0; tube < PI2; tube += TUBE_STEP)
			{
				float cosTube = cos(tube), sinTube = sin(tube);
				float cosRing = cos(ring), sinRing = sin(ring);
				float cosPitch = cos(pitch), sinPitch = sin(pitch);
				float cosYaw = cos(yaw), sinYaw = sin(yaw);

				float radus = cosRing + TORUS_SIZE;
				float camera = 1 / (sinTube * radus * sinPitch + sinRing * cosPitch + CAM_DIST);

				float y3d = sinTube * radus * cosPitch - sinRing * sinPitch;
				int col = COL_CENTER + COL_SCALE * camera * (cosTube * radus * cosYaw - y3d * sinYaw);
				int row = ROW_CENTER + ROW_SCALE_Y * camera * (cosTube * radus * sinYaw + y3d * cosYaw);

				int pos = col + W * row;

				int bright = INTENSITY * ((sinRing * sinPitch - sinTube * cosRing * cosPitch) * cosYaw
								- sinTube * cosRing * sinPitch - sinRing * cosPitch - cosTube * cosRing * sinYaw);

				if(row > 0 && row < H && col > 0 && col < W && camera > z[pos])
				{
					z[pos] = camera;
					b[pos] = SHADE[bright > 0 ? bright : 0];
				}
			}
		}
		printf("\x1b[H");
		for(int index = 0; index < S; index++)
			putchar(index % W ? b[index] : '\n');
		pitch += 0.004;
		yaw += 0.002;
		//usleep(16667);
	}
	return (EXIT_SUCCESS);
}
