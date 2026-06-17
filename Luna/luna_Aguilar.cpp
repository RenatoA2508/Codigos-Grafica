#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

float anguloTierraOrbita = 0.0f;
float anguloTierraRotacion = 0.0f;
float anguloLunaOrbita = 0.0f;
float anguloLunaRotacion = 0.0f;
float anguloSolRotacion = 0.0f;

void material(float r, float g, float b, float emision = 0.0f) {
    GLfloat difuso[] = {r, g, b, 1.0f};
    GLfloat ambiente[] = {r * 0.15f, g * 0.15f, b * 0.15f, 1.0f};
    GLfloat especular[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat emisivo[] = {r * emision, g * emision, b * emision, 1.0f};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, emisivo);
}

void dibujarMancha(float x, float y, float z, float tam, float r, float g, float b) {
    glPushMatrix();
        glTranslatef(x, y, z);
        material(r, g, b, 0.0f);
        glutSolidSphere(tam, 20, 20);
    glPopMatrix();
}

void dibujarSol() {
    material(1.0f, 0.65f, 0.05f, 0.35f);
    glutSolidSphere(1.7f, 80, 80);

    // Manchas solares
    dibujarMancha(1.45f, 0.45f, 0.35f, 0.18f, 0.75f, 0.25f, 0.0f);
    dibujarMancha(1.25f, -0.55f, -0.45f, 0.22f, 0.85f, 0.35f, 0.0f);
    dibujarMancha(0.55f, 1.20f, 0.60f, 0.14f, 0.9f, 0.4f, 0.0f);
    dibujarMancha(-0.8f, 0.75f, 1.10f, 0.16f, 0.8f, 0.3f, 0.0f);
}

void dibujarTierra() {
    material(0.0f, 0.25f, 1.0f);
    glutSolidSphere(0.8f, 60, 60);

    // Manchas verdes simulando continentes
    dibujarMancha(0.68f, 0.20f, 0.25f, 0.16f, 0.0f, 0.65f, 0.15f);
    dibujarMancha(0.55f, -0.25f, -0.45f, 0.18f, 0.0f, 0.55f, 0.10f);
    dibujarMancha(-0.30f, 0.35f, 0.65f, 0.13f, 0.0f, 0.70f, 0.20f);
    dibujarMancha(-0.60f, -0.15f, -0.35f, 0.14f, 0.0f, 0.60f, 0.10f);
}

void dibujarLuna() {
    material(0.72f, 0.72f, 0.72f);
    glutSolidSphere(0.30f, 50, 50);

    // Manchas/cráteres
    dibujarMancha(0.24f, 0.08f, 0.10f, 0.055f, 0.35f, 0.35f, 0.35f);
    dibujarMancha(0.18f, -0.10f, -0.18f, 0.045f, 0.40f, 0.40f, 0.40f);
    dibujarMancha(-0.10f, 0.18f, 0.20f, 0.040f, 0.45f, 0.45f, 0.45f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 7.0, 16.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    // Luz principal ubicada en el Sol
    GLfloat posicionLuz[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

    // Luz suave auxiliar para que el Sol tenga volumen visible
    GLfloat posicionLuzSol[] = {0.0f, 6.0f, 10.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, posicionLuzSol);

    // SOL
    glPushMatrix();
        glRotatef(anguloSolRotacion, 0.0f, 1.0f, 0.0f);
        dibujarSol();
    glPopMatrix();

    // TIERRA + LUNA
    glPushMatrix();

        glRotatef(anguloTierraOrbita, 0.0f, 1.0f, 0.0f);
        glTranslatef(5.7f, 0.0f, 0.0f);

        // Tierra
        glPushMatrix();
            glRotatef(anguloTierraRotacion, 0.0f, 1.0f, 0.0f);
            dibujarTierra();
        glPopMatrix();

        // Luna
        glPushMatrix();
            glRotatef(anguloLunaOrbita, 0.0f, 1.0f, 0.0f);
            glTranslatef(2.0f, 0.0f, 0.0f);

            glRotatef(anguloLunaRotacion, 0.0f, 1.0f, 0.0f);
            dibujarLuna();
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void timer(int v) {
    anguloTierraOrbita += 0.04f;
    anguloTierraRotacion += 0.35f;

    anguloLunaOrbita += 0.12f;
    anguloLunaRotacion += 0.12f;

    anguloSolRotacion += 0.08f;

    if (anguloTierraOrbita >= 360) anguloTierraOrbita -= 360;
    if (anguloTierraRotacion >= 360) anguloTierraRotacion -= 360;
    if (anguloLunaOrbita >= 360) anguloLunaOrbita -= 360;
    if (anguloLunaRotacion >= 360) anguloLunaRotacion -= 360;
    if (anguloSolRotacion >= 360) anguloSolRotacion -= 360;

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void reshape(GLint w, GLint h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, GLfloat(w) / GLfloat(h), 1.0, 50.0);
}

void init() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat luzDifusa[] = {1.0f, 0.95f, 0.75f, 1.0f};
    GLfloat luzAmbiente[] = {0.015f, 0.015f, 0.015f, 1.0f};
    GLfloat luzEspecular[] = {1.0f, 1.0f, 0.8f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.015f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.002f);

    // Luz auxiliar solo para que el Sol no se vea plano
    GLfloat luzSolDifusa[] = {0.35f, 0.25f, 0.15f, 1.0f};
    GLfloat luzSolAmbiente[] = {0.04f, 0.025f, 0.01f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzSolDifusa);
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzSolAmbiente);

    glClearColor(0.0f, 0.0f, 0.04f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Sistema Sol - Tierra - Luna con iluminacion");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);

    init();

    glutMainLoop();
    return 0;
}
