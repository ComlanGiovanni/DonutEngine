#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
	const char *SHADE = ".,-~:;=!*#$@";
	const int W = 80, H = 22;
	const int S = W * H;
	const int INTENSITY = 8;
	const int COL_CENTER = 40, ROW_CENTER = 12;
	const int COL_SCALE = 30, ROW_SCALE = 15;
	const float PI2 = 6.28;
	const float CAM_DIST = 5;
	const float TORUS_SIZE = 3;
	const float RING_STEP = 0.07, TUBE_STEP = 0.02;
	float pitch = 0, yaw = 0;
	float z[S];
	char b[S];
	printf("\x1b[2J");
	while (true)
	{
		memset(b, ' ', S);
		memset(z, 0, sizeof(z));
		for (float ring = 0; ring < PI2; ring += RING_STEP)
		{
			for (float tube = 0; tube < PI2; tube += TUBE_STEP)
			{
				float cosTube = cos(tube), sinTube = sin(tube);
				float cosRing = cos(ring), sinRing = sin(ring);
				float cosPitch = cos(pitch), sinPitch = sin(pitch);
				float cosYaw = cos(yaw), sinYaw = sin(yaw);
				float radius = cosRing + TORUS_SIZE;
				float depth = 1 / (sinTube * radius * sinPitch + \
						sinRing * cosPitch + CAM_DIST);
				float worldY = sinTube * radius * cosPitch - sinRing * sinPitch;
				int col = COL_CENTER + COL_SCALE * depth * \
					(cosTube * radius * cosYaw - worldY * sinYaw);
				int row = ROW_CENTER + ROW_SCALE * depth * \
					(cosTube * radius * sinYaw + worldY * cosYaw);
				int pos = col + W * row;
				int bright = INTENSITY * \
					((sinRing * sinPitch - sinTube * cosRing * cosPitch) * \
					cosYaw - sinTube * cosRing * sinPitch - sinRing * \
						cosPitch - cosTube * cosRing * sinYaw);
				if (row > 0 && row < H && col > 0 && col < W && depth > z[pos])
				{
					z[pos] = depth;
					b[pos] = SHADE[bright > 0 ? bright : 0];
				}
			}
		}
		printf("\x1b[H");
		for (int index = 0; index < S; index++)
			putchar(index % W ? b[index] : '\n');
		pitch += 0.004;
		yaw += 0.002;
	}
	return (EXIT_SUCCESS);
}
