#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

void drawCircle(int x,int y,int r)
{
	glBegin(GL_POINTS);
		glVertex2f(x,y+r);
	glEnd();
	glFlush();
	int xk=0,yk=r;
	int P=1.25-r;
	while(xk<=yk)
	{
		xk++;
		if(P<0)
			P+=2*xk+3;	
		else
		{
			yk--;
			P+=2*xk-2*yk+5;
		}
		glBegin(GL_POINTS);
			glVertex2f(xk+x,yk+y);
			glVertex2f(yk+y,xk+x);
			glVertex2f(x-xk,y+yk);
			glVertex2f(y+yk,x-xk);
			glVertex2f(x-xk,y-yk);
			glVertex2f(y-yk,x-xk);
			glVertex2f(xk+x,y-yk);
			glVertex2f(y-yk,x+xk);
		glEnd();
		glFlush();
	}
}

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


void getPoints(int *x,int *y,int *r)
{
	printf("Enter X-Coordinate:");
	scanf("%d",x);
	printf("Enter Y-Coordinate:");
	scanf("%d",y);
	printf("Enter Radius:");
	scanf("%d",r);
	printf("\n\n");
}

void render()
{
	printf("Enter Coordinates for Center of circle\n");
	int x,y,r;
	getPoints(&x,&y,&r);
	drawCircle(x,y,r);
	drawCircle(x,y,2*r);
	drawLine(x,y-r,(int)(x+sqrt(3)*r),y-r);
	drawLine(x,y-r,(int)(x-sqrt(3)*r),y-r);
	drawLine(x,y+2*r,(int)(x+sqrt(3)*r),y-r);
	drawLine(x,y+2*r,x-sqrt(3)*r,y-r);
}

int main(int argc,char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(400,500);
	glutCreateWindow("Assignment2");
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(0,400,0,500);
	glutDisplayFunc(render);
	glutMainLoop();
}
