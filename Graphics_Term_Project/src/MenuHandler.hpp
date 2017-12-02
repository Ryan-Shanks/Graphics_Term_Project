/*
 * MenuHanlder.cpp
 * Goal is to separate the menu functions and global variables from the rest of the main functions
 *  Created on: Nov 9, 2017
 *      Author: ryanw
 */
#ifndef CMENUHANDLER
#define CMENUHANDLER
#include "World.hpp"
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
World *myWorld;

void MCTransMenu(GLint transOption) {
	myWorld->setWorldState(TEXTURED_CUBE);
	Operation a[] = { ROTX, ROTY, ROTZ, SCALE };
	type = a[transOption - 1];
	coordinate = MODEL;
	glutPostRedisplay();
}

void WCTransMenu(GLint transOption) {
	myWorld->setWorldState(TEXTURED_CUBE);
	coordinate = WORLD;
	Operation a[] = { ROTX, ROTY, ROTZ, TX, TY, TZ };
	type = a[transOption - 1];
	glutPostRedisplay();
}

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		delete myWorld;
		myWorld = new World();
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

void A4Menu(GLint opt) {
	WorldState a[] = { CP_SELECT, BEZIER_CURVE_GEN, ROT_SURFACE_GEN, GL_SHADING, GLSL_SHADING, SOLAR_SYSTEM };
	if (opt == 1){
		myWorld->clearCP();
	}
	myWorld->setWorldState(a[opt - 1]);
	glutPostRedisplay();
}
void SMenu(int o){
	myWorld->stepRotation = o;
	myWorld->remakeCurve();
}
void RMenu(int o){
	myWorld->totalRotation = o;
	myWorld->remakeCurve();
}
void TMenu(int o){
	myWorld->bezCurveRes = o;
	myWorld->remakeCurve();
}
void createMenu() {
	GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, Light_Menu, A4_Menu, R_Menu, T_Menu, S_Menu;
	MCTrans_Menu = glutCreateMenu(MCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Scale", 4);

	WCTrans_Menu = glutCreateMenu(WCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);

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

	//curve configurations
	R_Menu = glutCreateMenu(RMenu);
	glutAddMenuEntry(" 45", 45);
	glutAddMenuEntry(" 90", 90);
	glutAddMenuEntry(" 135", 135);
	glutAddMenuEntry(" 180", 180);
	glutAddMenuEntry(" 225", 225);
	glutAddMenuEntry(" 270", 270);
	glutAddMenuEntry(" 315", 315);
	glutAddMenuEntry(" 360", 360);

	S_Menu = glutCreateMenu(SMenu);
	glutAddMenuEntry(" 1", 1);
	glutAddMenuEntry(" 5", 5);
	glutAddMenuEntry(" 10", 10);
	glutAddMenuEntry(" 15", 15);

	T_Menu = glutCreateMenu(TMenu);
	glutAddMenuEntry(" 10", 10);
	glutAddMenuEntry(" 15", 15);
	glutAddMenuEntry(" 20", 20);
	glutAddMenuEntry(" 25", 25);
	glutAddMenuEntry(" 200", 200);

	A4_Menu = glutCreateMenu(A4Menu);
	glutAddSubMenu(" R", R_Menu);
	glutAddSubMenu(" S", S_Menu);
	glutAddSubMenu(" T", T_Menu);
	glutAddMenuEntry(" Control Point Selection", 1);
	glutAddMenuEntry(" Bezier Curve Generation", 2);
	glutAddMenuEntry(" 3D Bezier Mesh", 3);
	glutAddMenuEntry(" Solid Mesh with OpenGL Shading", 4);
	glutAddMenuEntry(" Solid Mesh with GLSL Phong Shading", 5);
	glutAddMenuEntry(" Solar System Simulation", 6);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations", Light_Menu);
	glutAddSubMenu(" A4 Menu", A4_Menu);
	glutAddMenuEntry(" Quit", 3);
}

#endif
