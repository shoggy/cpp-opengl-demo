#include <GL/freeglut.h>

#include <cstdlib>

constexpr unsigned char kEscKey = 27;

static void display() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.6f, -0.4f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.6f, -0.4f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.6f);
    glEnd();

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    if (h == 0) h = 1;
    if (w == 0) w = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float aspect = static_cast<float>(w) / static_cast<float>(h);
    if (aspect >= 1.0f) {
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    } else {
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    if (key == kEscKey) {
        glutLeaveMainLoop();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Colored Triangle");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return EXIT_SUCCESS;
}
