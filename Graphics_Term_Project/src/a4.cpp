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

void display(void) {
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

void mouseAction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = true;
		xBegin = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
		myUniverse->normalizeAll();
	}
}

void standardKeys(unsigned char key, int x, int y) {
	if (key == 'w') { // accelerate
		cout << "w" << endl;
	} else if (key == 'a') { // turn left
		myUniverse->getShip().rotate_mc(0,1,0,5);
	} else if (key == 's') { // break
		cout << "s" << endl;
	} else if (key == 'd') { // turn right
		myUniverse->getShip().rotate_mc(0,1,0,-5);
	}
}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) { // roll left
		cout << "left" << endl;
	} else if (key == GLUT_KEY_RIGHT) { // roll right
		cout << "right" << endl;
	} else if (key == GLUT_KEY_UP) { // pitch fwd
		cout << "up" << endl;
	} else if (key == GLUT_KEY_DOWN) { // pitch backward
		cout << "down" << endl;
	}
}

void mouseMotion(GLint x, GLint y) {
	//GLfloat rx, ry, rz, theta;
	if (moving) {
		glutPostRedisplay();
	}

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("A4 Ryan Shanks)");

	myUniverse = new Universe();
	createMenu();

	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	myUniverse->myCamera->setDefaultCamera();
	myUniverse->myCamera->setProjectionMatrix();

	//init gl hidden surface removal
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glewInit();
	GLuint SLProgramObject = InitShader("src/vertexshader.txt", "src/fragmentshader.txt");
	glUseProgram(SLProgramObject);  // dont use the shader yet

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutKeyboardFunc(standardKeys);
	glutSpecialFunc(specialKeys);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	delete myUniverse;
	return 0;
}
