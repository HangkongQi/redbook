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

unsigned int trans_num = 2;

float trans = 0.0f;
float trans_flag = (1.0/trans_num);

void display(void)
{

    int i;
    glClearColor(0.0, 0.0, 0.0, 0.0);
	unsigned int texname;
	glGenTextures(1, &texname);

    for (i=0; i<trans_num; i++) {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(trans, 0, 0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);               // 按顺时针绘制一个正方形，在右上方c
        glVertex3f(0.0f, 0.0f, 0.0);
        glVertex3f(trans_flag, 0.0f, 0.0);
        glVertex3f(trans_flag, 0.1f, 0.0);
        glVertex3f(0.0f, 0.1f, 0.0);
        glEnd();
        glPopMatrix();
        trans = trans_flag + trans;
        glAccum(GL_ACCUM, trans_flag * (i+1));
    }

    glAccum(GL_RETURN, 1.0f);
    glFlush();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0, 1, -1, 1, -1, 1);
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
