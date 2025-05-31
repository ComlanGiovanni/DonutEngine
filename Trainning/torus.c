
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	const char *SHADE = ".,-~:;=!*#$@";
	const int W = 80, H = 22, S = W * H, INTENSITY = 8, \
		COL_CENTER = 40, ROW_CENTER = 12, COL_SCALE = 30, ROW_SCALE = 15;
	const float PI2 = 6.28, CAM_DIST = 5, \
		TORUS_SIZE = 3, RING_STEP = 0.07, TUBE_STEP = 0.02;
	float pitch = 0, yaw = 0;
	float z[S];
	char b[S];
	printf("\x1b[2J");
	while(true)
	{
		memset(b, ' ', S);
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
				int row = ROW_CENTER + ROW_SCALE * camera * (cosTube * radus * sinYaw + y3d * cosYaw);
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
	}
	return (EXIT_SUCCESS);
}
