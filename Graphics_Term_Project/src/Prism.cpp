/*
 * Prism.cpp
 *
 * will take any convex shape defined by 2d vertex points and draw a prism for the given height.
 * Intended to be used for wings and such
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#include "Prism.hpp"

Prism::Prism(std::vector<Point> points, GLfloat height) {
	this->points = points;
	for (int i = 0; i < points.size(); i++) {
		points[i].z = 0;
	}
	this->height = height;
}

Prism::~Prism() {
	points.clear();
}

void Prism::draw() {
	glPushMatrix();
	ctm_multiply();

	glNormal3f(1,0,0); //top face, will be rotated according to the MC matrix
	glBegin(GL_POLYGON);
	//draw the top face;
	for (int i =0; i < points.size(); i++){
		glVertex3f(points[i].x, points[i].y, height);
	}
	glEnd();
	glNormal3f(-1,0,0);
	glBegin(GL_POLYGON);
	for(int i = 0; i < points.size(); i++){
		glVertex2f(points[i].x,points[i].y);
	}
	glEnd();
	//now connect the 2 planes with a quad strip
	glBegin(GL_QUAD_STRIP);
	for (int i =0; i < points.size(); i++){
		glVertex3f(points[i].x, points[i].y, height);
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
	glPopMatrix();
}
