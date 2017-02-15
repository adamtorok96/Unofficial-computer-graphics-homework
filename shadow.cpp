#include "shadow.h"

Logo logo;

CameraWindow cameraWindow;

int main(int argc, char** argv)
{
    try
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(600, 600);
        glutInitWindowPosition(420, 0);
        glutCreateWindow("Press space to feed the troll :)");

        init();

        glutIdleFunc(idle);
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutMainLoop();
    }
    catch (const char *filename)
    {
        printf("Can't find %s.\n", filename);
    }

    return 0;
}

void display(void)
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 2.8, 0, 1, 0.8, 0, 0, 1);

	static const GLfloat lightColor[] = {1, 1, 1, 1.0};
	static const GLfloat lightPosition[4] = {0, -8, 20, 0};

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

    logo.render();
	cameraWindow.render();

	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 50.0);
}

void init(void)
{
    logo.init();
	cameraWindow.init();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		break;
	case 13:

		break;
	case 'w':
	case 'W':
		break;
	case 's':
	case 'S':
		break;
	case 'a':
	case 'A':
		break;
	case 'd':
	case 'D':
		break;
	default:
		break;
	}
}