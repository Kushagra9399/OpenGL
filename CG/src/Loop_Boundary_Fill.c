#include <GL/glut.h>
#include <stdio.h>

int v = 3;
int input[3][10];

int s[100][2];
int top = -1;
void push(int a,int b){
    top += 1;
    s[top][0] = a;
    s[top][1] = b;
}
void pop(int *a,int *b){
    if (top == -1){
        *a = -1;
        *b = -1;
    } else {
        *a = s[top][0];
        *b = s[top][1];
        top -= 1;
    }
}

void BresLine(int xa,int ya,int xb,int yb){
    int dx,dy,d;
    int x,y;
    dx = xb-xa;
    dy = yb-ya;
    if (abs(dx)>abs(dy)){
        if (xa>xb){
            x = xa;
            y = ya;
            xa = xb;
            ya = yb;
            xb = x;
            yb = y;
        }
        dx = xb-xa;
        dy = yb-ya;
        d = 2*dy - dx;
        while (xb>=xa){
            glVertex2d(xa,ya);
            if (d<0){
                d += 2*abs(dy);
            } else {
                d += 2*abs(dy) - 2*dx;
                if (yb>=ya){
                    ya+= 1;
                } else {
                    ya-=1;
                }
            }
            xa += 1;
        }
    } else {
        if (ya>yb){
            x = xa;
            y = ya;
            xa = xb;
            ya = yb;
            xb = x;
            yb = y;
        }
        dx = xb-xa;
        dy = yb-ya;
        d = 2*dx - dy;
        while (yb>=ya){
            glVertex2d(xa,ya);
            if (d<0){
                d += 2*abs(dx);
            } else {
                d += 2*abs(dx) - 2*dy;
                if (xb>=xa){
                    xa+= 1;
                } else {
                    xa -=1;
                }
            }
            ya += 1;
        }
    }
}

void flood_fill(int back_col[3],int f_col[3],int x,int y){
    float current[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
    if ((current[0]==back_col[0] && current[1]==back_col[1] && current[2]==back_col[2])) {
        glBegin(GL_POINTS);  // Begin drawing points
        glColor3f(f_col[0], f_col[1], f_col[2]);  // Set the color for filling
        glVertex2d(x, y);  // Plot the point
        glEnd();
        glFlush();
        flood_fill(back_col,f_col,x+1,y);
        flood_fill(back_col,f_col,x,y+1);
        flood_fill(back_col,f_col,x-1,y);
        flood_fill(back_col,f_col,x,y-1);
    }
}

void boundary_fill(int b_col[3],int f_col[3],int x,int y){
    float current[3];
    top = -1;
    push(x,y);
    while (top!=-1){
        pop(&x,&y);
        glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
        if ((current[0]!=b_col[0] || current[1]!=b_col[1] || current[2]!=b_col[2]) && (current[0]!=f_col[0] || current[1]!=f_col[1] || current[2]!=f_col[2])) {
            glBegin(GL_POINTS);  // Begin drawing points
            glColor3f(f_col[0], f_col[1], f_col[2]);  // Set the color for filling
            glVertex2d(x, y);  // Plot the point
            glEnd();
            glFlush();
            push(x+1,y);
            push(x,y+1);
            push(x-1,y);
            push(x,y-1);
        }
    }
}

void Triangle(){
	for (int i=0;i<v;i++){
		printf("%i\t",input[i][0]);
		printf("%i\t",input[i][1]);
		printf("%i\n",input[i][2]);
	}
	for (int i=0;i<v;i++){
		BresLine(input[0][i],input[1][i],input[0][(i+1)%v],input[1][(i+1)%v]);
	}
	int b_col[3] = {0,0,0};
	int f_col[3] = {1,0,0};
	int back_col[3] = {1,1,1};
	glColor3f(f_col[0],f_col[1],f_col[2]);
	boundary_fill(b_col,f_col,130,120);
	//flood_fill(back_col,f_col,150,120);
	//translate(10,20,input);
}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glVertex2d(100,200);
	glColor3f(0,0,0);
	Triangle();
	glEnd();
	glFlush();
}

int main(int args,char** argv){
	printf("Enter the coordinates for the 3 vertices of the triangle:\n");
    for (int i = 0; i < v; i++) {
        printf("Vertex %d:\n", i + 1);
        printf("X%d: ", i + 1);
        scanf("%d", &input[0][i]); // X coordinates
        printf("Y%d: ", i + 1);
        scanf("%d", &input[1][i]); // Y coordinates
        input[2][i] = 1; // Homogeneous coordinate
    }
	glutInit(&args,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Colour loop");
	glClearColor(1,1,1,1);
	glColor3f(0,0,0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}