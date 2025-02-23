#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>  // For Sleep()
#include <math.h>

int xc, yc, r; // Circle center and radius
float pixel[10][2];
int top=-1;

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

    // Start from the initial point and draw
    plotPoints(x, y);

    // First half of the circle
    while (x <= y) {
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;

        plotPoints(x, y);
        Sleep(5); // Delay in milliseconds (5 milliseconds) to animate
    }

    // The circle is now complete, so we return to the starting point
    // The starting point is at (r, 0), so we manually plot it again
    plotPoints(r, 0);
    Sleep(5); // Add delay for visual effect
}

void Circle(){
    if (top==1){
        top = -1;
        xc = pixel[0][0];
        yc = pixel[0][1];
        r = pow((pixel[1][0]*pixel[1][0]+pixel[1][1]*pixel[1][1]),0.5);
        drawCircle();
    }
}

void display() {
    // glClear(GL_COLOR_BUFFER_BIT);
    // drawCircle();
    Circle();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);      // Set background color to black
    glColor3f(1.0, 1.0, 1.0);              // Set drawing color to white
    gluOrtho2D(0, 640,0,480);      // Set coordinate system for the window
}

void mouse(int button,int state,int x,int y){
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        printf("%f",GLUT_WINDOW_HEIGHT);
        float winX = x;
        float winY = -1*(GLUT_WINDOW_HEIGHT-582+y);
        printf("Mouse clicked at: (%f, %f)\n", winX, winY);
        top += 1;
        pixel[top][0] = winX;
        pixel[top][1] = winY;

        // Set the color for drawing
        glColor3f(1,1,0);

        // Draw the point at the mouse position
        glBegin(GL_POINTS);
        glVertex2d(winX, winY);
        glEnd();

        // Flush the OpenGL pipeline to make sure drawing happens
        glFlush();
    }
}

int main(int argc, char** argv) {
    // printf("Enter center of circle (xc yc): ");
    // scanf("%d %d", &xc, &yc);
    // printf("Enter radius of circle: ");
    // scanf("%d", &r);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Circle (Animated, Returns to Start)");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
