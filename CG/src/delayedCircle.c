#include <GL/glut.h>
#include <windows.h>  // For Sleep()
#include <stdio.h>

int xc, yc, r; // Circle center and radius

void plotPoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y); // Octant 1
    glVertex2i(xc - x, yc + y); // Octant 2
    glVertex2i(xc + x, yc - y); // Octant 7
    glVertex2i(xc - x, yc - y); // Octant 8
    glVertex2i(xc + y, yc + x); // Octant 3
    glVertex2i(xc - y, yc + x); // Octant 4
    glVertex2i(xc + y, yc - x); // Octant 6
    glVertex2i(xc - y, yc - x); // Octant 5
    glEnd();
    glFlush();
}

void drawCircle() {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    plotPoints(x, y);

    while (x <= y) {
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;

        plotPoints(x, y);

        // Introduce a small delay to visualize the circle formation
        Sleep(5); // Delay in milliseconds (5 milliseconds)
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);      // Set background color to black
    glColor3f(1.0, 1.0, 1.0);              // Set drawing color to white
    gluOrtho2D(-500, 500, -500, 500);      // Set coordinate system for the window
}

int main(int argc, char** argv) {
    printf("Enter center of circle (xc yc): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter radius of circle: ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle (Real-Time)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
