#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <GL/glew.h>
#include "Sphere.hpp"
#include "Cube.hpp"
#include "PointLightSource.hpp"
#include "Camera.hpp"
#include <iostream>
#include <list>
#include <vector>
#include "BezierCurve.hpp"

enum WorldState {
	CP_SELECT, BEZIER_CURVE_GEN, ROT_SURFACE_GEN, TEXTURED_CUBE, SOLAR_SYSTEM, GL_SHADING, GLSL_SHADING
};
class World {
public:
	Camera *myCamera;
	Shape *cube; // cube to show texture mapping
	World();
	~World();
	void draw_world(); // draw all objects in the world
	void normalizeAll();
	PointLightSource *lightSource;
	void setWorldState(WorldState newState);
	WorldState getWorldState();
	void addControlPoint(GLfloat mouseX, GLfloat mouseY);
	void setGLSLProgram(GLuint);
	void animateSolar();
	GLint stepRotation, totalRotation, bezCurveRes; // Parameters to control the rotation and smoothness of the curve
	void clearCP();
	void remakeCurve();
private:
	std::vector<Point*> controlPoints; // cp to generate the bezier curve
	Sphere *sun, *moon, *earth; // shapes for the solar system
	WorldState ws;
	BezierCurve* curve;
	PointLightSource *sunLight;

	void initRenderingMode(int); // 2 to switch to 2d or 3 to switch to 3d
	GLuint program;
};

#endif
