#include <GL/glut.h>
#include <stdio.h>

float red = 1.0, green = 0.0, blue = 0.0; // Color of the points

// This function will be called when the mouse is clicked
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert the mouse coordinates to OpenGL coordinates
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);
        float winX = (2.0f * x) / width - 1.0f;
        float winY = 1.0f - (2.0f * y) / height;

        // Print out the mouse coordinates
        printf("Mouse clicked at: (%f, %f)\n", winX, winY);

        // Set the color for drawing
        glColor3f(1,1,0);

        // Draw the point at the mouse position
        glBegin(GL_POINTS);
        glVertex2f(winX, winY);
        glEnd();

        // Flush the OpenGL pipeline to make sure drawing happens
        glFlush();
    }
}

// This function will be called when the mouse is moved
void mouseMotion(int x, int y) {
    // Convert the mouse coordinates to OpenGL coordinates
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    float winX = (2.0f * x) / width - 1.0f;
    float winY = 1.0f - (2.0f * y) / height;

    // Print out the mouse coordinates
    printf("Mouse moved to: (%f, %f)\n", winX, winY);

    // Change the color based on the mouse X position for fun
    red = (winX + 1.0f) / 2.0f;
    green = (winY + 1.0f) / 2.0f;
    blue = 1.0f - (winX + 1.0f) / 2.0f;

    // Redraw the window to show the updated mouse movement color
    glutPostRedisplay();
}

// Display function to refresh the screen
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// Initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glColor3f(red, green, blue);       // Set the initial color
    glPointSize(5.0);                  // Set the size of points
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthogonal projection
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set window size
    glutCreateWindow("OpenGL Mouse Interaction");

    init(); // Initialize OpenGL settings

    glutMouseFunc(mouseButton); // Register the mouse button callback
    glutMotionFunc(mouseMotion); // Register the mouse motion callback
    glutDisplayFunc(display); // Register the display callback

    glutMainLoop(); // Enter the GLUT event loop

    return 0;
}
