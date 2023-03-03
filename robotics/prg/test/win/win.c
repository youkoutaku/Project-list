#include <GL/glut.h>

void onRenderWin(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("test");
	glutDisplayFunc(onRenderWin);
	glClearColor(1.0, 0.8, 0.8, 0.0);
	glutMainLoop();
	return 0;
}
