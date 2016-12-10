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
#include <GL/glut.h>				// include GLUT library
//***********************************************************************************
void myDisplayCallback();
//gluLookAt(60, 70, 60, 0, 0, 0, 0, 1, 0);
//gluPerspective(100, 1, 0, 400);

double toRadians(double degrees) {
	return degrees * 3.14159 / 180;
}

double toDegrees(double radians){
    return radians * 180 / 3.14159;
}

class Camera{
    private:
        // ORIGIN OF CAMERA COORD
        double eyeX, eyeY, eyeZ;

        // WHERE CAMERA LOOKS
        double directX, directY, directZ;

        // POINT ABOVE CAMERA
        double orientX, orientY, orientZ;

        // PERSPECTIVE VALUES
        double view_field, ratio, near, far;

        double movement;

        void move();

    public:
        Camera(double view, double r, double n, double f){
            this->eyeX = -200;
            this->eyeY = 25;
            this->eyeZ = 50;
            this->directX = 0;
            this->directY = 0;
            this->directZ = 0;
            this->orientX = 0;
            this->orientY = 0;
            this->orientZ = 100;
            this->view_field = view;
            this->ratio = r;
            this->near = n;
            this->far = f;
            this->movement = 10;
        };

        void perspective(){
            glMatrixMode(GL_PROJECTION);
            gluPerspective(this->view_field, this->ratio, this->near, this->far);
        };

        void lookAt(){
            glMatrixMode(GL_MODELVIEW);
            gluLookAt(this->eyeX, this->eyeY, this->eyeZ,
                    this->directX, this->directY, this->directZ,
                    this->orientX, this->orientY, this->orientZ);
        };
        void debug(){
            std::cout << "Camera Debug info: " << std::endl;
            std::cout << "Eye coord: (" << this->eyeX << ", " << this->eyeY << ", " << this->eyeZ << ")" << std::endl;
            std::cout << "direct coord: (" << this->directX << ", " << this->directY << ", " << this->directZ << ")" << std::endl;
            std::cout << "orient coord: (" << this->orientX << ", " << this->orientY << ", " << this->orientZ << ")" << std::endl;
        };

        void right();
        void left();
};

void Camera::move(){
    glLoadIdentity();
    this->lookAt();
    this->debug();
    myDisplayCallback();
};

void Camera::right(){
    this->eyeY -= this->movement;
    this->directY -= this->movement;
    this->move();
};

void Camera::left(){
    this->eyeY += this->movement;
    this->directY += this->movement;
    this->move();
};

// GLOBALS //

Camera camera = Camera(120, 1, 0.1, 500);

// END GLOBALS //

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

void handleKeys(unsigned char key, int cur_x, int cur_y){
    switch(key){
        case 'd':
            camera.right();
            break;
        case 'a':
            camera.left();
            break;
    }
}


//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background color: white 
//glOrtho(-500, 500, -500, 500, -500, 500);  // specify a viewing area
//gluPerspective(100, 1, 0, 400);
camera.perspective();
glEnable(GL_DEPTH_TEST);
//gluLookAt(60, 70, 60, 0, 0, 0, 0, 1, 0);
camera.lookAt();
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
    glutInitWindowSize(700, 600);				// specify a window size
    glutInitWindowPosition(100, 0);			// specify a window position
    glutCreateWindow("3D Stuff");	// create a titled window

    myInit();

    glutKeyboardFunc(handleKeys);

    glutDisplayFunc(myDisplayCallback);	// register a callback
    glutMainLoop();							// get into an infinite loop
}
