/*
 * Cone.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#include "Cone.hpp"

Cone::Cone() {
	quad = gluNewQuadric();
	//gluQuadricOrientation(quad, GLU_OUTSIDE);
	matFar.rotate(1,0,0,180); // flip the back face so it is facing out
}

Cone::~Cone() {
}

void Cone::draw(){
	glPushMatrix();
	ctm_multiply();
	gluCylinder(quad, 0.5, 0, 1, 50, 50); // need to add a disk at each end now

	glPushMatrix();
	matFar.ctm_multiply();
	gluDisk(quad, 0, 0.5, 50, 50);
	glPopMatrix();
}
