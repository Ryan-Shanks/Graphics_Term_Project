/*
 * MenuHanlder.cpp
 * Goal is to separate the menu functions and global variables from the rest of the main functions
 *  Created on: Nov 9, 2017
 *      Author: ryanw
 */
#ifndef CMENUHANDLER
#define CMENUHANDLER
#include "Universe.hpp"
enum Coordinate {
	MODEL, WORLD, VIEW, LIGHT
};
enum Operation {
	ROTX = 1, ROTY = 2, ROTZ = 3, SCALE, TX, TY, TZ, CLIP_NEAR, CLIP_FAR, VIEW_ANGLE, ROTX_UP, ROTY_UP, ROTZ_UP
};
enum LightOperation {
	L_ROTX = 1, L_ROTY = 2, L_ROTZ = 3, L_TX, L_TY, L_TZ, L_POINT_INTENSITY, L_POINT_REFLECTION, L_AMBIENT_REFLECTION
};

GLint winWidth = 800, winHeight = 800;
GLint moving = 0, xBegin = 0;

Operation type = SCALE;
Coordinate coordinate = MODEL;
LightOperation lightOperation = L_POINT_INTENSITY;

//Declare a world containing all objects to draw.
Universe *myUniverse;

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		delete myUniverse;
		myUniverse = new Universe();
		type = SCALE;
		coordinate = MODEL;
		break;
	case 3:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void VCTransMenu(GLint transOption) {
	coordinate = VIEW;
	Operation a[] = { ROTX, ROTY, ROTZ, TX, TY, TZ, CLIP_NEAR, CLIP_FAR, VIEW_ANGLE, ROTX_UP, ROTY_UP, ROTZ_UP };
	type = a[transOption - 1];
	glutPostRedisplay();
}

void LightMenu(GLint option) {
	LightOperation a[] = { L_ROTX, L_ROTY, L_ROTZ, L_TX, L_TY, L_TZ, L_POINT_INTENSITY, L_POINT_REFLECTION,
			L_AMBIENT_REFLECTION };
	coordinate = LIGHT;
	lightOperation = a[option - 1];
	glutPostRedisplay();
}

void createMenu() {
	GLint VCTrans_Menu, Light_Menu;

	VCTrans_Menu = glutCreateMenu(VCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Clipping Near ", 7);
	glutAddMenuEntry(" Clipping Far ", 8);
	glutAddMenuEntry(" Angle ", 9);
	glutAddMenuEntry(" Rotate X Up", 10);
	glutAddMenuEntry(" Rotate Y Up", 11);
	glutAddMenuEntry(" Rotate Z Up", 12);

	Light_Menu = glutCreateMenu(LightMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Point Light Intensity I ", 7);
	glutAddMenuEntry(" Point Light Reflection Rd", 8);
	glutAddMenuEntry(" Ambient Reflection Ra", 9);

	glutAddMenuEntry(" Control Point Selection", 1);
	glutAddMenuEntry(" Bezier Curve Generation", 2);
	glutAddMenuEntry(" 3D Bezier Mesh", 3);
	glutAddMenuEntry(" Solid Mesh with OpenGL Shading", 4);
	glutAddMenuEntry(" Solid Mesh with GLSL Phong Shading", 5);
	glutAddMenuEntry(" Solar System Simulation", 6);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations", Light_Menu);
	glutAddMenuEntry(" Quit", 3);
}

#endif
