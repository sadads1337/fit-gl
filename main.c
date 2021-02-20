#include <GL/gl.h>
#include <GL/glut.h>

double rotate_y = 0;
double rotate_x = 0;

// redraw scene with changed variables
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    // front side
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);   // red
    glVertex3f(0.5, -0.5, -0.5);
    glColor3f(0.0, 1.0, 0.0);   // green
    glVertex3f(0.5, 0.5, -0.5);
    glColor3f(0.0, 0.0, 1.0);   // blue
    glVertex3f(-0.5, 0.5, -0.5);
    glColor3f(1.0, 0.0, 1.0);   // magenta
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
    // back side
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    // right side
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();
    // left side
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
    // top side
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    // bottom side
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

// without interact (timer)
void timer(int = 0) {
    display();
    glutTimerFunc(10, timer, 0);
}

// interact with the program
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            rotate_y += 5;
            break;
        case GLUT_KEY_LEFT:
            rotate_y -= 5;
            break;
        case GLUT_KEY_UP:
            rotate_x += 5;
            break;
        case GLUT_KEY_DOWN:
            rotate_x -= 5;
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CUBE");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -100, 100);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    timer();
    glutMainLoop();
    return 0;
}
