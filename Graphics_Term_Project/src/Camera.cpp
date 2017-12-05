#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"

bool DEBUG = false;

Camera::Camera() {
	setDefaultCamera();
}

void Camera::setDefaultCamera(void) { // make default camera
	eye.x = -10, eye.y = 0, eye.z = 0.0;
	ref.x = 10, ref.y = 0, ref.z = 0.0;
	viewup.x = 0.0, viewup.y = 1.0, viewup.z = 0.0;
	aspect = 1.0, viewAngle = 40.0, nearDist = 0.1, farDist = 10000.0;
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = 1.0, viewAngle = 40.0, nearDist = 0.1, farDist = 10000.0;
	//setModelViewMatrix();
}

void Camera::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) { //w.r.p.t WC
	Matrix m;
	m.rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = eye.x;
	v[1] = eye.y;
	v[2] = eye.z;
	v[3] = 1;
	m.multiply_vector(v);
	eye.x = v[0];
	eye.y = v[1];
	eye.z = v[2];
	//std::cout << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
}

void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz) { //w.r.p.t WC
	eye.x += tx;
	eye.y += ty;
	eye.z += tz;
}

void Camera::setProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x, viewup.y, viewup.z);

}

void Camera::setViewVolume(float viewAngle, float aspect, float Near, float Far) {
	this->viewAngle = viewAngle;
	this->aspect = aspect;
	nearDist = Near > 0 ? Near : 0.01; // should never be set to 0 according to documentation
	farDist = Far > 0 ? Far : 0;
}

void Camera::rotateViewUp(GLfloat rx, GLfloat rz, GLfloat ry, GLfloat angle) {
	Matrix m;
	m.rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = viewup.x;
	v[1] = viewup.y;
	v[2] = viewup.z;
	v[3] = 1;
	m.multiply_vector(v);
	viewup.x = v[0];
	viewup.y = v[1];
	viewup.z = v[2];
}
Vector Camera::getViewVector() {
	Vector v;
	v.set(ref.x - eye.x, ref.y - eye.y, ref.z - eye.z);
	return v;
}
