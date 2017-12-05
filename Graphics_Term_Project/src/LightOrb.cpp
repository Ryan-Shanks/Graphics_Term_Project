/*
 * PointLightSource.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: ryanw
 */

#include "LightOrb.hpp"

LightOrb::LightOrb(GLfloat starty, GLfloat startz, GLfloat r, GLfloat g, GLfloat b, vector<int> *lightsAvail, float speedFactor) {
	speed = -.000000000025*speedFactor;
	lightNo = -1;
	translate(100, starty, startz);
	this->r = r;
	this->g = g;
	this->b = b;
	this->lightsAvail = lightsAvail;
}

LightOrb::~LightOrb() {
	// TODO Auto-generated destructor stub
	if (lightNo != -1) { // if this is currently occupying one of the opengl lights, put back
		lightsAvail->push_back(lightNo);
		glDisable(GL_LIGHT0 + lightNo);
	}
}

void LightOrb::draw() {
	GLfloat p[] = { 1, 1, 1, 1 };
	GLfloat a[] = { r * 0.2, g * 0.2, b * 0.2, 1 };
	GLfloat d[] = { r * 1, g * 1, b * 1, 1 };
	GLfloat e[] = { r * 1, g * 1, b * 1, 1 };
	glMaterialfv(GL_FRONT, GL_POSITION, p);
	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT, GL_EMISSION, e);

	glPushMatrix();
	ctm_multiply();
	glutSolidSphere(.5, 20, 20);
	glPopMatrix();
	//go back to the default material, ie dont emit
	GLfloat matEm[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
	setGLLighting();

}

void LightOrb::setGLLighting() {
	if (lightNo != -1) {
		if (mc.mat[0][3] > 0) {
			glEnable(GL_LIGHT0 + lightNo);
			glPushMatrix();
			ctm_multiply();
			GLfloat p[] = {-1, 0, 0, 1 };
			GLfloat a[] = { r * 0.2, g * 0.2, b * 0.2, 1 };
			GLfloat d[] = { r * 1, g * 1, b * 1, 1 };
			GLfloat s[] = { r * 1, g * 1, b * 1, 1 };
			glLightfv(GL_LIGHT0 + lightNo, GL_POSITION, p);
			glLightfv(GL_LIGHT0 + lightNo, GL_AMBIENT, a);
			glLightfv(GL_LIGHT0 + lightNo, GL_DIFFUSE, d);
			glLightfv(GL_LIGHT0 + lightNo, GL_SPECULAR, s);
			glPopMatrix();
		} else {
			glDisable(GL_LIGHT0 + lightNo);
		}
	}
}

void LightOrb::tick(DWORD ticks) {
	translate(speed * ticks, 0, 0);
	// try and get a light from the vector
	if (lightNo == -1 && lightsAvail->size() > 0) {
		lightNo = (*lightsAvail)[lightsAvail->size() - 1];
		lightsAvail->pop_back();
	}
	if (mc.mat[0][3] < 3) {
		//TODO check for collision
	}
}
