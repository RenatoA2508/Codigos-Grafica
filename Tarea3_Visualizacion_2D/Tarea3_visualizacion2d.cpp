#include <GL/glut.h>
#include <cstdlib>

// Cantidad de vertices de cada figura
const int VerticesTriangulo = 3;
const int VerticesEstrella = 10;

// Arreglo de vertices del triangulo
double Triangulo[VerticesTriangulo][2] = {
    {-0.5, -0.5},
    { 0.5, -0.5},
    { 0.0,  0.5}
};

// Arreglo de vertices de la estrella
double Estrella[VerticesEstrella][2] = {
    {-0.35, -0.20},
    { 0.00,  0.10},
    { 0.35, -0.20},
    { 0.20,  0.20},
    { 0.50,  0.40},
    { 0.12,  0.40},
    { 0.00,  0.80},
    {-0.12,  0.40},
    {-0.50,  0.40},
    {-0.20,  0.20}
};

// Funcion que dibuja una linea entre dos puntos
void PintarLineas(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
}

// Funcion que recorre el arreglo de vertices y dibuja la figura
void PintarFigura(double Matriz[][2], int cantidadVertices)
{
    for (int i = 0; i < cantidadVertices; i++)
    {
        int siguiente = i + 1;
        // Si llega al ultimo vertice, vuelve al primero
        if (siguiente == cantidadVertices)
        {
            siguiente = 0;
        }
        PintarLineas(Matriz[i][0], Matriz[i][1], Matriz[siguiente][0], Matriz[siguiente][1]);
    }
}

// Configuracion comun para ambas ventanas
void PrepararEscena()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(5);
    glColor3f(0.7f, 1.0f, 0.2f);
}

// Ventana del triangulo
static void displayTriangulo(void)
{
    PrepararEscena();

    PintarFigura(Triangulo, VerticesTriangulo);

    glFlush();
}

// Ventana de la estrella
static void displayEstrella(void)
{
    PrepararEscena();

    PintarFigura(Estrella, VerticesEstrella);

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // Ventana 1: Triangulo
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(20, 400);
    glutCreateWindow("Triangulo con arreglo");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(displayTriangulo);

    // Ventana 2: Estrella
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(550, 400);
    glutCreateWindow("Estrella con arreglo");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(displayEstrella);

    glutMainLoop();

    return EXIT_SUCCESS;
}
