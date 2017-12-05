/**
 * File: World.hpp
 */

#include "Universe.hpp"

Universe::Universe() {
	earth = new Sphere("earth.bmp", 201);
	earth->translate(2, 0, 0);
	earth->scale_change(-0.85);
	earth->rotate_mc(-1, 0, 0, 101.5); // make earth right side up
	moon = new Sphere("moon.bmp", 202);
	moon->scale_change(-0.95);
	moon->translate(2.5, 0, 0);
	sun = new Sphere("sun.bmp", 203);
	sun->scale_change(-0.5);
	sunLight = new PointLightSource();
	sunLight->translate(-2, -2, -2); //light sources start out at 2,2,2 by default, put it back at the origin
	myCamera = new Camera();
	lightSource = new PointLightSource();
	curve = NULL;
	totalRotation = 90;
	stepRotation = 1;
	bezCurveRes = 200;
}

Universe::~Universe() {
	delete sun;
	delete earth;
	delete moon;
	delete myCamera;
	delete lightSource;
	delete sunLight;
}

void Universe::draw_world() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat matAmb[] = { 0.2, .2, .2, 1.0 }; //ambient
	GLfloat matDif[] = { 0.8, .8, 0.8, 1.0 }; //diffuse
	GLfloat matSpec[] = { 0.0, 0.0, 0.0, 1.0 }; //specular
	GLfloat matEm[] = { 0, 0, 0, 1 }; //emission, make the axis always bright
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
	//myCamera->followShip(ship.getMC());
	ship.draw();
	lightSource->draw();
	glFlush();
	glutSwapBuffers();
}

void Universe::normalizeAll() {
	sun->normalize();
	moon->normalize();
	earth->normalize();
	if (curve != NULL) {
		curve->normalize();
	}
	ship.normalize();
}
void clockHelper(int pointerToWorld) {
	((Universe*) pointerToWorld)->clock();
}
void Universe::clock() {
	static DWORD start, end;
	start = GetTickCount();

	ship.tick();

	glutPostRedisplay();
	glutTimerFunc(10, clockHelper, (int) this);
	end = GetTickCount();
	glutPostRedisplay();
}

