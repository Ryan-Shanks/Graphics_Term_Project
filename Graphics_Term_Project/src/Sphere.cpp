/*
 * Sphere.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: ryanw
 */

#include "Sphere.hpp"

Sphere::Sphere(bool solid, GLfloat r, GLfloat g, GLfloat b) {
	this->solid = solid;
	this->r = r;
	this->g = g;
	this->b = b;
	useTexture = false;
	texName = 0;
}
Sphere::Sphere(std::string texture, int uniqueTexName) {
	r = 0, g = 0, b = 0, solid = true;
	tex.readBMPFile(texture);
	tex.setTexture(uniqueTexName);
	useTexture = true;
	texName = uniqueTexName;

	quad = gluNewQuadric();

	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluQuadricNormals(quad, GLU_SMOOTH);
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

void Sphere::draw() {
	glPushMatrix();
	this->ctm_multiply();
	if (useTexture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName);
		gluSphere(quad, s, 50, 50);
		glDisable(GL_TEXTURE_2D);
	} else {
		glColor3f(r, g, b);
		if (solid) {
			glutSolidSphere(s, 50, 50);
		} else {
			glutWireSphere(s, 50, 50);
		}
	}
	glPopMatrix();
}
