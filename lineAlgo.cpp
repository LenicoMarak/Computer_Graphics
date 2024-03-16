#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

void putPixelPoint(GLint x,GLint y){
    glBegin(GL_POINTS);
    // Normalize coordinates
    glVertex2f((float)x / glutGet(GLUT_WINDOW_WIDTH), (float)y / glutGet(GLUT_WINDOW_HEIGHT));
    glEnd();
}

void ddaLine(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = static_cast<float>(dx) / steps;
    float Yinc = static_cast<float>(dy) / steps;
    float x = x0;
    float y = y0;
    for (int i = 1; i < steps; i++){
        putPixelPoint(round(x), round(y));
        x += xinc;
        y += Yinc;
    }
}

void breshenhamLine(int x0, int y0, int x1, int y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int pk = 2 * dy - dx;
    int x, y;
    if (x0 > x1){
        x = x1;
        y = y1;
        x1 = x0;
    }
    else{
        x = x0;
        y = y0;
    }
    while (x < x1){
        putPixelPoint(x, y);
        if (pk < 0){
            pk += 2 * dy;
        }
        else{
            pk += 2 * (dy - dx);
            y++;
        }
        x++;
    }
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    breshenhamLine(300, 250, 500, 500);
    ddaLine(300, 100, 500, 400);
    breshenhamLine(300, 150, 500, 150);
    glFlush();
}

void Initialize(){
    glClearColor(0.12f, 0.12f, 0.15f, 2.20f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // Set orthographic projection
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(450, 150);
    glutCreateWindow("Line Drawing Algorithm");
    Initialize();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
