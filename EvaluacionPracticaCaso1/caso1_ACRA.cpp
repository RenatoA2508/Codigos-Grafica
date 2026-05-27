/*Rotación y traslación*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
//Variables
int x, y;
int where_to_rotate = 0; //Hace que no rote inicialmente
int what_to_draw = 0; // que figura dibujar
float rotate_angle = 0; // angulo inicial
float translate_x = 0, translate_y = 0; // traslacion inicial

void draw_pixel(float xl, float yl){
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(xl, yl); // Dibuja un unico punto de tamaño 5
    glEnd();
}

void triangle(int x, int y){ // Coordenadas iniciales
    glColor3f(1, 0, 0); // Rojo, verde, azul
    glBegin(GL_POLYGON); //Dibujando un triangulo
    glVertex2f(x, y); //Punto inicial (esquina izquierda)
    glVertex2f(x + 400, y + 300); // esquina superior
    glVertex2f(x + 300, y + 0); // esquina derecha
    glEnd();
}

void pentagon(int x, int y){ // Coordenadas iniciales
    glColor3f(0, 0, 1); // Rojo, verde, azul
    glBegin(GL_POLYGON); //Dibujando un triangulo
    glVertex2f(x, y); //Punto inicial (esquina inferior izquierda)
    glVertex2f(x + 400, y); // esquina inferior derecha
    glVertex2f(x + 500, y + 300); // esquina superior derecha
    glVertex2f(x + 200, y + 500); // esquina superior
    glVertex2f(x - 100, y + 300); // esquina superior izquierda
    glEnd();
}

void square(int x, int y){ // Coordenadas iniciales
    glColor3f(0, 1, 0); // Rojo, verde, azul
    glBegin(GL_POLYGON); //Dibujando un triangulo
    glVertex2f(x, y); //Punto inicial (esquina inferior izquierda)
    glVertex2f(x + 400, y); // esquina inferior derecha
    glVertex2f(x + 400, y + 400); // esquina superior derecha
    glVertex2f(x, y + 400); // esquina superior izquierda
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1, 1, 1); // Punto origen de color Blanco
    draw_pixel(0, 0); // punto origen
    if(where_to_rotate == 1){ // Rotar en el origen (1 -> opcion escogida)
        translate_x = 0;
        translate_y = 0;
        rotate_angle += 2; // Cantidad del angulo de rotacion, mas alto el numero, mas rapido rota. Positivo - antihorario, negativo - horario
    }

    if(where_to_rotate == 2){ // Rotar sobre un punto fijo (2 -> opcion escogida)
        translate_x = x; //Coloca la traslacion donde se haya especificado
        translate_y = y;
        rotate_angle += 2; // Cantidad del angulo de rotacion, mas alto el numero, mas rapido rota. Positivo - antihorario, negativo - horario
        glColor3f(0, 0, 1); // Coordenada del usuario de color azul
        draw_pixel(x, y);
    }

    // Traslaciones y rotaciones reales
    glTranslatef(translate_x, translate_y, 0);
    glRotatef(rotate_angle, 0, 0, 1);
    glTranslatef(-translate_x, -translate_y, 0);
    // Escoger que figura se dibuja
    if (what_to_draw == 1)
        triangle(translate_x, translate_y);
    if (what_to_draw == 2)
        pentagon(translate_x, translate_y);
    if (what_to_draw == 3)
        square(translate_x, translate_y);

    glutPostRedisplay(); //LLama a la funcion display una y otra vez
    glutSwapBuffers(); //Muestra la salida
}

void init(){
    glClearColor(0, 0, 0, 1); // negro
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-800, 800, -800, 800);
    glMatrixMode(GL_MODELVIEW);
}

void rotate_menu(int option){
    if(option == 1){
        where_to_rotate = 1; // Rotar en el origen
    }
    if(option == 2){
        where_to_rotate = 2; // Rotar en un punto especificado
    }
    if(option == 3){
        where_to_rotate = 0; // Parar rotacion
    }
}

void draw_menu(int option){
    if(option == 1) // Dibujar triangulo
        what_to_draw = 1;
    if(option == 2) // Dibujar pentagono
        what_to_draw = 2;
    if(option == 3) // Dibujar cuadrado
        what_to_draw = 3;
    rotate_angle = 0;       // reinicia la rotacion
    where_to_rotate = 0;    // aparece quieta primero
    glutPostRedisplay();
}

int main(int argc, char **argv){
    printf("Ingrese un punto fijo (x, y) para la rotacion: \n");
    scanf("%d %d", &x, &y); // Guarda las coordenadas del usuario
    glutInit(&argc, argv); // Inicializa graficos del sistema
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Crear y rotar triangulo");
    init();
    glutDisplayFunc(display);
    //Menu
    int sub_menu = glutCreateMenu(rotate_menu);
    glutAddMenuEntry("Rotar en el origen", 1);
    glutAddMenuEntry("Rotar sobre un punto fijo", 2);
    glutAddMenuEntry("Detener rotacion", 3);

    int main_menu = glutCreateMenu(draw_menu);
    glutAddSubMenu("abrir sub menu", sub_menu);
    glutAddMenuEntry("Dibujar triangulo", 1);
    glutAddMenuEntry("Dibujar pentagono", 2);
    glutAddMenuEntry("Dibujar cuadrado", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
