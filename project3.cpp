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

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include<vector>
#include <GL/glut.h>				// include GLUT library
//***********************************************************************************
using std::cout;
using std::endl;
using std::vector;
using std::string;
// SCREEN GLOBALS //
const int WIDTH = 900;
const int HEIGHT = 700;
bool CONTROL = false;
bool JUMPING = false;

void myDisplayCallback();

double toRadians(double degrees) {
	return degrees * 3.14159 / 180;
}

double toDegrees(double radians){
    return radians * 180 / 3.14159;
}

void handleSleep(){
        #ifdef _WIN32
            Sleep(10);
        #else
            usleep(1000);
        #endif
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
        double view_field, ratio, near_view, far_view;

        double movement;

        void move();

    public:
        Camera(double view, double r, double n, double f){
            this->eyeX = -600;
            this->eyeY = 0;
            this->eyeZ = 50;
            this->directX = this->eyeX+100;
            this->directY = 0;
            this->directZ = this->eyeZ;;
            this->orientX = 0;
            this->orientY = 0;
            this->orientZ = 100;
            this->view_field = view;
            this->ratio = r;
            this->near_view = n;
            this->far_view = f;
            this->movement = 10;
        };

        double lookX(){ return this->directX; };
        double lookY(){ return this->directY; };
        double lookZ(){ return this->directZ; };
        double getEyeX(){ return this->eyeX; };

        void perspective(){
            glMatrixMode(GL_PROJECTION);
            gluPerspective(this->view_field, this->ratio, this->near_view, this->far_view);
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
        void forward();
        void backward();
        void mouseMove(int mx, int my);
        void jump();
};

void Camera::move(){
    glLoadIdentity();
    this->lookAt();
    //this->debug();
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

void Camera::forward(){
    double wall_stop = 0;
    if(this->eyeX+this->movement >= wall_stop)
        return;
    this->eyeX += this->movement;
    this->directX += this->movement;
    this->move();
}

void Camera::backward(){
    this->eyeX -= this->movement;
    this->directX -= this->movement;
    this->move();
}

void Camera::mouseMove(int mx, int my){
    this->directY = -((double)mx - (WIDTH/2));
    this->directZ = (HEIGHT/2) - (double)my;
    this->move();
}

void Camera::jump(){
    JUMPING = true;
    int jump_len = 40;
    for(int i = 0; i < jump_len; i++){
        this->directZ += 2;
        this->eyeZ += 2;
        this->move();
        handleSleep();
    }
    for(int i = jump_len; i > 0; i--){
        this->directZ -= 2;
        this->eyeZ -= 2;
        this->move();
        handleSleep();
    }

    JUMPING = false;
}

// CAMERA GLOBAL
Camera camera = Camera(120, 1, 0.1, 2000);

class Box
{
public:
	Box(int x, int y, int z, int side_len);
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
	void remove(){ this->render = false; };
	bool exists(){ return this->render; };
	void checkAndRemove();
private:
	int x;
	int y;
	int z;
	int side_len;
	bool render = true;
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


Box::Box(int x, int y, int z, int side_len) 
{
	setX(x);
	setY(y);
	setZ(z);
	setSideLen(side_len);
}

void Box::checkAndRemove(){
    if(this->y < camera.lookY() && (this->y+this->side_len) > camera.lookY() && this->z < camera.lookZ() && (this->z+this->side_len) > camera.lookZ()){
        this->remove();
    }
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
	glVertex3i(x, y, z + side_len);
	//far x-y parallel plane
	glColor3f(1, .5, .25);
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
	glVertex3i(x + side_len, y, z);
	glColor3f(0, 1, 0);
	glVertex3i(x, y, z + side_len);
	glVertex3i(x + side_len, y, z + side_len);


	glEnd();
}

void drawChar(int aChar, bool smallText = false) {
	if (smallText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, aChar);
	}
	else {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, aChar);
	}
}


// GLOBALS //

vector<vector<Box>> boxes;

// END GLOBALS //

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

void initBoxes(){
    int width = 25;
    int height = 15;
    int box_len = 50;
    int start_y = -(width*box_len/2);
    int y = start_y;
    int z = 0;
    for(int i=0; i < height; i++){
        vector<Box> temp;
        for(int j=0; j < width; j++){
            temp.push_back(Box(0, y, z, box_len));
            y += box_len;
        }
        boxes.push_back(temp);
        z += box_len;
        y = start_y;
        temp.clear();
    }
}

void drawMasterWall(){
    for(int i = 0; i < boxes.size(); i++){
        for(int j = 0; j < boxes.at(i).size(); j++){
            if(boxes.at(i).at(j).exists())
                boxes.at(i).at(j).draw();
        }
    }
}

void drawAimDot(){
    double x = camera.lookX();
    double y = camera.lookY();
    double z = camera.lookZ();
    double len = 2;
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3d(x, y+len, z-len);
    glVertex3d(x, y-len, z-len);
    glVertex3d(x, y-len, z+len);
    glVertex3d(x, y+len, z+len);
    glPointSize(1);
    glEnd();
}

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// draw the background

	drawCoordinateSystem();
    drawMasterWall();
    drawAimDot();

	glFlush(); // flush out the buffer contents
}

void handleKeys(unsigned char key, int cur_x, int cur_y){
    if(key == 27)
        CONTROL = false;
    if(!CONTROL || JUMPING)
        return;

    switch(key){
        case 'd':
            camera.right();
            break;
        case 'a':
            camera.left();
            break;
        case 'w':
            camera.forward();
            break;
        case 's':
            camera.backward();
            break;
        case ' ':
            camera.jump();
            break;
    }
}

void handleMouse(int curX, int curY){
    if(!CONTROL)
        return;
    camera.mouseMove(curX, curY);
}

void handleClick(int button, int state, int mx, int my){
    int x = (mx - (WIDTH/2));
    int y = (HEIGHT/2) - my;
    if(button == GLUT_LEFT_BUTTON){
        for(int i = 0; i < boxes.size(); i++){
            for(int j = 0; j < boxes.at(i).size(); j++){
                if(boxes.at(i).at(j).exists())
                    boxes.at(i).at(j).checkAndRemove();
            }
        }
        myDisplayCallback();
    }
}

// MENU GLOBALS
const int ACTIVATE = 1;
const int EXIT = 2;

void mainMenu(int id){
    switch(id){
        case ACTIVATE:
            CONTROL = true;
            break;
        case EXIT:
            exit(0);
    }
}

void handleSpecial(int key, int mx, int my){
    switch(key){
        case GLUT_KEY_END:
            CONTROL = false;
            break;
    }
}


//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background color: white 
camera.perspective();
glEnable(GL_DEPTH_TEST);
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
    glutInitWindowSize(WIDTH, HEIGHT);				// specify a window size
    glutInitWindowPosition(100, 0);			// specify a window position
    glutCreateWindow("3D Stuff");	// create a titled window

    myInit();

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Take Control", ACTIVATE);
    glutAddMenuEntry("Exit", EXIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(handleKeys);
    glutSpecialFunc(handleSpecial);
    glutPassiveMotionFunc(handleMouse);
    glutMouseFunc(handleClick);

    initBoxes();
    glutDisplayFunc(myDisplayCallback);	// register a callback
    glutMainLoop();							// get into an infinite loop
}
