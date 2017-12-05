/**
 *	CP411 Assignment 4, adapted from assignment 3 and originally from A2 template from Dr. Fan
 */
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "InitShader.hpp"

#include "Camera.hpp"
#include "MenuHandler.hpp"
#include "Sphere.hpp"
#include "Universe.hpp"
#include <sstream>
#include <cstdlib>

void display(void) {
	if (myUniverse->collision){
		//game over
		Beep(500,500);
		Beep(400,500);
		Beep(300,500);
		stringstream message;
		message << "You dodged " << myUniverse->orbsPassed << " orbs! Would you like to play again?" << endl;
		if (::MessageBoxA(GetActiveWindow(), message.str().c_str(), "You Lose!", MB_YESNO) == 6){
			//replay
			delete myUniverse;
			myUniverse = new Universe();
			myUniverse->clock(); // start the animations
		}else{
			exit(0);
		}
	}
	myUniverse->myCamera->aspect = ((GLfloat) glutGet(GLUT_WINDOW_WIDTH))
			/ (glutGet(GLUT_WINDOW_HEIGHT) == 0 ? 0.01 : glutGet(GLUT_WINDOW_HEIGHT));
	myUniverse->myCamera->setProjectionMatrix();
	myUniverse->draw_world(); // draw all objects in the world
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("LightSpeed");

	myUniverse = new Universe();
	createMenu();

	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	myUniverse->myCamera->setDefaultCamera();
	myUniverse->myCamera->setProjectionMatrix();

	//init gl hidden surface removal
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);

	glewInit();
	GLuint SLProgramObject = InitShader("src/vertexshader.txt", "src/fragmentshader.txt");
	glUseProgram(SLProgramObject);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glutDisplayFunc(display);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myUniverse->clock(); // start the animations
	glutMainLoop();

	delete myUniverse;
	return 0;
}
