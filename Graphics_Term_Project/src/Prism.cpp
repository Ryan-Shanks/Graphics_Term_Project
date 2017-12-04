/*
 * Prism.cpp
 *
 * will take any convex shape defined by 2d vertex points and draw a prism for the given height.
 * Intended to be used for wings and such. Points given should be in the xz plane
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#include "Prism.hpp"

Prism::Prism(std::vector<Point> points, GLfloat height) {
	this->points = points;
	for (unsigned i = 0; i < points.size(); i++) {
		points[i].y = 0;
		Vector n = Vector();
		n.setAs2DNormal(points[i],points[wrapPoints(i+1)]);
		normalsOnSideFaces.push_back(n);
	}
	this->height = height;
}

Prism::~Prism() {
	points.clear();
}

void Prism::draw() {
	glPushMatrix();
	ctm_multiply();

	glNormal3f(0,1,0); //top face, will be rotated according to the MC matrix
	glBegin(GL_POLYGON);
	//draw the top face;
	for (unsigned i =0; i < points.size(); i++){
		glVertex3f(points[i].x, height /2, points[i].z);
	}
	glEnd();
	glNormal3f(0,-1,0);
	glBegin(GL_POLYGON);
	//i cannot be less than 0 since its unsigned, it would just go back around
	for(unsigned i = points.size()-1; i < points.size(); i--){
		glVertex3f(points[i].x, -height /2, points[i].z);
	}
	glEnd();
	//now connect the 2 planes with a quad strip
	glBegin(GL_QUAD_STRIP);
	for (unsigned i =0; i <= points.size(); i++){
		GLfloat n[4];
		normalsOnSideFaces[wrapPoints(i)].build4tuple(n);
		glNormal3fv(n);
		glVertex3f(points[wrapPoints(i)].x, height/2, points[wrapPoints(i)].z);
		glVertex3f(points[wrapPoints(i)].x, -height/2, points[wrapPoints(i)].z);
	}
	glEnd();
	glPopMatrix();
}

int Prism::wrapPoints(int i){
	return i % points.size();
}
