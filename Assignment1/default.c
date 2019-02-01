
#include <GL/glut.h>
#define max 200
#define shift 100
void outerSquare(void)		/* function called whenever redisplay needed */
{
  glClear(GL_COLOR_BUFFER_BIT);		/* clear the display */
  glColor3f(1.0, 1.0, 1.0);		/* set current color to white */
  glBegin(GL_LINE_STRIP);			
  glVertex2i(shift+1,shift+1);			
  glVertex2i(shift+1,shift+max);
  glVertex2i(shift+max,shift+max);
  glVertex2i(shift+max,shift+1);
  glVertex2i(shift+1,shift+1);
  glEnd();				/* OpenGL draws the filled triangle */
  glFlush();
  int mid=(max+shift+1+shift)/2;
  glBegin(GL_LINE_STRIP);			
  	glVertex2i(1+shift,mid);			
  	glVertex2i(mid,max+shift);
  	glVertex2i(max+shift,mid);
  	glVertex2i(mid,1+shift);
  	glVertex2i(1+shift,mid);
 	glEnd();				
  glEnd();
  glBegin(GL_LINE_STRIP);
  	glVertex2i((1+shift+mid)/2,(mid+max+shift)/2);
  	glVertex2i((mid+max+shift)/2,(mid+max+shift)/2);
  	glVertex2i((mid+max+shift)/2,(1+shift+mid)/2);
  	glVertex2i((1+shift+mid)/2,(1+shift+mid)/2);
  	glVertex2i((1+shift+mid)/2,(mid+max+shift)/2);
  glEnd();
  glFlush();	
}


int main(int argc, char *argv[])
{
  int win;

  glutInit(&argc, argv);		/* initialize GLUT system */

  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(400,500);		/* width=400pixels height=500pixels */
  win = glutCreateWindow("Assignment1");	/* create window */

  /* from this point on the current window is win */

  glClearColor(0.0,0.0,0.0,0.0);	/* set background to black */
  gluOrtho2D(0,400,0,500);		/* how object is mapped to window */
  glutDisplayFunc(outerSquare);		/* set window's display callback */	

  glutMainLoop();			/* start processing events... */

  /* execution never reaches this point */

  return 0;
}
