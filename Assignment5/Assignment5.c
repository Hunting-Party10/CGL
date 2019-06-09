
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
void line(int x1,int y1 ,int x2,int y2)
{
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


void render()
{
  glClearColor(1.0f,1.0f,1.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  //printf("");
  //scanf("%d")
  glColor3f(1.0f,0.0f,0.0f);
  line(200,200,100,100);
  glFlush();
}

int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(250,250);
  glutCreateWindow("Assignment5");
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,500,0,500);
  glutDisplayFunc(render);
  glutMainLoop();
}

/*
#include <GL/glut.h>
void init (void){
  glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
  glMatrixMode (GL_PROJECTION);       // Set projection parameters.
  gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}

void lineSegment (void){
  glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
  glColor3f (0.0, 0.4, 0.2);      // Set line segment color to green.
  glBegin (GL_LINES);
  glVertex2i (180, 15);       // Specify line-segment geometry.
  glVertex2i (10, 145);
  glEnd ( );
  glFlush ( );     // Process all OpenGL routines as quickly as possible.
}

void main (int argc, char** argv)
{
  glutInit (&argc, argv);                         // Initialize GLUT.
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
  glutInitWindowPosition (50, 100);   // Set top-left display-window position.
  glutInitWindowSize (400, 300);      // Set display-window width and height.
  glutCreateWindow ("An Example OpenGL Program"); // Create display window.
  init ( );                            // Execute initialization procedure.
  glutDisplayFunc (lineSegment);       // Send graphics to display window.
  glutMainLoop ( );                    // Display everything and wait.
}
*/
