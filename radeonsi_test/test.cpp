#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    char *buf;

    buf = (char *)glGetString(GL_VERSION);
    std::cout << buf << std::endl;
}

void display(void)
{

    int i;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);               // 按顺时针绘制一个正方形，在右上方c
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0f, 0.0f, 0.0);
    glVertex3f(1.0, 0.0f, 0.0);
    glVertex3f(1.0, 1.0f, 0.0);
    glEnd();

    glFlush();

    exit(-1);
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM);
    glutInitWindowSize (480, 320);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("EE");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
