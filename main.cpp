#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct p
{
	GLfloat x,y;
}lPontos;

vector<lPontos> pontos(1000);
int nPontos = 0;
int isEditable = 0;
int Print = 0;



void inserePonto(int x, int y)
{
	pontos[nPontos].x = x;
	pontos[nPontos].y = y;
	nPontos++;
}

int procuraPontoProximo(int x, int y);

void inserePontoNoLugarCerto(int x, int y)
{	
	int i,j;
	int addeded = 0;
	float DistanciaMenorX = 9999999;
	float DistanciaMenorY = 9999999;
	int ponto = 50;
	if (nPontos >= 2 && procuraPontoProximo(x,y) == 1000)
	{
		for(i = 0; i<nPontos; i++)
		{
			float m = (pontos[i].y - pontos[i+1].y)/ (pontos[i].x - pontos[i+1].x);
			double yAplicadoReta = m*(x - pontos[i+1].y) + pontos[i+1].y;
			double xAplicadoReta = (y - pontos[i+1].y + m*pontos[i+1].x)/m;

	
			double distanciaY = abs(yAplicadoReta - y);
			double distanciaX = abs(xAplicadoReta - x);
				
			if(distanciaY < 10 && distanciaY < DistanciaMenorY)
			{
				if((x > pontos[i].x && x < pontos[i+1].x) || (x < pontos[i].x && x > pontos[i+1].x))
				{
					ponto = i;
					DistanciaMenorY = distanciaY;
				}
			}
			if(distanciaX < 10 && distanciaX < DistanciaMenorX)
			{
				if((y > pontos[i].y && y < pontos[i+1].y)||(y < pontos[i].y && y > pontos[i+1].y))
				{
					ponto = i;
					DistanciaMenorX = distanciaX;
				}
			}

		} 
		if(ponto < 50)
		{			

			for (j = nPontos; j>ponto; j--)
			{	
				pontos[j].x = pontos[j-1].x;
				pontos[j].y = pontos[j-1].y;
		
			}
			pontos[j+1].x = x;
			pontos[j+1].y = y;
			addeded = 1;
			nPontos++;
		}else
		{
			inserePonto(x,y);
		}
	}else
	{
		inserePonto(x,y);
	}
}


float distanciaPontos (int x1, int y1, int x2, int y2)
{
	float dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	return dist;
}

int procuraPontoProximo(int x, int y)
{
	int i;
	float maisProximoD = 5.0;
	int maisProximoI = 1000;
	for(i=0;i<nPontos;i++)
	{
		float distancia = distanciaPontos(pontos[i].x,pontos[i].y,x,y);
		if(distancia < maisProximoD)
		{
			maisProximoD = distancia;
			maisProximoI = i;
		}
	}
	return maisProximoI;
}
void removePontoProximo (int x, int y)
{
	int pontoProximo = procuraPontoProximo(x,500 -y);
	int i;
	if(pontoProximo != 1000)
	{
		for(i = pontoProximo; i < nPontos; i++)
		{
			pontos[i].x = pontos[i+1].x;
			pontos[i].y = pontos[i+1].y;
		}		
		nPontos--;
	}
}

void mouseClicks (int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && nPontos >= 2)
	{
		removePontoProximo(x,y);
		glutPostRedisplay();

		
	}	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && isEditable == 0 && procuraPontoProximo(x,500 - y) == 1000)
	{
		inserePontoNoLugarCerto(x,500 - y);
		glutPostRedisplay();
	}
}

void mouseArraste (int x, int y)
{
	int pontoProx = procuraPontoProximo(x, 500 - y);
	if(pontoProx < 1000)
	{
		pontos[pontoProx].x = x;
		pontos[pontoProx].y = 500 - y;	

		glutPostRedisplay();
	}
}

void display(void)
{
	int i;
 
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);

	if(distanciaPontos(pontos[0].x,pontos[0].y,pontos[nPontos-1].x,pontos[nPontos-1].y) < 10.0 && nPontos >= 3){
		nPontos--;
		Print = 1;
	   	isEditable = 1;
	}

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		for (i = 0; i < nPontos; i++)
		{
			glVertex2f(pontos[i].x,pontos[i].y);
		}
	glEnd();


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
		for (i = 0; i < nPontos; i++)
			glVertex2f(pontos[i].x,pontos[i].y);
	glEnd();

	if (Print == 1){
	   glColor3f(0.0, 1.0,0.0);
	   glBegin(GL_POLYGON);
		for (i = 0; i < nPontos; i++)
			glVertex2f(pontos[i].x,pontos[i].y);
	   glEnd();
		isEditable = 1;
	}
	glFlush();

	
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, -1 ,1);

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutMotionFunc(mouseArraste);
   glutMouseFunc(mouseClicks);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
