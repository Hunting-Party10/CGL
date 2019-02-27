#include <GL/glut.h>
#include<stdio.h>
#include <math.h>
#define shift 100

void drawLine(int x1,int y1,int x2,int y2)//Draws Lines between 2 points
{
	float dx=x2-x1;
	float dy=y2-y1;
	float steps;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	float xinc=dx/steps;
	float yinc=dy/steps;
	float x=x1;
	float y=y1;
	glBegin(GL_POINTS);
			glVertex2f(abs(x1), abs(y1));
		glEnd();
	int i;
	for(i=0;i<steps;i++)
	{
		x=x+xinc;
		y=y+yinc;
		glBegin(GL_POINTS);
			glVertex2f(abs(x), abs(y));
		glEnd();
		glFlush();
	}
		
}

void getPoints(int *x,int *y)
{
	printf("Enter X-Coordinate:");
	scanf("%d",x);
	printf("Enter Y-Coordinate:");
	scanf("%d",y);
	printf("\n\n");
}

void drawFig()
{
	int x1,x2,x3,x4,y1,y2,y3,y4;
	printf("For Point P1\n");
	getPoints(&x1,&y1);
	printf("For Point P2\n");
	getPoints(&x2,&y2);
	printf("For Point P3\n");
	getPoints(&x3,&y3);
	printf("For Point P4\n");
	getPoints(&x4,&y4);
	drawLine(x1,y1,x2,y2);
	drawLine(x2,y2,x3,y3);
	drawLine(x3,y3,x4,y4);
	drawLine(x4,y4,x1,y1);
	/*
	Calculation of the the points for the given set of lines
	*/
	int m1[]={(x1+x2)/2,(y1+y2)/2};
	int m2[]={(x2+x3)/2,(y2+y3)/2};
	int m3[]={(x3+x4)/2,(y3+y4)/2};
	int m4[]={(x1+x4)/2,(y1+y4)/2};
	int M1[]={(m1[0]+m2[0])/2,(m1[1]+m2[1])/2};
	int M2[]={(m2[0]+m3[0])/2,(m2[1]+m3[1])/2};
	int M3[]={(m3[0]+m4[0])/2,(m3[1]+m4[1])/2};
	int M4[]={(m1[0]+m4[0])/2,(m1[1]+m4[1])/2};
	drawLine(m1[0],m1[1],m2[0],m2[1]);
	drawLine(m2[0],m2[1],m3[0],m3[1]);
	drawLine(m3[0],m3[1],m4[0],m4[1]);
	drawLine(m1[0],m1[1],m4[0],m4[1]);
	drawLine(M1[0],M1[1],M2[0],M2[1]);
	drawLine(M2[0],M2[1],M3[0],M3[1]);
	drawLine(M3[0],M3[1],M4[0],M4[1]);
	drawLine(M1[0],M1[1],M4[0],M4[1]);
	
	/*
	printf("Exit?(Y/N)");
	char choice;
	scanf("%c",&choice);
	*/
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(400,500);//Window Size
  glutCreateWindow("DDA Method");
  glClearColor(0.0, 0.0, 0.0, 0.0);//Black Colour
  gluOrtho2D(0,400,0,500);//x-0 to 400 y-0 to 500
  glutDisplayFunc(drawFig);
  glutMainLoop();
}
