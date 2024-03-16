#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
int cx, cy, r;
void putPixelPoint(GLint x,GLint y){
    glBegin(GL_POINTS);
    // Normalize coordinates
    glVertex2f((float)x / glutGet(GLUT_WINDOW_WIDTH), (float)y / glutGet(GLUT_WINDOW_HEIGHT));
    glEnd();
}

void plotReflex(GLint x,GLint y,GLint cx,GLint cy){
    putPixelPoint(cx + x, cy + y);
    putPixelPoint(cx - x, cy + y);
    putPixelPoint(cx + x, cy - y);
    putPixelPoint(cx - x, cy - y);
    putPixelPoint(cx + y, cy + x);
    putPixelPoint(cx - y, cy + x);
    putPixelPoint(cx + y, cy - x);
    putPixelPoint(cx - y, cy - x);
}

void drawDotCircle(float cx, float cy, float r, int num_segments){
    
    for (int i = 0; i < num_segments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        putPixelPoint(cx + x, cy + y);
    }
}

void midPointCircle(GLint cx, GLint cy, int r){
    GLint x = 0;
    GLint y = r;
    int pk = 1 - r;
    while (x < y) {
        plotReflex(x, y, cx, cy);
        if(pk < 0){
            pk += 2 * x + 1;
        } else {
            pk += 2 * (x - y) + 1;
            y--;
        }
        x++;
    }
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    midPointCircle(cx,cy,r);
    glFlush();
}

void Init(){
    glClearColor(0.12f, 0.12f, 0.12f, 2.20f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f); // Set orthographic projection
}
void reshape(int width,int hight){
    glViewport(0, 0, width, hight);
    glutPostRedisplay();
}
int main(int argc, char **argv){
    std::cout << "Enter the coodinate for x and y: ";
    std::cin >> cx >> cy;
    std::cout << "Enter the radius of a circle: ";
    std::cin >> r;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(450, 150);
    glutCreateWindow("Circle Drawing Algorithm");
    Init();
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
