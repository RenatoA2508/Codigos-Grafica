#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* GLUT */
/*
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el color del buffer (background)
    glFlush(); // Render now
}

/* Programa Básico
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);              // Inicializar GLUT OpenGL
    glutInitDisplayMode(GLUT_RGB);      // Activar modo pantalla
    glutInitWindowSize(600,300);        // Tamaño de la ventana
    glutInitWindowPosition(0,0);        // Posición de la ventana en la pantalla
    glutCreateWindow("Ejemplo Básico"); // Crea la ventana
    glutDisplayFunc(display);           // Activa dibujado
    glClearColor(1.0,0.0,0.0,1.0);      // Color de fondo
    glutMainLoop();                     // Bucle principal
    return 0;
}
*/
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el color del buffer (background)

    glLineWidth(5);
    glBegin(GL_LINE_LOOP); //dIBUJADO DE LINEAS
        glColor3f(0.0f, 0.0f, 0.0f);
        /*Casa usando GL_LINES
        //Lado inferior
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        //Lado izquierdo
        glVertex2f( -0.5f, -0.5f);
        glVertex2f( -0.5f, 0.5f);
        //Lado derecho
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f, 0.5f);
        //Lado superior
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
        //Lado izquierdo techo
        glVertex2f( -0.5f,  0.5f);
        glVertex2f(0.0f,  0.8f);
        //Lado derecho techo
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(0.0f,  0.8f);
        //Lado izquierdo puerta
        glVertex2f( -0.1f,  -0.5f);
        glVertex2f(-0.1f,  -0.1f);
        //Lado derecho puerta
        glVertex2f(0.1f,  -0.5f);
        glVertex2f(0.1f,  -0.1f);
        //Lado superior puerta
        glVertex2f(-0.1f,  -0.1f);
        glVertex2f(0.1f,  -0.1f);
*/

        //Casa usando GL_LINE_STRIP
/*
        //Cuadrado
        glVertex2f(-0.5f,  0.5f);
        glVertex2f(-0.5f,  -0.5f);
        glVertex2f(0.5f,  -0.5f);
        glVertex2f(0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
        //Techo
        glVertex2f(0.0f,  0.8f);
        glVertex2f(0.5f,  0.5f);
        //Puerta
        glVertex2f(0.5f,  -0.5f);
        glVertex2f(0.1f,  -0.5f);
        glVertex2f(0.1f,  -0.1f);
        glVertex2f(-0.1f,  -0.1f);
        glVertex2f(-0.1f,  -0.5f);
*/


        //Casa usando GL_LINE_LOOP
        //Cuadrado
        glVertex2f(-0.5f,  0.5f);
        glVertex2f(-0.5f,  -0.5f);
        glVertex2f(0.5f,  -0.5f);
        glVertex2f(0.5f,  0.5f);
        //Techo
        glVertex2f(-0.5f,  0.5f);
        glVertex2f(0.0f,  0.8f);
        glVertex2f(0.5f,  0.5f);
        //Puerta
        glVertex2f(0.5f,  -0.5f);
        glVertex2f(0.1f,  -0.5f);
        glVertex2f(0.1f,  -0.1f);
        glVertex2f(-0.1f,  -0.1f);
        glVertex2f(-0.1f,  -0.5f);
        //Recolocación para regresar al punto original
        glVertex2f(-0.5f,  -0.5f);
    glEnd();

    glFlush(); // Render now
}

/* Program Básico */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);              // Inicializar GLUT OpenGL
    glutInitDisplayMode(GLUT_RGB);      // Activar modo pantalla
    glutInitWindowSize(300,300);        // Tamaño de la ventana
    glutInitWindowPosition(0,0);        // Posición de la ventana en la pantalla
    glutCreateWindow("Ejemplo Básico"); // Crea la ventana
    glutDisplayFunc(display);           // Activa dibujado
    glClearColor(1.0,1.0,1.0,1.0);      // Color de fondo
    glutMainLoop();                     // Bucle principal
    return 0;
}
