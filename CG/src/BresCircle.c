#include <GL/glut.h>
#include <math.h>

// Function to plot symmetric points for the circle
void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(xc + x, yc + y);
    glVertex2d(xc - x, yc + y);
    glVertex2d(xc + x, yc - y);
    glVertex2d(xc - x, yc - y);
    glVertex2d(xc + y, yc + x);
    glVertex2d(xc - y, yc + x);
    glVertex2d(xc + y, yc - x);
    glVertex2d(xc - y, yc - x);
    glEnd();
}

// Bresenham's Circle Drawing Algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r; // Decision parameter

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glFlush();
}

// Display function for GLUT
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int xc = 250, yc = 250, r = 100; // Circle center and radius
    drawCircle(xc, yc, r);
}

// Initialization function for GLUT
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background to black
    glColor3f(1.0, 1.0, 1.0);         // Set drawing color to white
    glPointSize(2.0);                 // Set point size
    gluOrtho2D(0, 500, 0, 500);       // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // Window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
