/*
 * GLUT Shapes Demo
 *
 * Written by Sebastian Chavez June 2026
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

static void initLightning(){
    //Definir los componentes de Luz
    GLfloat luz_ambiente[] = {0.8f, 0.2f, 0.2f, 1.0f};
    GLfloat   luz_difusa[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat posicion_luz[] = {1.0f, 1.0f, 1.0f, 0.0f};

    glEnable(GL_LIGHTING);

    //Activacion de las luces
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicion_luz);

    glEnable(GL_DEPTH_TEST);
}

static void display(void)
{
    //glClearColor(0,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glutSolidCube(0.5);
    //glutWireCube(0.5)
    //glutSolidSphere(0.5, 50, 50);
    glutSolidTeapot(0.5);
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(10,10);

    glutCreateWindow("GLUT Shapes");

    glutDisplayFunc(display);
    initLightning();

    glutMainLoop();

    return EXIT_SUCCESS;
}
