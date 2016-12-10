/*==================================================================================================
 PROGRAMMER:			Nathan Kroll,
                        Thomas Kroll, kroll001
 COURSE:				CSC 525/625
 MODIFIED BY:			Nathan Kroll,
                        Thomas Kroll, kroll001
 LAST MODIFIED DATE:	12/5/2016
 DESCRIPTION:
 NOTE:					N/A
 FILES:					project3.cpp, (CSC525Labs.sln)
 IDE/COMPILER:			MicroSoft Visual Studio 2013
                        Vim/g++
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
 LINUX/G++ COMMAND LINE:
    1.      Open a terminal in the project directory
    2.      Execute command to COMPILE: g++ -std=c++11 project2.cpp -o PROJECT -lGL -lGLU -lglut
    3.      Execute command to EXECUTE: ./PROJECT
==================================================================================================*/
#include <cmath>
#include<string>
#include<iostream>
#include<vector>
#include <GL/glut.h>				// include GLUT library
//***********************************************************************************

using std::cout;
using std::endl;
using std::vector;
using std::string;

//class Vertex
//{
//public:
//	Vertex();
//	Vertex(float x, float y, float z);
//	Vertex& operator=(Vertex& v);
//	float X();
//	float Y();
//	float Z();
//	void setX(float x);
//	void setY(float y);
//	void setZ(float z);
//
//private:
//	float x;
//	float y;
//	float z;
//};
//Vertex::Vertex() {}
//Vertex::Vertex(float x, float y, float z)
//{
//	setX(x);
//	setY(y);
//	setZ(z);
//}
//Vertex& Vertex::operator=(Vertex& v)
//{
//	setX(v.X());
//	setY(v.Y());
//	setZ(v.Z());
//}
//float Vertex::X() { return this->x; }
//float Vertex::Y() { return this->y; }
//float Vertex::Z() { return this->z; }
//void Vertex::setX(float x) { this->x = x; }
//void Vertex::setY(float y) { this->y = y; }
//void Vertex::setZ(float z) { this->z = z; }


class Box
{
public:
	Box(int x, int y, int z, int side_len, int id);
	/*void setVertex(int i, Vertex v);
	void setVertex(int i, float x, float y, float z);*/
	int X();
	int Y();
	int Z();
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	void setSideLen(int len);
	int sideLen();
	void draw();
	int Id();
	void setId(int id);
private:
	int id;
	int x;
	int y;
	int z;
	int side_len;
	//vector<Vertex> vertices;
};

int Box::X() { return this->x; }
int Box::Y() { return this->y; }
int Box::Z() { return this->z; }
int Box::sideLen() { return this->side_len; }
void Box::setX(int x) { this->x = x; }
void Box::setY(int y) { this->y = y; }
void Box::setZ(int z) { this->z = z; }
void Box::setSideLen(int len) { this->side_len = len; }


Box::Box(int x, int y, int z, int side_len, int id) 
{
	setX(x);
	setY(y);
	setZ(z);
	setSideLen(side_len);
	setId(id);
}
void Box::draw()
{
	glBegin(GL_POLYGON);
	//top z-x parallel plane
	glColor3f(0, 1, 0);
	glVertex3i(x, y + side_len, z + side_len);
	glColor3f(1, .5, .25);
	glVertex3i(x, y + side_len, z);
	glVertex3i(x + side_len, y + side_len, z);

	glColor3f(0, 1, 0);
	glVertex3i(x + side_len, y + side_len, z + side_len);


	glColor3f(1, .5, .25);
	//far z-y parallel plane
	glVertex3i(x, y, z);
	glVertex3i(x, y + side_len, z);
	glColor3f(0, 1, 0);
	glVertex3i(x, y + side_len, z + side_len);
	glColor3f(1, .5, .25);
	glVertex3i(x, y, z + side_len);
	//far x-y parallel plane
	glVertex3i(x, y, z);
	glVertex3i(x, y + side_len, z);
	glVertex3i(x + side_len, y + side_len, z);
	glVertex3i(x + side_len, y, z);
	//near z-y parallel plane

	glColor3f(0, 1, 0);
	glVertex3i(x + side_len, y, z + side_len);
	glColor3f(1, .5, .25);
	glVertex3i(x + side_len, y + side_len, z);
	glVertex3i(x + side_len, y, z);
	glColor3f(0, 1, 0);
	glVertex3i(x + side_len, y + side_len, z + side_len);
	//near x-y paralled plane
	glVertex3i(x + side_len, y, z + side_len);
	glVertex3i(x, y, z + side_len);
	glVertex3i(x, y + side_len, z + side_len);
	glVertex3i(x + side_len, y + side_len, z + side_len);
	//far z-x parallel plane
	glColor3f(1, .5, .25);
	glVertex3i(x, y, z);
	glColor3f(0, 1, 0);
	glVertex3i(x, y, z + side_len);
	glVertex3i(x + side_len, y, z + side_len);
	glColor3f(1, .5, .25);
	glVertex3i(x + side_len, y, z);


	glEnd();
}
int Box::Id() { return this->id; }
void Box::setId(int i) { this->id = id; }
//void Box::setVertex(int i, Vertex v)
//{
//	if (i > 0 && i < 9)
//	{
//		vertices.at(i) = v;
//	}
//}
//void Box::setVertex(int i, float x, float y, float z)
//{
//	Vertex v(x, y, z);
//	if (i > 0 && i < 9)
//	{
//		vertices.at(i) = v;
//	}
//}

void drawChar(int aChar, bool smallText = false) {
	if (smallText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, aChar);
	}
	else {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, aChar);
	}
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
	return degrees * 3.14159 / 180;
}

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// draw the background

	drawCoordinateSystem();
	/*glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(shield_pattern);*/
	Box b1(0, 0, 0, 50, 0);
	b1.draw();
	Box b(50, 0, 0, 50, 1);
	b.draw();
	/*glPushMatrix();
	glTranslatef(50, 0, 0);
	glutSolidCube(50);*/
	/*glPopMatrix();*/

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
int  main()
{
    //====================================================================//
    // These lines are only here so I (Thomas) can work on this at home
    // since the only c++ compiler available to me is g++
    // (Visual Studio and Linux don't play well together)
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);
    //====================================================================//
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(400, 400);				// specify a window size
 glutInitWindowPosition(100, 0);			// specify a window position
 glutCreateWindow("3D Stuff");	// create a titled window

 myInit();		
glutDisplayFunc(myDisplayCallback);	// register a callback
 glutMainLoop();							// get into an infinite loop
}
