#include <GL/gl.h>
#include <GL/glut.h>

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
//    // glPolygonMode(GL_FRONT, GL_FILL); // 设置正面为填充模式
//    glPolygonMode(GL_BACK, GL_LINE);   // 设置反面为线形模式
//
//     glEnable(GL_CLIP_PLANE0);
//    double data[4] = {0, 0, 1, -0.5};
//    glClipPlane(GL_CLIP_PLANE0, data);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);               // 按顺时针绘制一个正方形，在右上方c
    glVertex3f(0.0f, 0.0f, 1.0);
    glVertex3f(0.0f, 1.0f, 0.0);
    glVertex3f(1.0f, 1.0f, 0.0);
    glEnd();

    glFlush();
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize (480, 320); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("EE");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
