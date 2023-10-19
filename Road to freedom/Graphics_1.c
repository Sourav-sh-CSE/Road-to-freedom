#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>

void display()
{
	//clear the display
	//color black
	glClearColor(0, 0, 0, 0);

	//clear buffers to preset values
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/***************************
	/ set-up camera (view) here
	****************************/

	//load the correct matrix -- MODEL-VIEW matrix
	//specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?
	gluLookAt(0,0,100,	0,0,0,	0,1,0);

	//cirle
/*
glColor3f(0, 1, 0);
glBegin(GL_QUADS);
{
        glVertex3f(0, 0, 0);
	    glVertex3f(10, 0, 0);
	    glVertex3f(10, 20, 0);
	    glVertex3f(0, 20, 0);
}
glEnd();*/
	/*glColor3f(.85, 0, 0);
	double i;
	for(i=0;i<=2*3.14;i+=.2)
	{

	glBegin(GL_TRIANGLES);
	{
	     glVertex3f(0,0, 0);
	    glVertex3f(20*cos(i), 23*sin(i), 0);
	    glVertex3f(20*cos(i+.2), 23*sin(i+.2), 0);

	}
}
	glEnd();



	glColor3f(0, .6, .3);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-50, -40, 0);
	    glVertex3f(50, -40, 0);
	    glVertex3f(50, 40, 0);
	    glVertex3f(-50, 40, 0);
	}
	glEnd();*/
/*
		glColor3f(1, 0, 1);
	glBegin(GL_QUADS);
	{
	     glVertex3f(1, 17, 0);
	    glVertex3f(5, 17, 0);
	    glVertex3f(5, 21, 0);
	     glVertex3f(1, 21, 0);
	}
	glEnd();

	glColor3f(1, 0.5, 0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(0, 0, 0);
	    glVertex3f(20, 0, 0);
	    glVertex3f(20, 30, 0);
	    glVertex3f(0, 30, 0);
	}
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	{
	     glVertex3f(-10, 30, 0);
	    glVertex3f(30, 30, 0);
	    glVertex3f(10, 50, 0);

	    ;
	}
	glEnd();
*/

glutWireCube(30);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate()
{
	//codes for any changes in Models, Camera

	//this will call the display AGAIN
	glutPostRedisplay();
}

void init()
{
	//clear the screen
	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/

	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	/*glVertex3f(-50, -40, 0);
	    glVertex3f(50, -40, 0);
	    glVertex3f(50, 40, 0);
	    glVertex3f(-50, 40, 0);
	gluPerspective() — set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);

}

int main(int argc, char **argv)
{
	//initialize the GLUT library
	glutInit(&argc, argv);

	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("First_Lab!");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

