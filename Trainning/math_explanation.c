/**
 * Mathématiques de la Projection 3D du Donut
 * Ce programme démontre les concepts mathématiques de base utilisés dans la projection 3D
 * d'un donut (tore) en ASCII art.
 */

#include <stdio.h>
#include <math.h>

// Structure pour représenter un point 3D
typedef struct {
    float x;
    float y;
    float z;
} Point3D;

// Structure pour représenter un point 2D projeté
typedef struct {
    int x;
    int y;
    float depth;
} Point2D;

// Fonction pour calculer un point sur le tore
Point3D calculateTorusPoint(float theta, float phi, float R, float r) {
    Point3D point;
    // R est le rayon principal du tore
    // r est le rayon du tube
    point.x = (R + r * cos(phi)) * cos(theta);
    point.y = (R + r * cos(phi)) * sin(theta);
    point.z = r * sin(phi);
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

// Fonction pour projeter un point 3D sur un plan 2D
Point2D projectPoint(Point3D point, float distance) {
    Point2D projected;
    // Projection perspective simple
    float scale = distance / (distance + point.z);
    projected.x = (int)(point.x * scale);
    projected.y = (int)(point.y * scale);
    projected.depth = point.z;
    return projected;
}

int main() {
    // Paramètres du tore
    const float R = 2.0;  // Rayon principal
    const float r = 0.5;  // Rayon du tube
    const float distance = 5.0;  // Distance de projection

    // Angles de rotation
    float angleX = 0.0;
    float angleY = 0.0;

    // Exemple de calcul pour un point
    float theta = 0.0;  // Angle autour du tore
    float phi = 0.0;    // Angle autour du tube

    // Calcul d'un point sur le tore
    Point3D point = calculateTorusPoint(theta, phi, R, r);

    // Application des rotations
    point = rotateX(point, angleX);
    point = rotateY(point, angleY);

    // Projection sur le plan 2D
    Point2D projected = projectPoint(point, distance);

    // Affichage des résultats
    printf("Point 3D original: (%.2f, %.2f, %.2f)\n", point.x, point.y, point.z);
    printf("Point 2D projeté: (%d, %d) avec profondeur %.2f\n",
           projected.x, projected.y, projected.depth);

    return 0;
}
