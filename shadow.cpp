#include "shadow.h"

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
	static bool firstRun = true;
	if (firstRun)
	{
		firstRun = false;
		gameController.setTimeOfInitCompleted();
	}

	static float lastTime=0;
	gameController.captureTimeSinceInitCompleted();

	if (gameController.userControlOn && (gameController.timeSinceInitCompleted - lastTime > 0.05))
	{
		lastTime = gameController.timeSinceInitCompleted;
		imageProcessor.render();
	}
	else
	{
		char msg[256];

		if (gameController.timeSinceInitCompleted < gameController.timeIntro)
			sprintf(msg, "Game starts in %d seconds...", int(gameController.timeIntro - gameController.timeSinceInitCompleted + 1));
		else
			sprintf(msg, "Press Enter to play!");

		imageProcessor.renderString(msg);
	}

	const float speed        = 1.0/7.0;
	const float stopInterval = 3.0;
	const float accel        = speed/stopInterval;
	const float crawlTime    = 32.0;
	const float gameStartPosition   = (crawlTime+stopInterval)*speed - stopInterval*stopInterval*accel/2.0;
	float globalCameraPosition;

	if (gameController.timeSinceInitCompleted < crawlTime)
        globalCameraPosition = gameController.timeSinceInitCompleted*speed;
	else if (gameController.timeSinceInitCompleted < crawlTime+stopInterval)
        globalCameraPosition = gameController.timeSinceInitCompleted*speed - (gameController.timeSinceInitCompleted-crawlTime)*(gameController.timeSinceInitCompleted-crawlTime)*accel/2.0;
    else
        globalCameraPosition = gameStartPosition;

	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,-globalCameraPosition,2.8,   0,1-globalCameraPosition,0.8,  0,0,1);

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

	crawler.render();
	interceptor.render();
    logo.render();

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
	imageProcessor.init();
	crawler.init();
	interceptor.init();
    logo.init();
}

void keyboard (unsigned char key, int x, int y)
{
	gameController.captureTimeSinceInitCompleted();

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		crawler.arrowTrollStartTimeSec = gameController.timeSinceInitCompleted;
		break;
	case 13:

		if ((gameController.timeSinceInitCompleted >= gameController.timeIntro)  && (gameController.timeGameStart < 0.0))
		{
            gameController.timeGameStart = gameController.timeSinceInitCompleted;
		} else {
            gameController.skipIntro();
            gameController.timeGameStart = gameController.timeSinceInitCompleted;
        }

		break;
	case 'w':
	case 'W':
		if (gameController.userControlOn) imageProcessor.virtualMouseDeltaY -= 0.05f;
		break;
	case 's':
	case 'S':
		if (gameController.userControlOn) imageProcessor.virtualMouseDeltaY += 0.05f;
		break;
	case 'a':
	case 'A':
		if (gameController.userControlOn) imageProcessor.virtualMouseDeltaX -= 0.05f;
		break;
	case 'd':
	case 'D':
		if (gameController.userControlOn) imageProcessor.virtualMouseDeltaX += 0.05f;
		break;
	default:
		break;
	}
}