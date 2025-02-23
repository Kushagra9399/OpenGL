#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float input[3][10];
int v;

void Bresnum_Line(int xa,int ya,int xb, int yb){
	int d;
	int dx,dy,x,y;
	dx = xb-xa;
	dy = yb-ya;
	if (abs(dx)>abs(dy)) {
		if (xb<xa) {
			x = xa;
			y = ya;
			xa = xb;
			ya = yb;
			xb = x;
			yb = y;
		}
		dx = xb-xa;
		dy = yb-ya;
		d = 2*abs(dy)-abs(dx);
		while (xb>xa){
			if (d<0){
				d+= 2*abs(dy);
			} else {
				d+= 2*abs(dy)-2*abs(dx);
				if (dy>0){
					ya+=1;		
				} else {
					ya -=1;
				}
			}
			xa += 1;
			glVertex2d(xa,ya);
		}
	} else {
		if (yb<ya) {
			x = xa;
			y = ya;
			xa = xb;
			ya = yb;
			xb = x;
			yb = y;
		}
		dx = xb-xa;
		dy = yb-ya;
		d = 2*abs(dx)-abs(dy);
		while (yb>ya){
			if (d<0){
				d+= 2*abs(dx);
			} else {
				d+= 2*abs(dx)-2*abs(dy);
				if (dx>0){
					xa+=1;		
				} else {
					xa -=1;
				}
			}
			ya += 1;
			glVertex2d(xa,ya);
		}
	}
}

void Bresnum_Circle(int r,int xa, int ya){
	int d = 3-2*r;
	int x,y;
	x = 0;
	y = r;
	while (x<y){
		if (d<0){
			d += 4*x + 6;
		} else {
			y -= 1;
			d += 4*x - 4*y +10;
		}
		x += 1;
		glVertex2d(xa + x,ya + y);
		glVertex2d(xa + y,ya + x);
		glVertex2d(xa + y,ya - x);
		glVertex2d(xa + x,ya - y);
		glVertex2d(xa - x,ya - y);
		glVertex2d(xa - y,ya - x);
		glVertex2d(xa - y,ya + x);
		glVertex2d(xa - x,ya + y);
	}
}

void Shape(float input[3][10]){
	for (int i=0;i<v;i++){
		Bresnum_Line(input[0][i],input[1][i],input[0][(i+1)%v],input[1][(i+1)%v]);
	}
}

void mul(float input[3][10],float t[3][3]){
	float output[3][10];
	for (int i=0;i<3;i++){
		for (int j=0;j<v;j++){
			output[i][j] = 0;
			for (int k=0;k<3;k++){
				output[i][j] += t[i][k]*input[k][j];
			}
		}
	}
	for (int i=0;i<3;i++){
		for (int j=0;j<v;j++){
			printf("%f\t",output[i][j]);
		}
		printf("\n");
	}
	Shape(output);
}

void identity(float t[3][3]){
	for (int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			if (i==j){
				t[i][j] = 1;
			} else {
				t[i][j] = 0;
			}
		}
	}
}

void Rotation(){
	float r[3][3];
	float a;
	int xr,yr;
	printf("Angle: \n");
	scanf("%f",&a);
    printf("xr: \n");
	scanf("%d",&xr);
	printf("yr: \n");
	scanf("%d",&yr);
	identity(r);
	a = a*3.14/180;
	r[0][0] = cos(a);
	r[1][1] = cos(a);
	r[0][1] = -sin(a);
	r[1][0] = sin(a);
	r[0][2] = xr*(1-cos(a))+yr*sin(a);
	r[1][2] = yr*(1-cos(a))-xr*sin(a);
	mul(input,r);
}

void Scale(){
	float s[3][3];
	float sx,sy;
	int xr,yr;
	identity(s);
	printf("sx: \n");
	scanf("%f",&sx);
	printf("sy: \n");
	scanf("%f",&sy);
	printf("xr: \n");
	scanf("%d",&xr);
	printf("yr: \n");
	scanf("%d",&yr);
	s[0][0] = sx;
	s[1][1] = sy;
	s[0][2] = xr*(1-sx);
	s[1][2] = yr*(1-sy);
	mul(input,s);
}

void Translate(){
	float t[3][3];
	float tx,ty;
	identity(t);
	printf("tx: \n");
	scanf("%f",&tx);
	printf("ty: \n");
	scanf("%f",&ty);
	t[0][2] = tx;
	t[1][2] = ty;
	mul(input,t);
}

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	Shape(input);
	//Translate();
	//Scale();
	Rotation();
	glEnd();
	glFlush();
}

int main(int args,char **argv){
	
	printf("Enter Vertex: \n");
	scanf("%d",&v);
	for (int i=0;i<v;i++){
		printf("X: \n");
		scanf("%f",&input[0][i]);
		printf("Y: \n");
		scanf("%f",&input[1][i]);
		input[2][i] = 1;
	}
	
	glutInit(&args,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("KP");
	gluOrtho2D(0,640,0,480);
	glClearColor(0,1,1,0);
	glColor3f(0,0,0);
	glutDisplayFunc(Draw);
	glutMainLoop();
}