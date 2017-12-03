#include "Shape.hpp"

Shape::Shape() {
	MC.mat[0][0] = 1.0;
	MC.mat[0][1] = 0.0;
	MC.mat[0][2] = 0.0;
	MC.mat[0][3] = 0.0;
	MC.mat[1][0] = 0.0;
	MC.mat[1][1] = 1.0;
	MC.mat[1][2] = 0.0;
	MC.mat[1][3] = 0.0;
	MC.mat[2][0] = 0.0;
	MC.mat[2][1] = 0.0;
	MC.mat[2][2] = 1.0;
	MC.mat[2][3] = 0.0;
	MC.mat[3][0] = 0.0;
	MC.mat[3][1] = 0.0;
	MC.mat[3][2] = 0.0;
	MC.mat[3][3] = 1.0;
	s = 1;
}

Shape::~Shape() {
}


Matrix Shape::getMC() {
	return MC;
}


void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	MC.translate(tx, ty, tz);
}

void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	MC.rotate(rx, ry, rz, angle);
}

void Shape::rotate_mc(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	GLfloat x0, y0, z0;
	x0 = MC.mat[0][3];
	y0 = MC.mat[1][3];
	z0 = MC.mat[2][3];
	MC.rotate(rx, ry, rz, angle);
	MC.mat[0][3] = x0;
	MC.mat[1][3] = y0;
	MC.mat[2][3] = z0;
}

void Shape::rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix* m = new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = MC.mat[0][3];
	v[1] = MC.mat[1][3];
	v[2] = MC.mat[2][3];
	v[3] = MC.mat[3][3];
	m->multiply_vector(v);
	MC.mat[0][3] = v[0];
	MC.mat[1][3] = v[1];
	MC.mat[2][3] = v[2];
	MC.mat[3][3] = v[3];
	delete m;
}

void Shape::scale_change(GLfloat x) {
	s += x;
}

/**
 * Shape::ctm_multiply() multiply this matrix to openGL current matrix
 */
void Shape::ctm_multiply() {
	MC.ctm_multiply();
}
void Shape::drawAxis(){
	glColor3f(1,0,0);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);
	glEnd();
}
void Shape::normalize(){
	MC.normalize();
}

void Shape::rotate_relative(double x0, double y0, double z0, double rx, double ry, double rz, double angle) {
    Matrix* m = new Matrix();
    m->rotate(rx, ry, rz, angle * 1);
    GLfloat v[4];
    v[0] = MC.mat[0][3]-x0;
    v[1] = MC.mat[1][3]-y0;
    v[2] = MC.mat[2][3]-z0;
    v[3] = 1;
    m->multiply_vector(v);
    MC.mat[0][3] = v[0]+x0;
    MC.mat[1][3] = v[1]+y0;
    MC.mat[2][3] = v[2]+z0;
    MC.mat[3][3] = 1;
    delete m;
}

void Shape::scale(GLfloat sx, GLfloat sy, GLfloat sz) {
	MC.mat[0][0] *= sx;
	MC.mat[1][1] *= sy;
	MC.mat[2][2] *= sz;
}

