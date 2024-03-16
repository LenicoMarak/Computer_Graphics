#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

class CohenSathenLand
{
private:
    int xmin, xmax, ymin, ymax;

    void windowPoints(int wx, int wy, int hx, int hy)
    {
        this->xmin = wx;
        this->xmax = wx + hx;
        this->ymin = wy;
        this->ymax = wy + hy;
    }
    int computeRegion(int x, int y)
    {
        int regionCode = 0;
        if (x < xmin)
            regionCode |= (1 << 0); // 0001
        else if (x > xmax)
            regionCode |= (1 << 1); // 0010

        if (y < ymin)
            regionCode |= (1 << 2); // 0100
        else if (y > ymax)
            regionCode |= (1 << 3); // 1000

        return regionCode;
    }
    int *clipp(int x0, int y0, int x1, int y1)
    {
        int *vertex = new int[4];
        int accepted = false;
        while (true)
        {
            int regionStart = computeRegion(x0, y0);
            int regionEnd = computeRegion(x1, y1);
            if (regionStart == 0 && regionEnd == 0)
            {
                accepted = true;
                break;
            }
            if (regionStart & regionEnd != 0)
            {
                break;
            }
            int code = regionStart != 0 ? regionStart : regionEnd;
            int newX = 0, newY = 0;
            int slope = (y1 - y0) / (x1 - x0);
            if ((code & (1 << 0)) != 0)
            {
                newX = xmin;
                newY = y0 + slope * (newX - x0);
            }
            else if ((code & (1 << 1)) != 0)
            {
                newX = xmax;
                newY = y0 + slope * (newX - x0);
            }
            else if ((code & (1 << 2)) != 0)
            {
                newY = ymin;
                newX = x0 + slope * (newY - y0);
            }
            else if ((code & (1 << 3)) != 0)
            {
                newY = ymax;
                newX = x0 + slope * (newY - y0);
            }
            if (code == regionStart)
            {
                vertex[0] = newX;
                vertex[1] = newY;
            }
            else
            {
                vertex[2] = newX;
                vertex[3] = newY;
            }
        }
        if (accepted)
        {
            return vertex;
        }
        return NULL;
    }
};

void putPixelPoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    // Normalize coordinates
    glVertex2f((float)x / glutGet(GLUT_WINDOW_WIDTH), (float)y / glutGet(GLUT_WINDOW_WIDTH));
    glEnd();
}
void drawButton(int bx, int by, int bw, int bh, const unsigned char *text)
{
    GLfloat left = (float)bx / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat right = (float)by / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat top = (float)bw / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat bottom = (float)bh / glutGet(GLUT_WINDOW_WIDTH);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(left, right);
    glVertex2f(left + top, right);
    glVertex2f(left + top, right + bottom);
    glVertex2f(left, right + bottom);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, text);
    glRasterPos2f(left + (top - textWidth) / 2.0f, right + (bottom - 12) / 2.0f); // Center text
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
void bresenhamLine(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int pk = 2 * dy - dx;
    int x, y;
    if (x0 > x1)
    {
        x = x1;
        y = y1;
        x1 = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }
    while (x < x1)
    {
        putPixelPoint(x, y);
        if (pk < 0)
        {
            pk += 2 * dy;
        }
        else
        {
            pk += 2 * (dy - dx);
            y++;
        }
        x++;
    }
}
void drawLine(GLint x0, GLint y0, GLint x1, GLint y1)
{
    GLfloat sx = (float)x0 / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat sy = (float)y0 / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat dx = (float)x1 / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat dy = (float)y1 / glutGet(GLUT_WINDOW_WIDTH);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(sx, sy);
    glVertex2f(dx, dy);
    glEnd();
}
void drawWindow(GLint l, GLint r, GLint t, GLint b)
{
    GLfloat left = (float)l / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat right = (float)r / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat top = (float)t / glutGet(GLUT_WINDOW_WIDTH);
    GLfloat bottom = (float)b / glutGet(GLUT_WINDOW_WIDTH);
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red (optional)
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);
    glEnd();
}
void Display()
{
    CohenSathenLand obj;
    int sx1 = 50, sy1 = 250, dx1 = 450, dy1 = 350;
    int sx2 = 50, sy2 = 450, dx2 = 400, dy2 = 300;
    glClear(GL_COLOR_BUFFER_BIT);
    drawWindow(100, 350, 450, 200);
    drawButton(400, 200, 200, 50, reinterpret_cast<const unsigned char *>("Clipp"));
    bresenhamLine(sx1, sy1, dx1, dy1);
    drawLine(sx2, sy2, dx2, dy2);
    glFlush();
}
void buttonCallBack()
{
}
void Initialize()
{
    glClearColor(0.12f, 0.12f, 0.15f, 2.20f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // Set orthographic projection
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(450, 150);
    glutCreateWindow("Line Clipping Algorithm");
    Initialize();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
