/*
 * SpaceShip.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#include "Spaceship.hpp"

Spaceship::Spaceship() {
	vector<Point*> cp;
	cp.push_back(new Point(3,0,0));
	cp.push_back(new Point(1.5,1,0));
	cp.push_back(new Point(0,0,0));
	body = new BezierCurve(cp, 50,370,2);
	body->setDrawingMode(GLSL_SHADE);
	//body->rotate_mc(0, 1, 0, 90);
	vector<Point> wingPoints;
	wingPoints.push_back(Point(0.5, 0, 1.5));
	wingPoints.push_back(Point(1, 0, 2));
	wingPoints.push_back(Point(1.5, 0, 2));
	wingPoints.push_back(Point(2, 0, 1.5));
	wingPoints.push_back(Point(1.5, 0, 0));
	//wingPoints.push_back(Point(2, 0, 0));
	wingPoints.push_back(Point(0.5, 0, 0));

	// add the wings
	rightUpperWing = new Prism(wingPoints, 0.02);
	leftUpperWing = new Prism(wingPoints, 0.02);
	leftLowerWing = new Prism(wingPoints, 0.02);
	rightLowerWing = new Prism(wingPoints, 0.02);

	rightLowerWing->rotate(1, 0, 0, 20);
	leftLowerWing->rotate(1, 0, 0, 160);
	leftUpperWing->rotate(1, 0, 0, 200);
	rightUpperWing->rotate(1, 0, 0, -20);
	vy = 0;
	vz = 0;
}

Spaceship::~Spaceship() {
	delete rightUpperWing;
	delete leftUpperWing;
	delete body;
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
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	glPushMatrix();
	ctm_multiply();
	tilt.ctm_multiply();
	body->draw();
	leftUpperWing->draw();
	rightUpperWing->draw();
	leftLowerWing->draw();
	rightLowerWing->draw();
	glPopMatrix();
}

void Spaceship::vert(char d) {
	vy= d*0.00000000003;
}

void Spaceship::horiz(char d) {
	vz = d*-0.00000000003;
}

void Spaceship::tick(DWORD ticks){
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
	translate(0, vy * ticks, vz * ticks);
}
