/*==================================================================================================
 PROGRAMMER:			Nathan Kroll
 COURSE:				CSC 525/625
 MODIFIED BY:			Nathan Kroll
 LAST MODIFIED DATE:	12/5/2016
 DESCRIPTION:			Lab 14: Drawing a 3D triangular pipe, using the correct methods to generate the polygons in the right order every time. Rotating around different axis
 NOTE:					N/A
 FILES:					lab14.cpp, (CSC525Labs.sln)
 IDE/COMPILER:			MicroSoft Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <cmath>
#include<string>
#include<iostream>
#include <GL/glut.h>				// include GLUT library
//***********************************************************************************

GLdouble vertex[6][3] = 
{
	{ 60, 55, 40 },
	{ 60, -50, 40},
	{ 65, 90, -70},
	{ 65, 0, -70 },
	{ -70, 70, 20},
	{ -70, -20, 20}
};


void drawChar(int aChar, bool smallText = false) {
	if (smallText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, aChar);
	}
	else {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, aChar);
	}
}

void drawRed() {
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3dv(vertex[0]);
	glVertex3dv(vertex[1]);
	glVertex3dv(vertex[3]);
	glVertex3dv(vertex[2]);
	glEnd();
}

void drawBlue() {
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glFrontFace(GL_CCW);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3dv(vertex[0]);
	glVertex3dv(vertex[4]);
	glVertex3dv(vertex[5]);
	glVertex3dv(vertex[1]);
	glEnd();
}

void drawGreen() {
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glFrontFace(GL_CW);
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3dv(vertex[2]);
	glVertex3dv(vertex[4]);
	glVertex3dv(vertex[5]);
	glVertex3dv(vertex[3]);
	glEnd();

}
void drawPolygons() 
{
	drawRed();
	drawGreen();
	drawBlue();

}

void drawCoordinateSystem() {
	glPointSize(1);		// change point size back to 1

	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x = -150; x <= 150; x++) // draw X-axis
		glVertex3i(x, 0, 0);
	for (int y = -150; y <= 150; y++) // draw Y-axis
		glVertex3i(0, y, 0);
	for (int z = -150; z <= 150; z++) // draw Z-axis
		glVertex3i(0, 0, z);
	glEnd();
	glRasterPos3i(5, 140, 0);
	drawChar('Y', true);
	glRasterPos3i(140, 5, 0);
	drawChar('X', true);
	glRasterPos3i(10, 0, 140);
	drawChar('Z', true);
}

float toRadians(float degrees) {
	return degrees * 3.1459 / 180;
}

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// draw the background

	drawCoordinateSystem();
	drawPolygons();

	glFlush(); // flush out the buffer contents
}

void rotateX(float angle) {
	float radians = toRadians(angle);
	GLdouble matrix[] =
	{
		1, 0, 0, 0,
		0, cos(radians), sin(radians), 0,
		0, -sin(radians), cos(radians), 0,
		0, 0, 0, 1
	};
	glMultMatrixd(matrix);
	myDisplayCallback();
}

void rotateY(float angle) {
	float radians = toRadians(angle);
	GLdouble matrix[] =
	{
		cos(radians), 0, -sin(radians), 0,
		0, 1, 0, 0,
		sin(radians), 0, cos(radians), 0,
		0, 0, 0, 1
	};
	glMultMatrixd(matrix);
	myDisplayCallback();
}

void rotateZ(float angle) {
	float radians = toRadians(angle);
	GLdouble matrix[] =
	{
		cos(radians), sin(radians), 0, 0,
		-sin(radians), cos(radians), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	glMultMatrixd(matrix);
	myDisplayCallback();
}

void rotateMenuCallback(int entryId) {
	switch (entryId) {
	case 0:
		rotateX(45);
		break;
	case 1:
		rotateX(-45);
		break;
	case 2:
		rotateY(45);
		break;
	case 3:
		rotateY(-45);
		break;
	case 4:
		rotateZ(45);
		break;
	case 5:
		rotateZ(-45);
		break;
	case 6:
		glLoadIdentity();
		gluLookAt(60, 70, 60, 0, 0, 0, 0, 1, 0);
		myDisplayCallback();
		break;
	case 7:
		exit(0);
	}
}

void createMenus() {
	glutCreateMenu(rotateMenuCallback);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("Rotate around X-axis 45 degrees", 0);
	glutAddMenuEntry("Rotate around X-axis -45 degrees", 1);
	glutAddMenuEntry("Rotate around Y-axis 45 degrees", 2);
	glutAddMenuEntry("Rotate around Y-axis -45 degrees", 3);
	glutAddMenuEntry("Rotate around Z-axis 45 degrees", 4);
	glutAddMenuEntry("Rotate around Z-axis -45 degrees", 5);
	glutAddMenuEntry("Reset", 6);
	glutAddMenuEntry("Exit", 7);
}

//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background color: white 
glMatrixMode(GL_PROJECTION);
glOrtho(-200, 200, -200, 200, -200, 200);  // specify a viewing area
glEnable(GL_DEPTH_TEST);
glMatrixMode(GL_MODELVIEW);
gluLookAt(60, 70, 60, 0, 0, 0, 0, 1, 0);
}

//***********************************************************************************

//***********************************************************************************
void main()
{
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(400, 400);				// specify a window size
 glutInitWindowPosition(100, 0);			// specify a window position
 glutCreateWindow("3D Stuff");	// create a titled window
 createMenus();

 myInit();		
glutDisplayFunc(myDisplayCallback);	// register a callback
 glutMainLoop();							// get into an infinite loop
}
