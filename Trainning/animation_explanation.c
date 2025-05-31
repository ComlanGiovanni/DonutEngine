/**
 * Animation et Rotations du Donut
 * Ce programme démontre les concepts d'animation et de rotation
 * utilisés dans le rendu du donut ASCII.
 */

#include <stdio.h>
#include <math.h>
#include <unistd.h>  // Pour usleep

// Caractères pour l'affichage
const char CHARS[] = ".,-~:;=!*#$@";

// Structure pour un point 3D
typedef struct {
    float x, y, z;
} Point3D;

// Structure pour les angles de rotation
typedef struct {
    float x, y, z;
} RotationAngles;

// Fonction pour calculer un point sur le tore
Point3D calculateTorusPoint(float theta, float phi, float R, float r) {
    Point3D point;
    float cosPhi = cos(phi);
    float sinPhi = sin(phi);
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    point.x = (R + r * cosPhi) * cosTheta;
    point.y = (R + r * cosPhi) * sinTheta;
    point.z = r * sinPhi;

    return point;
}

// Fonction pour appliquer une rotation autour de l'axe X
Point3D rotateX(Point3D point, float angle) {
    Point3D rotated;
    float cosA = cos(angle);
    float sinA = sin(angle);

    rotated.x = point.x;
    rotated.y = point.y * cosA - point.z * sinA;
    rotated.z = point.y * sinA + point.z * cosA;

    return rotated;
}

// Fonction pour appliquer une rotation autour de l'axe Y
Point3D rotateY(Point3D point, float angle) {
    Point3D rotated;
    float cosA = cos(angle);
    float sinA = sin(angle);

    rotated.x = point.x * cosA + point.z * sinA;
    rotated.y = point.y;
    rotated.z = -point.x * sinA + point.z * cosA;

    return rotated;
}

// Fonction pour appliquer une rotation autour de l'axe Z
Point3D rotateZ(Point3D point, float angle) {
    Point3D rotated;
    float cosA = cos(angle);
    float sinA = sin(angle);

    rotated.x = point.x * cosA - point.y * sinA;
    rotated.y = point.x * sinA + point.y * cosA;
    rotated.z = point.z;

    return rotated;
}

// Fonction pour projeter un point 3D sur un plan 2D
void projectPoint(Point3D point, int* x, int* y, float distance) {
    float scale = distance / (distance + point.z);
    *x = (int)(point.x * scale * 10) + 20;  // Centrage et mise à l'échelle
    *y = (int)(point.y * scale * 5) + 10;   // Centrage et mise à l'échelle
}

int main() {
    // Paramètres du tore
    const float R = 2.0;  // Rayon principal
    const float r = 0.5;  // Rayon du tube
    const float distance = 5.0;  // Distance de projection

    // Taille de l'écran
    const int WIDTH = 40;
    const int HEIGHT = 20;

    // Buffer pour l'affichage
    char screen[HEIGHT][WIDTH];
    float zBuffer[HEIGHT][WIDTH];

    // Angles de rotation initiaux
    RotationAngles angles = {0.0, 0.0, 0.0};

    // Boucle d'animation
    while(1) {
        // Effacer l'écran
        printf("\x1b[2J\x1b[H");

        // Initialiser les buffers
        for(int y = 0; y < HEIGHT; y++) {
            for(int x = 0; x < WIDTH; x++) {
                screen[y][x] = ' ';
                zBuffer[y][x] = -INFINITY;
            }
        }

        // Calculer les points du tore
        for(float theta = 0; theta < 6.28; theta += 0.1) {
            for(float phi = 0; phi < 6.28; phi += 0.1) {
                // Calculer le point sur le tore
                Point3D point = calculateTorusPoint(theta, phi, R, r);

                // Appliquer les rotations
                point = rotateX(point, angles.x);
                point = rotateY(point, angles.y);
                point = rotateZ(point, angles.z);

                // Projeter le point
                int x, y;
                projectPoint(point, &x, &y, distance);

                // Vérifier si le point est dans les limites de l'écran
                if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                    // Calculer l'intensité lumineuse simple
                    int intensity = (int)((point.z + 1.0) * 5.5);
                    if(intensity < 0) intensity = 0;
                    if(intensity > 11) intensity = 11;

                    // Z-buffering
                    if(point.z > zBuffer[y][x]) {
                        zBuffer[y][x] = point.z;
                        screen[y][x] = CHARS[intensity];
                    }
                }
            }
        }

        // Afficher le résultat
        for(int y = 0; y < HEIGHT; y++) {
            for(int x = 0; x < WIDTH; x++) {
                printf("%c", screen[y][x]);
            }
            printf("\n");
        }

        // Mettre à jour les angles de rotation
        angles.x += 0.1;
        angles.y += 0.05;
        angles.z += 0.02;

        // Attendre un peu
        usleep(50000);  // 50ms
    }

    return 0;
}
