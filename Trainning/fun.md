// 1. DIFFERENT SHADING CHARACTERS - Try these variations:
const char *shade = ".,-~:;=!*#$@";           // Original
const char *shade = "░▒▓█";                   // Block characters
const char *shade = "⠀⠄⠆⠇⠧⠷⠿⣿";            // Braille patterns
const char *shade = "123456789ABCDEF";        // Numbers/letters
const char *shade = "○◔◐◕●";                  // Circles
const char *shade = "▁▂▃▄▅▆▇█";               // Bars

// 2. SPEED VARIATIONS - Change rotation speeds:
pitch += 0.004;  yaw += 0.002;    // Original (smooth)
pitch += 0.02;   yaw += 0.01;     // Faster
pitch += 0.001;  yaw += 0.0005;   // Slower
pitch += 0.01;   yaw += 0;        // Only pitch rotation
pitch += 0;      yaw += 0.01;     // Only yaw rotation

// 3. SIZE AND RESOLUTION - Modify loop increments:
for(float ring = 0; ring < PI2; ring += 0.07)    // Original
for(float tube = 0; tube < PI2; tube += 0.02)

for(float ring = 0; ring < PI2; ring += 0.05)    // Higher detail
for(float tube = 0; tube < PI2; tube += 0.01)

for(float ring = 0; ring < PI2; ring += 0.1)     // Lower detail (faster)
for(float tube = 0; tube < PI2; tube += 0.05)

// 4. TORUS SHAPE - Modify the torus geometry:
float h = cosRing + 2;                 // Original
float h = cosRing + 3;                 // Bigger torus
float h = cosRing + 1.5;               // Smaller torus
float h = cosRing + 1 + sin(pitch);    // Pulsating torus
float h = cosRing + 2 + cos(ring*3);   // Wavy torus

// 5. PROJECTION SCALING - Change the 3D to 2D mapping:
int x = 40 + 30 * D * (cosTube * h * cosYaw - t * sinYaw);  // Original
int y = 12 + 15 * D * (cosTube * h * sinYaw + t * cosYaw);

int x = 40 + 20 * D * (cosTube * h * cosYaw - t * sinYaw);  // Smaller
int y = 12 + 10 * D * (cosTube * h * sinYaw + t * cosYaw);

int x = 40 + 40 * D * (cosTube * h * cosYaw - t * sinYaw);  // Larger
int y = 12 + 20 * D * (cosTube * h * sinYaw + t * cosYaw);

// 6. LIGHTING EFFECTS - Modify brightness calculation:
int bright = 8 * ((sinRing * sinPitch - sinTube * cosRing * cosPitch) * cosYaw
                - sinTube * cosRing * sinPitch - sinRing * cosPitch
                - cosTube * cosRing * sinYaw);                    // Original

int bright = 12 * (...);    // Brighter
int bright = 4 * (...);     // Dimmer
int bright = abs(8 * (...)); // Always positive (no dark areas)

// 7. PSYCHEDELIC EFFECTS - Add time-based variations:
const char *shade = ".,-~:;=!*#$@";
int shadeIdx = (bright + (int)(pitch*10)) % 12;  // Color cycling
b[pos] = shade[shadeIdx];

// 8. MULTIPLE DONUTS - Add offset donuts:
// Inside the main loop, add another nested loop:
for(int donut = 0; donut < 3; donut++) {
    float offsetX = 20 * cos(donut * 2.1);
    float offsetY = 10 * sin(donut * 2.1);
    // ... modify x and y calculations with offsets
}

// 9. OSCILLATING EFFECTS:
pitch += 0.004 + 0.002 * sin(yaw * 5);    // Variable speed
yaw += 0.002 + 0.001 * cos(pitch * 3);

// 10. WARPED SPACE:
float warp = sin(pitch * 2) * 0.5;
int x = 40 + (30 + warp * 10) * D * (cosTube * h * cosYaw - t * sinYaw);

// 11. BREATHING DONUT:
float breath = 1 + 0.3 * sin(pitch * 8);
float h = (cosRing + 2) * breath;

// 12. RAINBOW EFFECT (using different characters as colors):
const char rainbow[] = "ROYGBIV";
int colorIdx = (int)(ring * 7 / PI2) % 7;
if(bright > 0) b[pos] = rainbow[colorIdx];
