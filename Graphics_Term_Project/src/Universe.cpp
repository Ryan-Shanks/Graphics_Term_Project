/**
 * File: World.hpp
 */

#include "Universe.hpp"

Universe::Universe() {
	myCamera = new Camera();
	orbsPassed = 0;
	/**
	 * opengl only supports 8 lights in the way we use them. Need to keep track of which are already taken so we dont take them again.
	 */
	for (int i = 0; i < 9; i++) {
		lightsAvailable.push_back(8 - i);
	}
	collision = false;
}

Universe::~Universe() {
	delete myCamera;
}

void Universe::draw_world() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//materials for the ship
	GLfloat matAmb[] = { 0.2, .2, .2, 1.0 }; //ambient
	GLfloat matDif[] = { 0.8, .8, 0.8, 1.0 }; //diffuse
	GLfloat matSpec[] = { 0.0, 0.0, 0.0, 1.0 }; //specular
	GLfloat matEm[] = { 0, 0, 0, 1 }; //emission, make the axis always bright
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 125);
	ship.draw();
	for (std::list<LightOrb*>::const_iterator iterator = orbs.begin(), end = orbs.end(); iterator != end; ++iterator) {
		(*iterator)->draw();
	}
	glFlush();
	glutSwapBuffers();
}

void Universe::normalizeAll() {
	ship.normalize();
}
void clockHelper(int pointerToWorld) {
	((Universe*) pointerToWorld)->clock();
}

void Universe::clock() {
	static DWORD start, end;
	start = GetTickCount();
	DWORD ticks = end - start;
	keys();
	if (orbs.size() < sqrt(orbsPassed) || orbs.size() == 0) {
		//create a new orb
		GLfloat startx = -5.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10.0f)));
		GLfloat starty = -5.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10.0f)));

		//choose a color
		int c = rand() % 5;
		GLfloat r, g, b;
		switch (c) {
		case 0:
			r = 1, g = 0, b = 0;
			break;
		case 1:
			r = 0, g = 1, b = 0;
			break;
		case 2:
			r = 0, g = 0, b = 1;
			break;
		case 3:
			r = 1, g = 1, b = 0;
			break;
		case 4:
			r = 0, g = 1, b = 1;
			break;
		case 5:
			r = 1, g = 0, b = 1;
		}
		float speedFactor = 1.0
				+ static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f + sqrt(orbsPassed))));
		orbs.push_back(new LightOrb(startx, starty, r, g, b, &lightsAvailable, speedFactor));
		cout << "new orb" << endl;
	}
	for (std::list<LightOrb*>::const_iterator iterator = orbs.begin(), end = orbs.end(); iterator != end; ++iterator) {
		(*iterator)->tick(ticks);
	}

	for (std::list<LightOrb*>::const_iterator iterator = orbs.begin(), end = orbs.end(); iterator != end; ++iterator) {
		(*iterator)->tick(ticks);
		if (checkCollision(*iterator)) {
			collision = true;
		}
		if ((*iterator)->getMC().mat[0][3] < 0) {
			//it has passed, delete
			delete *iterator;
			orbs.remove(*iterator);
			orbsPassed++;
		}
	}
	ship.tick(ticks);
	keys();
	if (!collision) {
		glutTimerFunc(10, clockHelper, (int) this);
	}
	end = GetTickCount();
	glutPostRedisplay();
}

bool Universe::checkCollision(LightOrb* o) {
	Vector ov = o->getMC().getPosVect();
	Vector sv = ship.getMC().getPosVect();
	float radius = 0.5;
	if (ov.x < 2 && ov.x > 0) { // if its too far or too close it could not have hit the ship
	//check the body first, it has a radius of 1 and the orbs have .5
		if (sqrt(pow(sv.y - ov.y, 2) + pow(sv.z - ov.z, 2) < 1 + radius)) {
			//hit the body
			return true;
		}
		Vector bodyToCircle = Vector(0, ov.y - sv.y, ov.z - sv.z); // vector from the body of the plane to the circle, 2d
		GLfloat angle = bodyToCircle.angleFromPosZinYZPlane();
		cout << angle << endl;
		float angleTolerance = 10;
		float tilt = 0;
		if (ship.vz > 0){
			tilt = 20;
		}else if (ship.vz < 0){
			tilt = -20;
		}
		if ((angle > 20 - angleTolerance+tilt && angle < 20 + angleTolerance+tilt)
				|| (angle > -20 - angleTolerance+tilt && angle < -20 + angleTolerance+tilt)) {
			//hit a wing, aproximately
			return true;
		}
	}
	return false;
}

void Universe::keys() {
	BYTE mask = 0b10000000;
	bool u, d, l, r;
	u = (GetAsyncKeyState('W') && mask) || (GetAsyncKeyState(VK_UP) && mask);
	d = (GetAsyncKeyState('S') && mask) || (GetAsyncKeyState(VK_DOWN) && mask);
	l = (GetAsyncKeyState('A') && mask) || (GetAsyncKeyState(VK_LEFT) && mask);
	r = (GetAsyncKeyState('D') && mask) || (GetAsyncKeyState(VK_RIGHT) && mask);

	if (u && !d) {
		ship.vert(1);
	} else if (d && !u) {
		ship.vert(-1);
	} else {
		ship.vert(0);
	}

	if (l && !r) {
		ship.horiz(1);
	} else if (r && !l) {
		ship.horiz(-1);
	} else {
		ship.horiz(0);
	}
}
