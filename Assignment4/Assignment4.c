#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
GLint xstart=50,ystart=50;
GLint xend=450,yend=450;

typedef struct pixel
{
	GLfloat red;
	GLfloat blue;
	GLfloat green;
}pixel;

void boundry_fill(int x ,int y, pixel boundrycolor, pixel fillcolor)
{
	pixel c;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT, &c);
	//printf("%f - %f - %f\n",c.red,c.blue,c.green );
	if((c.red != boundrycolor.red || c.green != boundrycolor.green || c.blue !=
               boundrycolor.blue) && (c.red != fillcolor.red || c.green != fillcolor.green || c.blue !=
						                fillcolor.blue))
	{
		glColor3f(fillcolor.red,fillcolor.green,fillcolor.blue);
		glBegin(GL_POINTS);
  		      glVertex2f(x, y);
		glEnd();
		glFlush();
		boundry_fill(x+1,y, boundrycolor, fillcolor);
		boundry_fill(x-2,y, boundrycolor, fillcolor);
	  boundry_fill(x,y+2, boundrycolor, fillcolor);
	  boundry_fill(x,y-2, boundrycolor, fillcolor);
	}
}

void BresenhamLine(int x1,int y1,int x2,int y2){
	int dy=abs(y2-y1),dx=abs(x2-x1);
	int p,flag=0;
	if(dy>dx){
		flag=1;
		dy=dx+dy;
		dx=dy-dx;
		dy=(dy-dx);
		y1=x1+y1;
		x1=y1-x1;
		y1=(y1-x1);
		y2=x2+y2;
		x2=y2-x2;
		y2=(y2-x2);
	}
	int x=x1,y=y1;
	p=2*dy-dx;
	int inx,iny;
	if(x2>=x1)
		inx=1;
	else
		inx=-1;
	if(y2>=y1)
		iny=1;
	else
		iny=-1;
	glBegin(GL_POINTS);
	while(x!=x2 || y!=y2){
		if(p<=0){
			p=p+2*dy;
			x=x+inx;
		}else{
			p=p+2*(dy-dx);
			y=y+iny;
			x=x+inx;

		}
		glVertex2d((flag==0)?x:y,(flag==0)?y:x);
	}
	glEnd();
	glFlush();

}

void render(){


	pixel oldcolor;
	oldcolor.red =1.0;
	oldcolor.green = 0.0;
	oldcolor.blue = 0.0;

	pixel newcolor;
	newcolor.red =0.0;
	newcolor.green = 0.0;
	newcolor.blue = 0.0;

	glColor3f(oldcolor.red,oldcolor.green,oldcolor.blue);	//Color to use for for drawing objects - (R,G,B) values
	BresenhamLine(50,50,450,50);
	BresenhamLine(50,150,450,150);
	BresenhamLine(50,250,450,250);
	BresenhamLine(50,350,450,350);
	BresenhamLine(50,450,450,450);
	BresenhamLine(50,50,50,450);
	BresenhamLine(150,50,150,450);
	BresenhamLine(250,50,250,450);
	BresenhamLine(350,50,350,450);
	BresenhamLine(450,50,450,450);


	boundry_fill(51,51,oldcolor,newcolor);

}


int main(int argc, char **argv)
{
	glutInit(&argc,argv); // Initialise GLUT library
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	glutInitWindowSize(500,500);
  	glutInitWindowPosition(250,250); // Set the initial window position
  	glutCreateWindow("Assignment 4"); // Create window with title Assignment4
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	glutDisplayFunc(render);
	glutMainLoop();
}
