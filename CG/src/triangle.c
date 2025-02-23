#include <GL/glut.h>
#include <stdio.h>

int v = 3;
int input[3][10];

float ROUND(int x){
	return x+0.5;
}

void dda_line(int xa,int ya,int xb,int yb){
	int dx = xb-xa;
	int dy = yb-ya;
	int steps = abs(dx);
	if (abs(dx)<abs(dy)){
		steps = abs(dy);
	}
	float xinc = (float)dx/steps;
	float yinc = (float)dy/steps;
	float x,y;
	x = xa;
	y = ya;
	for (int i=0;i<steps;i++){
		glVertex2d(ROUND(x),ROUND(y));
		x += xinc;
		y += yinc;
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

void boundary_fill(int b_col[3],int f_col[3],int x,int y){
	float current[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
	if ((current[0]!=b_col[0] || current[1]!=b_col[1] || current[2]!=b_col[2]) && (current[0]!=f_col[0] || current[1]!=f_col[1] || current[2]!=f_col[2])) {
		glBegin(GL_POINTS);  // Begin drawing points
        glColor3f(f_col[0], f_col[1], f_col[2]);  // Set the color for filling
        glVertex2d(x, y);  // Plot the point
        glEnd();
        glFlush();
		boundary_fill(b_col,f_col,x+1,y);
		boundary_fill(b_col,f_col,x,y+1);
		boundary_fill(b_col,f_col,x-1,y);
		boundary_fill(b_col,f_col,x,y-1);
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

void mul(int input[3][10],int t[3][3]){
	int output[3][10];
	for (int i=0;i<v;i++){
		for (int j=0;j<3;j++){
			output[i][j]=0;
			for (int k=0;k<3;k++){
				output[i][j] = output[i][j]+t[i][k]*input[k][j];
			}
		}
	}
	for (int i=0;i<v;i++){
		printf("%i\t",output[i][0]);
		printf("%i\t",output[i][1]);
		printf("%i\n",output[i][2]);
	}
	for (int i=0;i<v;i++){
		dda_line(output[0][i],output[1][i],output[0][(i+1)%v],output[1][(i+1)%v]);
	}
}

void translate(int tx,int ty,int input[3][10]){
	int t[3][3];
	for (int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			if (i==j){
				t[i][j]=1;
			}
			else {
				t[i][j]=0;
			}
		}
	}
	t[0][2]=tx;
	t[1][2]=ty;
	mul(input,t);
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
	glutCreateWindow("Translation");
	glClearColor(1,1,1,1);
	glColor3f(0,0,0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}