#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <GL/glew.h>
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Camera.hpp"
#include <iostream>
#include <list>
#include <vector>
#include "BezierCurve.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "LightOrb.hpp"
#include "Spaceship.hpp"
#include <mmsystem.h>

class Universe {
public:
	Camera *myCamera;
	Universe();
	~Universe();
	void draw_world(); // draw all objects in the world
	void normalizeAll();
	void clock();
	Spaceship ship;
	int orbsPassed;
	vector<int> lightsAvailable;
	bool collision;
	void keys();
private:
	std::list<LightOrb*> orbs;
	bool checkCollision(LightOrb *o);
};

#endif
