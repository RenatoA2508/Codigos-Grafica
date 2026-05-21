//Renato Aguilar, GR1CC Computación Gráfica
#include <GL/glut.h>
#include <cstdlib>

const int VerticesLobo = 126;

double Lobo[VerticesLobo][2] = {
    {0,  0.6},
    {-0.3,  0.55},
    {-0.60,  0.77},
    {-0.70,  0.90},
    {-0.77,  0.75},
    {-0.60,  0.77},
    {-0.5,  0.475},
    {-0.77,  0.75},
    {-0.77,  0.5},
    {-0.5,  0.475},
    {-0.3,  0.55},
    {0,  0.45},
    {-0.5,  0.475},
    {-0.77,  0.5},
    {-0.75,  0.4},
    {-0.5,  0.475},
    {-0.36,  0.3},
    {-0.55,  0.2},
    {-0.5,  0.475},
    {-0.75,  0.4},
    {-0.55,  0.2},
    {-0.9,  0.15},
    {-0.75,  0.4},
    {-0.9,  0.15},
    {-0.8,  -0.35},
    {-0.55,  0.2},
    {-0.40,  0.17},
    {-0.36,  0.3},
    {0,  0.45},
    {-0.15,  0.12},
    {-0.40,  0.17},
    {-0.38,  -0.11},
    {-0.55,  0.2},
    {-0.8,  -0.35},
    {-0.38,  -0.11},
    {-0.15,  0},
    {-0.40,  0.17},
    {-0.15,  0.12},
    {-0.15,  0},
    {0,  0},
    {-0.15,  0.12},
    {-0.15,  0},
    {-0.38,  -0.11},
    {-0.8,  -0.35},
    {-0.4,  -0.45},
    {-0.38,  -0.11},
    {-0.13,  -0.5},
    {-0.38,  -0.11},
    {0,  0},
    {0,  -0.39},
    {-0.38,  -0.11},
    {-0.4,  -0.45},
    {-0.13,  -0.5},
    {0,  -0.39},
    {-0.13,  -0.5},
    {-0.4,  -0.45},
    {-0.2,  -0.7},
    {-0.13,  -0.5},
    {-0.1,  -0.6},
    {-0.2,  -0.7},
    {0,  -0.7},
    {-0.1,  -0.6},
    {-0.2,  -0.7},
    {0,  -0.8},
    {0,  -0.7},
    {0,  -0.8},
    {0.2,  -0.7},
    {0,  -0.7},
    {0.1,  -0.6},
    {0.2,  -0.7},
    {0.4,  -0.45},
    {0.13,  -0.5},
    {0.2,  -0.7},
    {0.1,  -0.6},
    {0.13,  -0.5},
    {0,  -0.39},
    {0,  0},
    {0.38,  -0.11},
    {0,  -0.39},
    {0.13,  -0.5},
    {0.38,  -0.11},
    {0.4,  -0.45},
    {0.8,  -0.35},
    {0.38,  -0.11},
    {0.15,  0},
    {0, 0},
    {0.15,  0.12},
    {0.15,  0},
    {0.40,  0.17},
    {0.38,  -0.11},
    {0.55,  0.2},
    {0.8,  -0.35},
    {0.9,  0.15},
    {0.55,  0.2},
    {0.40,  0.17},
    {0.15,  0.12},
    {0, 0},
    {0,  0.45},
    {0.15,  0.12},
    {0.36,  0.30},
    {0.40,  0.17},
    {0.36,  0.30},
    {0.55,  0.20},
    {0.9,  0.15},
    {0.75,  0.40},
    {0.55,  0.2},
    {0.5,  0.475},
    {0.36,  0.3},
    {0,  0.45},
    {0.5,  0.475},
    {0.75,  0.40},
    {0.77,  0.50},
    {0.5,  0.475},
    {0.77,  0.50},
    {0.77,  0.75},
    {0.7,  0.90},
    {0.6,  0.77},
    {0.77,  0.75},
    {0.5,  0.475},
    {0.6,  0.77},
    {0.3,  0.55},
    {0.5,  0.475},
    {0,  0.45},
    {0.3,  0.55},
    {0,  0.6},
    {0,  0.45}
};




void PintarLineas(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
}


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

void PrepararEscena()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(2);
    glColor3f(0.7f, 1.0f, 0.2f);
}


static void displayLobo(void)
{
    PrepararEscena();

    PintarFigura(Lobo, VerticesLobo);

    glFlush();
}




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);


    glutInitWindowSize(300, 300);
    glutInitWindowPosition(20, 400);
    glutCreateWindow("Lobo con arreglo");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(displayLobo);


    glutMainLoop();

    return EXIT_SUCCESS;
}
