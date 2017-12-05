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
	for (int i =0; i < 9; i++){
		lightsAvailable.push_back(8-i);
	}
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
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
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
	if (orbs.size() < sqrt(orbsPassed) || orbs.size() == 0) {
		//create a new orb
		GLfloat startx = -3.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
		GLfloat starty = -3.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.0f)));

		//choose a color
		int c = rand() % 5;
		GLfloat r,g,b;
		switch (c){
			case 0:
				r = 1,g=0,b=0;
				break;
			case 1:
				r=0, g=1, b=0;
				break;
			case 2:
				r = 0,g=0,b=1;
				break;
			case 3:
				r=1,g=1,b=0;
				break;
			case 4:
				r=0,g=1,b=1;
				break;
			case 5:
				r=1,g=0,b=1;
		}
		orbs.push_back(new LightOrb(startx, starty, r, g, b, &lightsAvailable));
		cout << "new orb" << endl;
	}
	for (std::list<LightOrb*>::const_iterator iterator = orbs.begin(), end = orbs.end(); iterator != end; ++iterator) {
		(*iterator)->tick(ticks);
	}

	for (std::list<LightOrb*>::const_iterator iterator = orbs.begin(), end = orbs.end(); iterator != end; ++iterator) {
		(*iterator)->tick(ticks);
		if ((*iterator)->getMC().mat[0][3] < 0){
			//it has passed, delete
			delete *iterator;
			orbs.remove(*iterator);
			orbsPassed++;
		}
	}
	ship.tick(ticks);

	glutTimerFunc(10, clockHelper, (int) this);
	end = GetTickCount();
	glutPostRedisplay();
}
