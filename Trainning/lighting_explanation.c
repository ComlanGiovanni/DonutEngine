/**
 * Système d'Éclairage et Z-Buffering du Donut
 * Ce programme démontre les concepts d'éclairage et de gestion de la profondeur
 * utilisés dans le rendu du donut ASCII.
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

// Caractères représentant différents niveaux d'éclairage
const char LIGHT_CHARS[] = ".,-~:;=!*#$@";

// Structure pour un point 3D avec sa normale
typedef struct {
    float x, y, z;      // Position
    float nx, ny, nz;   // Vecteur normal
} Point3DWithNormal;

// Structure pour le z-buffer
typedef struct {
    char character;     // Caractère à afficher
    float depth;        // Profondeur du point
} ZBufferCell;

// Fonction pour calculer un point sur le tore avec sa normale
Point3DWithNormal calculateTorusPointWithNormal(float theta, float phi, float R, float r) {
    Point3DWithNormal point;

    // Calcul de la position
    float cosPhi = cos(phi);
    float sinPhi = sin(phi);
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    point.x = (R + r * cosPhi) * cosTheta;
    point.y = (R + r * cosPhi) * sinTheta;
    point.z = r * sinPhi;

    // Calcul de la normale (vecteur perpendiculaire à la surface)
    point.nx = cosPhi * cosTheta;
    point.ny = cosPhi * sinTheta;
    point.nz = sinPhi;

    return point;
}

// Fonction pour calculer l'intensité lumineuse
int calculateLightIntensity(Point3DWithNormal point, float lightX, float lightY, float lightZ) {
    // Normalisation du vecteur lumière
    float length = sqrt(lightX * lightX + lightY * lightY + lightZ * lightZ);
    lightX /= length;
    lightY /= length;
    lightZ /= length;

    // Calcul du produit scalaire (cosinus de l'angle entre la normale et la lumière)
    float dotProduct = point.nx * lightX + point.ny * lightY + point.nz * lightZ;

    // Conversion en index de caractère (0-11)
    int index = (int)((dotProduct + 1.0) * 5.5);  // Échelle de -1,1 à 0,11

    // Clampage des valeurs
    if (index < 0) index = 0;
    if (index > 11) index = 11;

    return index;
}

int main() {
    // Paramètres du tore
    const float R = 2.0;  // Rayon principal
    const float r = 0.5;  // Rayon du tube

    // Direction de la lumière
    float lightX = 0.0;
    float lightY = 0.0;
    float lightZ = 1.0;

    // Création d'un petit z-buffer pour la démonstration
    const int WIDTH = 10;
    const int HEIGHT = 10;
    ZBufferCell zBuffer[WIDTH * HEIGHT];

    // Initialisation du z-buffer
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        zBuffer[i].character = ' ';
        zBuffer[i].depth = -INFINITY;
    }

    // Calcul de quelques points pour la démonstration
    for (float theta = 0; theta < 6.28; theta += 1.57) {
        for (float phi = 0; phi < 6.28; phi += 1.57) {
            Point3DWithNormal point = calculateTorusPointWithNormal(theta, phi, R, r);

            // Calcul de l'intensité lumineuse
            int lightIndex = calculateLightIntensity(point, lightX, lightY, lightZ);

            // Projection simple pour la démonstration
            int x = (int)((point.x + 2.5) * 2);
            int y = (int)((point.y + 2.5) * 2);

            // Vérification des limites
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                int index = y * WIDTH + x;

                // Z-buffering : on ne met à jour que si le point est plus proche
                if (point.z > zBuffer[index].depth) {
                    zBuffer[index].depth = point.z;
                    zBuffer[index].character = LIGHT_CHARS[lightIndex];
                }
            }
        }
    }

    // Affichage du résultat
    printf("Résultat du z-buffering avec éclairage :\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", zBuffer[y * WIDTH + x].character);
        }
        printf("\n");
    }

    return 0;
}
