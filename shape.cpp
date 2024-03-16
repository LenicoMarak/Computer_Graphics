#include <GL/freeglut.h>
#include <cmath>

GLfloat vertices[3][3] = {
    {0.0, 0.0, 0.5}, // Vertex 1
    {1.0, 0.0, 0.0}, // Vertex 2
    {0.5, 1.0, 0.0}  // Vertex 3
};
GLfloat colors[3][3] = {
    {1.0f, 0.0f, 0.0f}, // Red for Vertex 1
    {0.0f, 1.0f, 0.0f}, // Green for Vertex 2
    {0.0f, 0.0f, 1.0f}  // Blue for Vertex 3
};

void Display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color
    for (int i = 0; i < 3; ++i)
    {
        glColor3fv(colors[i]);
        glVertex3fv(vertices[i]);
    }
    glEnd();
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
    glutCreateWindow("Shape Drawing");
    Initialize();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
