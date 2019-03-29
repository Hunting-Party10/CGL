#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define shift 100
GLint xstart=125,ystart=125;
GLint xend,yend;
GLint size;
double point[20][2];
double transform[2][2];

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
		boundry_fill(x,y+1, boundrycolor, fillcolor);

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

	glClear(GL_COLOR_BUFFER_BIT);
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
	int k = 0;
	glColor3f(oldcolor.red,oldcolor.green,oldcolor.blue);
	for(i = 0;i<5;i++)
	{
		BresenhamLine(xstart + offset,ystart,xstart + offset,yend);
		point[k][0] = xstart + offset - xstart;
		point[k][1] =ystart - ystart;
		k++;
		point[k][0] = xstart + offset - xstart;
		point[k][1] = yend - ystart;
		k++;
		BresenhamLine(xstart,ystart + offset,xend,ystart + offset);
		point[k][0] = xstart - xstart;
		point[k][1] = ystart + offset - ystart;
		k++;
		point[k][0] = xend - xstart;
		point[k][1] = ystart + offset - ystart;
		k++;

		offset += block;
	}
	offset =block;
	int y = ystart;
	//boundry_fill(xstart+1,y+1,oldcolor,newcolor);
//	boundry_fill(xstart + 2*offset+1,y+1,oldcolor,newcolor);
	y+=block;
	//boundry_fill(xstart + offset + 1,y + 1,oldcolor,newcolor);
	//boundry_fill(xstart + offset + offset + offset + 1,y + 1,oldcolor,newcolor);
	y+=block;
	//boundry_fill(xstart+1,y+1,oldcolor,newcolor);
	//boundry_fill(xstart + 2*offset+1,y+1,oldcolor,newcolor);
	y+=block;
	//boundry_fill(xstart + offset+1,y+1,oldcolor,newcolor);
	//boundry_fill(xstart + offset + offset + offset + 1,y + 1,oldcolor,newcolor);

}
void render(){
	printf("Enter Chess Board Size :");
	scanf("%d",&size);
}

void rotate()
{

	pixel oldcolor;
	oldcolor.red =1.0;
	oldcolor.green = 0.0;
	oldcolor.blue = 0.0;

	pixel newcolor;
	newcolor.red =0.0;
	newcolor.green = 0.0;
	newcolor.blue = 0.0;
	glClear(GL_COLOR_BUFFER_BIT);
	//printf("%lf-%lf\n",point[1][0],point[1][1]);
	transform[0][0] = transform[0][1] = transform[1][0] = transform [1][1] = 1/sqrt(2);
	transform[1][0] *= -1;
	int i;
	glColor3f(oldcolor.red,oldcolor.green,oldcolor.blue);
	//printf("%lf\n",(point[1][0] * transform[0][1] + point[1][1] * transform[1][1]));
	for(i = 0; i<20;i++)
	{
		int temp1 = (point[i][0] * transform[0][0] + point[i][1] * transform[1][0]);
		int temp2 = (point[i][0] * transform[0][1] + point[i][1] * transform[1][1]);
		point[i][0] = temp1;
		point[i][1] = temp2;
	}

	for(i = 0;i<20;i+=2)
	{
		BresenhamLine(point[i][0] + xstart,point[i][1] +ystart,point[i+1][0]+ xstart,point[i+1][1]+ ystart);
	}

}

void mousePoint(GLint button,GLint action,GLint xMouse,GLint yMouse){
	if(button == GLUT_RIGHT_BUTTON && action == GLUT_UP)
		rotate();
	if(button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		drawbase();
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);// Initialise GLUT library
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
