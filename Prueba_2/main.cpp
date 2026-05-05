#include <GL/freeglut.h>

// Función de renderizado
void display() {
    // Limpiar la pantalla
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar un triángulo
    glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 0.0f, 0.0f); // rojo
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0.0f, 1.0f, 0.0f); // verde
        glVertex2f(0.5f, -0.5f);

        glColor3f(0.0f, 0.0f, 1.0f); // azul
        glVertex2f(0.0f, 0.5f);

    glEnd();

    // Forzar el renderizado
    glFlush();
}

// Configuración inicial
void init() {
    // Color de fondo (negro)
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {

    // Inicializar GLUT
    glutInit(&argc, argv);

    // Modo de visualización
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Tamaño de la ventana
    glutInitWindowSize(800, 600);

    // Posición de la ventana
    glutInitWindowPosition(100, 100);

    // Crear ventana
    glutCreateWindow("Prueba OpenGL - Triangulo");

    // Inicializar configuración
    init();

    // Registrar función de dibujo
    glutDisplayFunc(display);

    // Bucle principal
    glutMainLoop();

    return 0;
}
