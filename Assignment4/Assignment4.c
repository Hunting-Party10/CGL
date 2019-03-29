#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define shift 100
GLint xstart=125,ystart=125;
GLint xend,yend;
GLint size;

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
		//boundry_fill(x-2,y, boundrycolor, fillcolor);
	  boundry_fill(x,y+1, boundrycolor, fillcolor);
	  //boundry_fill(x,y-2, boundrycolor, fillcolor);
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
void drawbase()
{

	pixel oldcolor;
	oldcolor.red =1.0;
	oldcolor.green = 0.0;
	oldcolor.blue = 0.0;

	pixel newcolor;
	newcolor.red =0.0;
	newcolor.green = 0.0;
	newcolor.blue = 0.0;
	int i;
	int block = size/4;
	int offset = 0;
	xend =xstart + size;
	yend = ystart + size;
	glColor3f(oldcolor.red,oldcolor.green,oldcolor.blue);
	for(i = 0;i<5;i++)
	{
		BresenhamLine(xstart + offset,ystart,xstart + offset,yend);
		BresenhamLine(xstart,ystart + offset,xend,ystart + offset);
		offset += block;
	}
	offset =block;
	int y = ystart;
	boundry_fill(xstart+1,y+1,oldcolor,newcolor);
	boundry_fill(xstart + 2*offset+1,y+1,oldcolor,newcolor);
	y+=block;
	boundry_fill(xstart + offset + 1,y + 1,oldcolor,newcolor);
	boundry_fill(xstart + offset + offset + offset + 1,y + 1,oldcolor,newcolor);
	y+=block;
//	boundry_fill(xstart+1,y+1,oldcolor,newcolor);
//	boundry_fill(xstart + 2*offset+1,y+1,oldcolor,newcolor);
	y+=block;
//	boundry_fill(xstart + offset+1,y+1,oldcolor,newcolor);
//	boundry_fill(xstart + offset + offset + offset + 1,y + 1,oldcolor,newcolor);
/*
	for(i = 1; i<=4;i++)
	{
		if(i%2 != 0)
		{
			boundry_fill(xstart+1,y+1,oldcolor,newcolor);
			boundry_fill(xstart + 2*offset+1,y+1,oldcolor,newcolor);
		}
		else
		{
			boundry_fill(xstart + offset+1,y+1,oldcolor,newcolor);
			boundry_fill(xstart + 3*offset+1,y+1,oldcolor,newcolor);
		}
		y+=block;
	}

		//Color to use for for drawing objects - (R,G,B) values
	boundry_fill(xstart + 1 + shift,ystart + 1 + shift,oldcolor,newcolor);
	boundry_fill(126 + shift,ystart +1 + shift,oldcolor,newcolor);
	boundry_fill(76 + shift,76 + shift,oldcolor,newcolor);
	boundry_fill(176 + shift,76 + shift,oldcolor,newcolor);
	boundry_fill(xstart + 1 + shift,126 + shift,oldcolor,newcolor);
	boundry_fill(126 + shift,126 + shift,oldcolor,newcolor);
	boundry_fill(76 + shift,176 + shift,oldcolor,newcolor);
	boundry_fill(176 + shift,176 + shift,oldcolor,newcolor);
	*/
}
void render(){
	printf("Enter Chess Board Size :");
	scanf("%d",&size);
	drawbase();
}

void rotate()
{

}

void mousePoint(GLint button,GLint action,GLint xMouse,GLint yMouse){
/*	if(button == GLUT_LEFT_BUTTON || (button == GLUT_LEFT_BUTTON) && action == GLUT_DOWN)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	if(button == GLUT_RIGHT_BUTTON && action == GLUT_UP)
		rotate();
*/
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		drawbase();
		printf("Left Mouse Clicked");
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc,argv); // Initialise GLUT library
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   	// Set the initial display mode
  glutInitWindowSize(500,500);
  glutInitWindowPosition(250,250); // Set the initial window position
  glutCreateWindow("Assignment 4"); // Create window with title Assignment4
	glClearColor(1.0f,1.0f,1.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	glutDisplayFunc(render);
	glutMouseFunc(mousePoint);
	glutMainLoop();
}
