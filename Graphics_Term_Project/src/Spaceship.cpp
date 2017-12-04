/*
 * SpaceShip.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#include "Spaceship.hpp"

Spaceship::Spaceship() {
	body = new Cylinder();
	body->scale(1, 1, 3);
	body->rotate_mc(0, 1, 0, 90);
	vector<Point> wingPoints;
	wingPoints.push_back(Point(0.5, 0, 2));
	wingPoints.push_back(Point(2, 0, 2));
	wingPoints.push_back(Point(2, 0, 0.5));
	wingPoints.push_back(Point(0.5, 0, 0.5));

	// add the wings
	rightWing = new Prism(wingPoints, 0.02);
	leftWing = new Prism(wingPoints, 0.02);
	leftWing->rotate(1, 0, 0, 180);

	nose = new Cone();
	nose->translate(0,0,3);
	nose->rotate(0,1,0,90);
}

Spaceship::~Spaceship() {
	delete rightWing;
	delete leftWing;
	delete body;
	delete nose;
}

void Spaceship::draw() {
	glPushMatrix();
	ctm_multiply();
	body->draw();
	leftWing->draw();
	rightWing->draw();
	nose->draw();
	glPopMatrix();
}
