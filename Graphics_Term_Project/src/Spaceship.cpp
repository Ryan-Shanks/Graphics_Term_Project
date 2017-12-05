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
	nose->translate(0, 0, 3);
	nose->rotate(0, 1, 0, 90);
	vy = 0;
	vz = 0;
}

Spaceship::~Spaceship() {
	delete rightWing;
	delete leftWing;
	delete body;
	delete nose;
}

void Spaceship::draw() {
	Matrix tilt;
	if (vy > 0){
		tilt.rotate(0,0,1,20);
	}else if (vy < 0){
		tilt.rotate(0,0,1,-20);
	}

	if (vz > 0){
		tilt.rotate(1,0,0,20);
	}else if (vz < 0){
		tilt.rotate(1,0,0,-20);
	}

	glPushMatrix();
	ctm_multiply();
	tilt.ctm_multiply();
	body->draw();
	leftWing->draw();
	rightWing->draw();
	nose->draw();
	glPopMatrix();
}

void Spaceship::up() {
	vy= 0.25;
}
void Spaceship::down() {
	vy = -0.25;
}
void Spaceship::left() {
	vz = -0.25;
}
void Spaceship::right() {
	vz = 0.25;
}
void Spaceship::tick(){
	if(mc.mat[1][3] > 3){
		vy = 0;
		mc.mat[1][3] = 3;
	}else if(mc.mat[1][3] < -3){
		vy = 0;
		mc.mat[1][3] = -3;
	}

	if (mc.mat[2][3] > 3){
		vz = 0;
		mc.mat[2][3] = 3;
	}else if (mc.mat[2][3] < -3){
		vz = 0;
		mc.mat[2][3] = -3;
	}
	translate(0, vy, vz);
	mc.printMatrix();
}
