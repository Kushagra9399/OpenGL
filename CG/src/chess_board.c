#include <GL/glut.h>

int w=400;
int h=400;

void Bresnum_Line(int xa,int ya,int xb, int yb){
    int x,y,d;
    int dx = xb - xa;
    int dy = yb-ya;
    if (abs(dx)>abs(dy)){
        if (xb<xa){
            x = xa;
            y = ya;
            xa = xb;
            ya = yb;
            xb = x;
            yb = y;
        }
        dx = xb-xa;
        dy = yb-ya;
        d = 2*abs(dy) - dx;
        glVertex2d(xa,ya);
        while (xa<=xb){
            if (d<0){
                d += 2*abs(dy);
            } else {
                d += 2*abs(dy) - 2*dx;
                if (dy<0){
                    ya -= 1;
                } else {
                    ya += 1;
                }
            }
            xa += 1;
            glVertex2d(xa,ya);
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
        d = 2*abs(dx) - dy;
        glVertex2d(xa,ya);
        while (ya<=yb){
            if (d<0){
                d += 2*abs(dx);
            } else {
                d += 2*abs(dx) - 2*dy;
                if (dx<0){
                    xa -= 1;
                } else {
                    xa += 1;
                }
            }
            ya += 1;
            glVertex2d(xa,ya);
        }
    }
}

void Boundary_Fill(int x,int y,int bound_col[3],int f_col[3]){
    glColor3f(f_col[0],f_col[1],f_col[3]);
    int current[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
    if ((current[0]!=bound_col[0] || current[1]!=bound_col[1] || current[2]!=bound_col[2]) && (current[0]!=f_col[0] || current[1]!=f_col[1] || current[2]!=f_col[2])) {
        glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        glFlush();
        Boundary_Fill(x+1,y,bound_col,f_col);
        Boundary_Fill(x,y+1,bound_col,f_col);
        Boundary_Fill(x-1,y,bound_col,f_col);
        Boundary_Fill(x,y-1,bound_col,f_col);
    }
}

void Chess_Board(){
    int l,b;
    l = 0;
    b = 0;
    for (int i=0;i<9;i++){
        Bresnum_Line(0,l,w,l);
        l += h/8;
    }
    for (int i=0;i<9;i++){
        Bresnum_Line(b,0,b,h);
        b += w/8;
    }
    int bound_col[3] = {0,0,0};
    int f_col[3] = {1,0,0};
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if ((i+j)%2==0){
                Boundary_Fill(i*w/8+10,j*h/8+10,bound_col,f_col);
            }
        }
    }
}

void Partition(){
    Bresnum_Line(0,h/2,w,h/2);
    Bresnum_Line(w/2,0,w/2,h);
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    //Partition();
    Chess_Board();
    glEnd();
    glFlush();
}

int main(int args,char **argv){
    glutInit(&args,argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
    glutInitWindowSize(w,h);
    glutCreateWindow("Chess Board");
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    gluOrtho2D(0,w,0,h);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}