/**
 * ASCII Donut Animation
 * This program renders a rotating 3D donut (torus) as ASCII art in the terminal.
 * It uses 3D to 2D projection and z-buffering for hidden surface removal.
 */

 #include <string.h>  // For memset function
 #include <stdio.h>   // For printf and putchar functions
 #include <math.h>    // For sin() and cos() trigonometric functions

 // Global counter used in the output loop
 int outputIndex;

 int main() {
	 // Animation rotation angles
	 float rotationAngleA = 0;
	 float rotationAngleB = 0;

	 // Loop variables for angles
	 float angleAroundTube, angleAroundTorus;

	 // Screen dimensions
	 const int SCREEN_WIDTH = 80;
	 const int SCREEN_HEIGHT = 22;
	 const int BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

	 // Buffers for rendering
	 float depthBuffer[BUFFER_SIZE];    // Z-buffer to track depth
	 char outputBuffer[BUFFER_SIZE];    // Character buffer for ASCII output

	 // Constants for rendering
	 const float TORUS_DISTANCE = 2.0;        // Distance of torus from center
	 const float PROJECTION_DISTANCE = 5.0;   // Distance of viewer from scene
	 const int X_OFFSET = 40;                 // Center X position on screen
	 const int Y_OFFSET = 12;                 // Center Y position on screen
	 const float X_SCALE = 30.0;              // X scaling factor
	 const float Y_SCALE = 15.0;              // Y scaling factor

	 // Full circle in radians (2π)
	 const float FULL_CIRCLE = 6.28;

	 // Step sizes for angles (controls resolution)
	 const float TORUS_ANGLE_STEP = 0.07;     // Larger steps for torus circle
	 const float TUBE_ANGLE_STEP = 0.02;      // Smaller steps for tube circle (higher detail)

	 // Characters representing different light intensities (from darkest to brightest)
	 const char ILLUMINATION_CHARS[] = ".,-~:;=!*#$@";

	 // Clear the terminal screen using ANSI escape code
	 printf("\x1b[2J");

	 // Main animation loop (infinite)
	 while(1) {
		 // Clear the buffers for the next frame
		 memset(outputBuffer, ' ', BUFFER_SIZE);                 // Fill with spaces
		 memset(depthBuffer, 0, BUFFER_SIZE * sizeof(float));    // Reset depth values

		 // For each point on the torus surface
		 for(angleAroundTorus = 0; angleAroundTorus < FULL_CIRCLE; angleAroundTorus += TORUS_ANGLE_STEP) {
			 for(angleAroundTube = 0; angleAroundTube < FULL_CIRCLE; angleAroundTube += TUBE_ANGLE_STEP) {
				 // Precalculate sine and cosine values to improve readability
				 float sinTubeAngle = sin(angleAroundTube);
				 float cosTubeAngle = cos(angleAroundTube);
				 float sinTorusAngle = sin(angleAroundTorus);
				 float cosTorusAngle = cos(angleAroundTorus);
				 float sinRotationA = sin(rotationAngleA);
				 float cosRotationA = cos(rotationAngleA);
				 float sinRotationB = sin(rotationAngleB);
				 float cosRotationB = cos(rotationAngleB);

				 // Calculate the circle of the torus at distance TORUS_DISTANCE from center
				 float torusCircle = cosTorusAngle + TORUS_DISTANCE;

				 // Calculate depth (inverse of z-coordinate) for projection
				 float depth = 1.0 / (sinTubeAngle * torusCircle * sinRotationA +
									 sinTorusAngle * cosRotationA + PROJECTION_DISTANCE);

				 // Temporary calculation used in multiple places
				 float tempCalc = sinTubeAngle * torusCircle * cosRotationA - sinTorusAngle * sinRotationA;

				 // Calculate projected 2D coordinates
				 int xProjected = X_OFFSET + X_SCALE * depth * (cosTubeAngle * torusCircle * cosRotationB -
															   tempCalc * sinRotationB);
				 int yProjected = Y_OFFSET + Y_SCALE * depth * (cosTubeAngle * torusCircle * sinRotationB +
															   tempCalc * cosRotationB);

				 // Only process if the point is within screen boundaries
				 if(yProjected > 0 && yProjected < SCREEN_HEIGHT &&
					xProjected > 0 && xProjected < SCREEN_WIDTH) {

					 // Calculate buffer position
					 int bufferPosition = xProjected + SCREEN_WIDTH * yProjected;

					 // Calculate illumination level (normal vector dot product with light direction)
					 // This gives the surface brightness based on its orientation relative to light
					 int illumination = 8.0 * ((sinTorusAngle * sinRotationA -
											   sinTubeAngle * cosTorusAngle * cosRotationA) * cosRotationB -
											   sinTubeAngle * cosTorusAngle * sinRotationA -
											   sinTorusAngle * cosRotationA -
											   cosTubeAngle * cosTorusAngle * sinRotationB);

					 // Ensure illumination is not negative (clamp to valid range)
					 if(illumination < 0) illumination = 0;

					 // Only render if this point is closer than what was previously at this position
					 // This is a simple z-buffer for hidden surface removal
					 if(depth > depthBuffer[bufferPosition]) {
						 // Update depth buffer
						 depthBuffer[bufferPosition] = depth;

						 // Set character based on illumination level
						 outputBuffer[bufferPosition] = ILLUMINATION_CHARS[illumination];
					 }
				 }
			 }
		 }

		 // Move cursor to top-left corner of terminal using ANSI escape code
		 printf("\x1b[H");

		 // Output the frame, character by character
		 for(outputIndex = 0; outputIndex < BUFFER_SIZE; outputIndex++) {
			 // Print character or newline if at end of line
			 putchar(outputIndex % SCREEN_WIDTH ? outputBuffer[outputIndex] : '\n');
		 }

		 // Update rotation angles for next frame
		 rotationAngleA += 0.04;  // Controls rotation speed around X axis
		 rotationAngleB += 0.02;  // Controls rotation speed around Y axis
	 }

	 // This return statement is never reached due to the infinite loop
	 return 0;
 }
