#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define shift 100


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

void render()
{
	printf("Enter Coordinates for Center of circle\n");
	int x,y,r;
	getPoints(&x,&y,&r);
	drawCircle(x,y,r);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(400,500);
	glutCreateWindow("Circle");
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(0,400,0,500);
	glutDisplayFunc(render);
	glutMainLoop();
	
}
