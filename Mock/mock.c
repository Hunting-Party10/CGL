#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
const GLint width =30;
const GLint height =90;
const GLint shift = 250;
double point[40][2];
double transform[2][2];
int c = 0;
//const GLint offset = 250;
int flag=0;
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
		boundry_fill(x-1,y, boundrycolor, fillcolor);
		boundry_fill(x,y+1, boundrycolor, fillcolor);
		boundry_fill(x,y-1, boundrycolor, fillcolor);

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
	glVertex2d((flag==0)?x:y,(flag==0)?y:x);
	while(x!=x2 || y!=y2){
		if(p<=0){
			p=p+2*dy;
			x=x+inx;
		}else{
			p=p+2*(dy-dx);
			y=y+iny;
			x=x+inx;

		}
		glVertex2i((flag==0)?x:y,(flag==0)?y:x);
	}
	glEnd();
	glFlush();

}

void store(int x1,int y1,int x2,int y2)
{
	point[c][0] = x1 -shift;
	point[c][1] = y1 -shift;
	c++;
	point[c][0] = x2 -shift;
	point[c][1] = y2 -shift;
	c++;
}

void drawbase()
{
	glClearColor(1.0f,1.0f,1.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f,0.0f,0.0f);
  GLint x1,y1,x2,y2;
  x1 = shift + width/2 ;
  y1 = shift + (width/2) ;
  x2 = x1 ;
  y2 = height + shift ;
  BresenhamLine(x1,y1,x2,y2); //Level 1
	store(x1,y1,x2,y2);
	BresenhamLine(x2,y2,x2+height,y2);//Level 2
	store(x2,y2,x2+height,y2);
	BresenhamLine(x1,y1,y2 + width,x2);//level 1
	store(x1,y1,y2 + width,x2);
	BresenhamLine(y2 + width,x2,y2 + width,x2 - height - width);//level2
	store(y2 + width,x2,y2 + width,x2 - height - width);
	GLint tempx1 = y2 + width;
	GLint tempx2 = x2 - height - width;
	GLint tempy1 = x2+height;
	GLint tempy2 = y2;
	x1 = width/2 +shift;
	y1 = width/2 *-1 +shift;
	x2 = height +shift;
	y2 = y1;
	BresenhamLine(x1,y1,x2,y2);//level1
	store(x1,y1,x2,y2);
	BresenhamLine(x2,y2,x2,y2 -height);//level2
	store(x2,y2,x2,y2 -height);
	BresenhamLine(tempx1,tempx2,x2,y2 -height);//level3
	store(tempx1,tempx2,x2,y2 -height);
	BresenhamLine(x1,y1,x1,height*-1 -width + shift);//level1
	store(x1,y1,x1,height*-1 -width + shift);
	BresenhamLine(x1,height*-1 -width + shift,x1-width-height,height*-1 -width + shift);//level2
	store(x1,height*-1 -width + shift,x1-width-height,height*-1 -width + shift);
	tempx1 = x1-width-height;
	tempx2 = height*-1 -width + shift;

	x1 = width/2*-1 +shift;
	y1 = width/2 *-1 +shift;
	x2 = x1;
	y2 = -1 *height +shift;
	BresenhamLine(x1,y1,x2,y2);//level1
	store(x1,y1,x2,y2);
	BresenhamLine(x2,y2,x2-height,y2);//level2
	store(x2,y2,x2-height,y2);
	BresenhamLine(x2-height,y2,tempx1,tempx2);//level3
	store(x2-height,y2,tempx1,tempx2);
	BresenhamLine(x1,y1,y2-width,x2);//level1
	store(x1,y1,y2-width,x2);
	BresenhamLine(y2-width,x2,y2-width,x2+width+height);//level2
	store(y2-width,x2,y2-width,x2+width+height);
	tempx1 = y2-width;
	tempx2 =x2+width+height;
	x1 = width/2*-1 +shift;
	y1 = width/2 +shift;
	x2 = -1*height + shift;
	y2 = y1 ;
	BresenhamLine(x1,y1,x2,y2);//level1
	store(x1,y1,x2,y2);
	BresenhamLine(x2,y2,x2,y2+height);//level2
	store(x2,y2,x2,y2+height);
	BresenhamLine(x2,y2+height,tempx1,tempx2);//level3
	store(x2,y2+height,tempx1,tempx2);
	BresenhamLine(x1,y1,x1,height + width +shift);//level1
	store(x1,y1,x1,height + width +shift);
	BresenhamLine(x1,height + width +shift,x1+width+height,height + width +shift);//level2
	store(x1,height + width +shift,x1+width+height,height + width +shift);

	BresenhamLine(tempy1,tempy2,x1+width+height,height + width +shift);
	store(tempy1,tempy2,x1+width+height,height + width +shift);
	pixel boundrycolor;
	boundrycolor.red =1.0;
	boundrycolor.green =0.0;
	boundrycolor.blue =0.0;
	pixel fillcolor;
	fillcolor.red =0.0;
	fillcolor.green =0.0;
	fillcolor.blue =0.0;

	boundry_fill(250,250,boundrycolor,fillcolor);
}

void rotate()
{
	glClear(GL_COLOR_BUFFER_BIT);
	transform[0][0] = transform[0][1] = transform[1][0] = transform [1][1] = 1/sqrt(2);
	transform[1][0] *= -1;
	int i;
	for(i = 0; i<c;i++)
	{
		int temp1 = (point[i][0] * transform[0][0] + point[i][1] * transform[1][0]);
		int temp2 = (point[i][0] * transform[0][1] + point[i][1] * transform[1][1]);
		point[i][0] = temp1;
		point[i][1] = temp2;
	}
	glColor3f(1.0f,0.0f,0.0f);
	for(i = 0;i<c;i+=2)
	{
		BresenhamLine(point[i][0] + shift,point[i][1] + shift ,point[i+1][0] + shift,point[i+1][1] + shift);
	}
	pixel boundrycolor;
	boundrycolor.red =1.0;
	boundrycolor.green =0.0;
	boundrycolor.blue =0.0;
	pixel fillcolor;
	fillcolor.red =0.0;
	fillcolor.green =0.0;
	fillcolor.blue =0.0;
	boundry_fill(250,250,boundrycolor,fillcolor);
}

void render()
{
  drawbase();
}

void onClick(GLint button,GLint action,GLint x,GLint y)
{
//	printf("%d %d\n",x,y);
  if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
  {
    if(flag == 1){
      drawbase();
      flag= 0;
    }
    else
    {
        flag = 1;
	rotate();
	c = 0;
    }

  }
}

int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(250,250);
  glutCreateWindow("CG Mock");
	glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,500,0,500);
  glutDisplayFunc(render);
  glutMouseFunc(onClick);
  glutMainLoop();
}
