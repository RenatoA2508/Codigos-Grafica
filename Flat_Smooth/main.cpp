#include <GL/freeglut.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif // __APPLE__


bool smooth = true;

static void key(unsigned char key, int x, int y){
    switch(key){
        case 27:
            break;
        case 'q':
            exit(0);
            break;
        case 's':
            smooth = true;
            break;
        case 'f':
            smooth = false;
            break;
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if(smooth){
        glShadeModel(GL_SMOOTH);
    }else{
        glShadeModel(GL_FLAT);
    }

    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex2f(-0.8, -0.5); // Vertice 1
        glColor3f(0,1,0);
        glVertex2f(0.8, -0.5); // Vertice 2
        glColor3f(0,0,1);
        glVertex2f(0.0, 0.8); // Vertice 3
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("glut uSO DE gl_flat y gl_smooth");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}
