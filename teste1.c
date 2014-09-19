#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>


typedef struct pontos {
	GLfloat ctrlpoints[3];
	int id;
}lPontos;

GLfloat ctrlpoints[4][3] = {
        { -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
        {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};

lPontos pontos[40];

int nPontos;

void display(void)
{

	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
		for(i=0;i<=30;i++)
			glEvalCoordif((GLfloat) i/30.0);
	glEnd();

	glPointSize(5.0);
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POINTS);
		for (i=0;i<4;i++)
			glVertex3fv(pontos->ctrlpoints);
	glEnd();
	glFlush();

}

void mouseClicks (int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Ponto");
	}
}
void mouseArraste (int x, int y)
{
	printf("Arrastei Clicado");
}
void init()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_FLAT);
	//glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3.4, &ctrlpoints[0][0]);
	//glEnable(GL_MAP1_VERTEX_3);
}

int main(int argc, char** argv)
{
	int index = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode 
	(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	glutMouseFunc(mouseClicks);
	glutMotionFunc(mouseArraste);
	init();
	glutDisplayFunc(display); 
	glutMainLoop();
	
	/* C ANSI requer que main retorne um inteiro */
	return 0;
}
