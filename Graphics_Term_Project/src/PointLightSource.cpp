/*
 * PointLightSource.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: ryanw
 */

#include "PointLightSource.hpp"

PointLightSource::PointLightSource() {
	translate(2, 2, 2);
	i = 1;
	rd = 1;
	ra = 1;
	on = true;
	size = 1;
	ia = 1;
	s = 0; // not used for point light source anyway
}

PointLightSource::~PointLightSource() {
	// TODO Auto-generated destructor stub
}

/**
 * increment or decrement but ensure they stay between 0 and 1
 */
void PointLightSource::increment(GLfloat di, GLfloat drd, GLfloat dra) {
	i += di;
	rd += drd;
	ra += dra;

	if (i < 0) {
		i = 0;
	} else if (i > 1) {
		i = 1;
	}

	if (rd < 0) {
		rd = 0;
	} else if (rd > 1) {
		rd = 1;
	}

	if (ra < 0) {
		ra = 0;
	} else if (ra > 1) {
		ra = 1;
	}
}

void PointLightSource::draw() {
	GLfloat matAmb1[] = { 0.2, 0.2, 0.2, 1.0 }; //ambient
	GLfloat matDif1[] = { 0.8, .8, 0.8, 1.0 }; //diffuse
	GLfloat matSpec1[] = { 0.0, 0.0, 0.0, 1.0 }; //specular
	GLfloat matEm1[] = { 1.0, 1.0, 1.0, 1.0 }; //emission
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec1);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm1);

	glPushMatrix();
	this->ctm_multiply();
	glColor3f(1, 1, 1);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	//go back to the default material, ie dont emit
	GLfloat matEm[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
}

void PointLightSource::setGLLighting(){
	if (on){
		glPushMatrix();
		ctm_multiply();
		GLfloat p[] = {1,1,1,1};
		GLfloat a[]= {0.2,0.2,0.2,1};
		GLfloat d[]= {1,1,1,1};
		glLightfv(GL_LIGHT0, GL_POSITION, p);
		glLightfv(GL_LIGHT0, GL_AMBIENT, a);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
		glPopMatrix();
	}
}
