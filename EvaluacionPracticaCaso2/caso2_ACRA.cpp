#include <stdlib.h>
#include <GL/freeglut.h>
#include <cmath>
#include <stdio.h>

int numSegments = -1;
const float radius = 0.5f;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0.5, 1); // azul
    glBegin(GL_TRIANGLE_FAN);
        //Centro del circulo
        glVertex2f(0, 0);
        // Puntos del perimtero
        for(int i ; i <= numSegments; ++i){
            float angle = i * 2.0f * M_PI / numSegments;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            if(i % 2 == 0){
                glColor3f(0.0, 0.6, 0.7);
            }else{
                glColor3f(0.4, 0.2, 0.0);
            }
            glVertex2f(x, y);
        }
    glEnd();
    glFlush();
}

void init(){
    glClearColor(0, 0, 0, 1); // fondo negro
}

void ingresar_num_segmentos(){
    do{
        printf("Ingrese el numero de segmentos para el poligono (minimo: 1, maximo 14): \n");
        scanf("%d", &numSegments);
        if(numSegments <= 0 || numSegments > 14){
            printf("\nNumero de segmentos invalido, debe ser entre 1 y 14 \n");
        }
    }while(numSegments <= 0 || numSegments > 14);
}

int main(int argc, char** argv){
    ingresar_num_segmentos();
    glutInit(&argc, argv);
    glutCreateWindow("Ejemplo con GL_TRIANGLE_FAN y numero de segmentos variable");
    glutInitWindowSize(800, 800);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
