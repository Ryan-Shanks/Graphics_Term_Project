#include "Shape.hpp"

Shape::Shape() {
	mc.mat[0][0] = 1.0;
	mc.mat[0][1] = 0.0;
	mc.mat[0][2] = 0.0;
	mc.mat[0][3] = 0.0;
	mc.mat[1][0] = 0.0;
	mc.mat[1][1] = 1.0;
	mc.mat[1][2] = 0.0;
	mc.mat[1][3] = 0.0;
	mc.mat[2][0] = 0.0;
	mc.mat[2][1] = 0.0;
	mc.mat[2][2] = 1.0;
	mc.mat[2][3] = 0.0;
	mc.mat[3][0] = 0.0;
	mc.mat[3][1] = 0.0;
	mc.mat[3][2] = 0.0;
	mc.mat[3][3] = 1.0;
	s = 1;
}

Shape::~Shape() {
}


Matrix Shape::getMC() {
	return mc;
}


void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	mc.translate(tx, ty, tz);
}

void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	mc.rotate(rx, ry, rz, angle);
}

void Shape::rotate_mc(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	GLfloat x0, y0, z0;
	x0 = mc.mat[0][3];
	y0 = mc.mat[1][3];
	z0 = mc.mat[2][3];
	mc.rotate(rx, ry, rz, angle);
	mc.mat[0][3] = x0;
	mc.mat[1][3] = y0;
	mc.mat[2][3] = z0;
}

void Shape::rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix* m = new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = mc.mat[0][3];
	v[1] = mc.mat[1][3];
	v[2] = mc.mat[2][3];
	v[3] = mc.mat[3][3];
	m->multiply_vector(v);
	mc.mat[0][3] = v[0];
	mc.mat[1][3] = v[1];
	mc.mat[2][3] = v[2];
	mc.mat[3][3] = v[3];
	delete m;
}

void Shape::scale_change(GLfloat x) {
	s += x;
}

/**
 * Shape::ctm_multiply() multiply this matrix to openGL current matrix
 */
void Shape::ctm_multiply() {
	mc.ctm_multiply();
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
	mc.normalize();
}

void Shape::rotate_relative(double x0, double y0, double z0, double rx, double ry, double rz, double angle) {
    Matrix* m = new Matrix();
    m->rotate(rx, ry, rz, angle * 1);
    GLfloat v[4];
    v[0] = mc.mat[0][3]-x0;
    v[1] = mc.mat[1][3]-y0;
    v[2] = mc.mat[2][3]-z0;
    v[3] = 1;
    m->multiply_vector(v);
    mc.mat[0][3] = v[0]+x0;
    mc.mat[1][3] = v[1]+y0;
    mc.mat[2][3] = v[2]+z0;
    mc.mat[3][3] = 1;
    delete m;
}

void Shape::scale(GLfloat sx, GLfloat sy, GLfloat sz) {
	mc.mat[0][0] *= sx;
	mc.mat[1][1] *= sy;
	mc.mat[2][2] *= sz;
}

