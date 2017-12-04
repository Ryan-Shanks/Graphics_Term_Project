/*
 * Cylinder.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#include "Cylinder.hpp"

Cylinder::Cylinder() {
	quad = gluNewQuadric();
	//gluQuadricOrientation(quad, GLU_OUTSIDE);
	matNear.translate(0,0,1);
	matFar.rotate(1,0,0,180); // flip the back face so it is facing out
}

Cylinder::~Cylinder() {
}

void Cylinder::draw(){
	glPushMatrix();
	ctm_multiply();
	gluCylinder(quad, 0.5, 0.5, 1, 50, 50); // need to add a disk at each end now

	glPushMatrix();
	matNear.ctm_multiply();
	gluDisk(quad, 0, 0.5, 50, 50); // draw the close face at z = 1;
	glPopMatrix();

	glPushMatrix();
	matFar.ctm_multiply();
	gluDisk(quad, 0, 0.5, 50, 50);
	glPopMatrix();
	glPopMatrix();
}
