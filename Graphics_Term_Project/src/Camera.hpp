
#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Point.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

class Camera {
 public:
	Point eye; 			//camera position
	Point ref; 			//look at point
	Vector viewup; 		//view up vector
	GLfloat aspect, nearDist, farDist, viewAngle;

	//Point eye; 			//camera position
	//Vector u, v, n; 		//view

	Camera();
	void set(Point Eye, Point look, Vector up);
	void set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz);
	void printCamera(void);
	void setDefaultCamera();

	void rotate(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle);
	void rotateViewUp(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	void setViewVolume(float viewAngle, float aspect, float Near, float Far);
	void setAspect(float aspect);

	/* another set of transforms*/
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void slide(double du, double dv, double dn);

	/*  */
	void setProjectionMatrix();
	Vector getViewVector();
	void followShip(Matrix ship);
	void rotate_relative(double x0, double y0, double z0, double rx, double ry, double rz, double angle);
};
#endif


