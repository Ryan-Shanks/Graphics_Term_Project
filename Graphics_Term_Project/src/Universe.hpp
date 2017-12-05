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
private:
	std::list<LightOrb*> orbs;
};

#endif
