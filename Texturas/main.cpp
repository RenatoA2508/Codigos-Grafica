#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <cstdlib>
// Definir colores
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define blue {0x00, 0x00, 0xff}

// Definir texturas
GLubyte texture [][3] = {
    blue, yellow,
    yellow, blue
};

static void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, GLfloat(width)/height, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
    //        x,y,z
    // Definir texturas
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D,
                 0, //Nivel 0
                 3, //Colores RGB
                 2,2, // Textura 2x2
                 0,  // no border
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    glTexCoord2f(0.5, 1.0); glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0); glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0); glVertex2f(0, 0);

    glTexCoord2f(0.5, 1.0); glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
    glTexCoord2f(1.0, 0.0); glVertex2f(3, 0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Ventana OpenGL");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
