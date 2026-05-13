/*
 * GLUT Shapes example
 * Written by Mauricio Loachamin May 2025
 * Modified by Renato Aguilar May 2025
 */
#include <GL/glut.h>

static void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);        // Borramos la pantalla
    glMatrixMode(GL_PROJECTION);         // Modo proyección
    glLoadIdentity();                    // Cargamos la matriz identidad
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0); // Proyección ortográfica, dentro del cubo señalado

    glMatrixMode(GL_MODELVIEW);          // Modo de modelado

    glBegin(GL_QUADS);                   // Dibujamos un cuadrado
        glColor3f(1.0,1.0,0.0);          // Color para el cuadrado
        glVertex3f(-0.5,0.5,-0.5);       // Coordenadas del primer vértice (superior-izquierda)
        glVertex3f(-0.5,-0.5,0.5);       // Coordenadas del segundo vértice (inferior-izquierda)
        glVertex3f(0.5,-0.5,0.5);        // Coordenadas del primer vértice (inferior-derecha)
        glVertex3f(0.5,0.5,-0.5);        // Coordenadas del primer vértice (superior-derecha)
    glEnd();                             // Terminamos de dibujar
    glFlush();
}
static void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);        // Borramos la pantalla
    glMatrixMode(GL_PROJECTION);         // Modo proyección
    glLoadIdentity();                    // Cargamos la matriz identidad
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0); // Proyección ortográfica, dentro del cubo señalado

    gluPerspective(60.0,1.0,1.0,100.0);
    glTranslatef(0.0,0.0,-5.0);
    glMatrixMode(GL_MODELVIEW);          // Modo de modelado

    glBegin(GL_QUADS);                   // Dibujamos un cuadrado
        glColor3f(1.0,1.0,0.0);          // Color para el cuadrado
        glVertex3f(-0.5,0.5,-0.5);       // Coordenadas del primer vértice (superior-izquierda)
        glVertex3f(-0.5,-0.5,0.5);       // Coordenadas del segundo vértice (inferior-izquierda)
        glVertex3f(0.5,-0.5,0.5);        // Coordenadas del primer vértice (inferior-derecha)
        glVertex3f(0.5,0.5,-0.5);        // Coordenadas del primer vértice (superior-derecha)
    glEnd();                             // Terminamos de dibujar
    glFlush();
}
static void display3(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el color del buffer (background)

    glLineWidth(5);
    glBegin(GL_LINES); //dIBUJADO DE LINEAS
        glColor3f(1.0f, 0.0f, 1.0f);
        //Base
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        //Lado Izquierdo
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f,0.5f);
        //Lado Derecho
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f,0.5f);
    glEnd();
    glFlush(); // Render now
}
static void display4(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el color del buffer (background)

    glLineWidth(5);
    glBegin(GL_LINES); //dIBUJADO DE LINEAS
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(-0.35f, -0.2f);
        glVertex2f( 0.0f, 0.1f);

        glVertex2f(0.35f, -0.2f);
        glVertex2f(0.0f, 0.1f);

        glVertex2f(-0.35f, -0.2f);
        glVertex2f(-0.20f, 0.20f);

        glVertex2f(0.35f, -0.2f);
        glVertex2f(0.20f, 0.20f);

        glVertex2f(-0.20f, 0.20f);
        glVertex2f(-0.50f, 0.40f);

        glVertex2f(0.20f, 0.20f);
        glVertex2f(0.50f, 0.40f);

        glVertex2f(-0.50f, 0.40f);
        glVertex2f(-0.12f, 0.40f);

        glVertex2f(0.50f, 0.40f);
        glVertex2f(0.12f, 0.40f);

        glVertex2f(-0.12f, 0.40f);
        glVertex2f(0.0f, 0.80f);

        glVertex2f(0.12f, 0.40f);
        glVertex2f(0.0, 0.80f);

    glEnd();
    glFlush(); // Render now
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // Ventana 1
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Vista Ortogonal");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display1);

    // Ventana 2
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(550, 20);
    glutCreateWindow("Vista en Perspectiva");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display2);

    // Ventana 3
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(20, 400);
    glutCreateWindow("Triangulo");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display3);

    // Ventana 4
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(550, 400);
    glutCreateWindow("Estrella");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display4);

    glutMainLoop();

    return EXIT_SUCCESS;
}
