/*
 * BezierCurve.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: ryanw
 */

#include "BezierCurve.hpp"
BezierCurve::BezierCurve() {
	// default constructor because it complains otherwise. just make a straight line if this gets called.
	controlPoints.push_back(new Point(0, 0, 0));
	controlPoints.push_back(new Point(1, 1, 0));
	pointsOnCurve.resize(2, Point(0, 0, 0));
	computePointsOnCurve();
	angleOfRotation = 90;
	stepRotation = 5;
	fillInVerticesAndNormalsToDraw();
}
BezierCurve::BezierCurve(std::vector<Point*> controlPoints, int numCurvePoints, int angleOfRotation, int stepRotation) {
	this->controlPoints = controlPoints;
	pointsOnCurve.resize(numCurvePoints, Point(0, 0, 0));
	computePointsOnCurve();
	this->angleOfRotation = angleOfRotation;
	this->stepRotation = stepRotation;
	fillInVerticesAndNormalsToDraw();
}

BezierCurve::~BezierCurve() {
	// TODO Auto-generated destructor stub
}

void BezierCurve::computePointsOnCurve() {
	for (unsigned i = 0; i < pointsOnCurve.size(); i++) {
		computeBezierPoint(i);
	}
	computeBezierNorms();
}

void BezierCurve::setDrawingMode(DrawingMode d) {
	mode = d;
}

//compute the nth point on the bezier curve
void BezierCurve::computeBezierPoint(int n) {
	int ncp = controlPoints.size();
	GLfloat u = ((GLfloat) n) / (pointsOnCurve.size() - 1);
	if (u < 0.9999) {
		GLfloat b[ncp];

		b[0] = pow(1 - u, ncp - 1);
		GLfloat x = b[0] * controlPoints[0]->x, y = b[0] * controlPoints[0]->y;
		for (int i = 1; i < ncp; i++) {
			b[i] = b[i - 1] * (ncp - i) / i * u / (1 - u);

			x += b[i] * controlPoints[i]->x;
			y += b[i] * controlPoints[i]->y;
		}

		pointsOnCurve[n].x = x;
		pointsOnCurve[n].y = y;
	} else { // last point on the curve should be the last control point
		pointsOnCurve[n].x = controlPoints[controlPoints.size() - 1]->x;
		pointsOnCurve[n].y = controlPoints[controlPoints.size() - 1]->y;
	}
}

void BezierCurve::computeBezierNorms() {
	std::vector<Vector> tangents;
	for (unsigned i = 0; i < pointsOnCurve.size() - 1; i++) {
		tangents.push_back(
				Vector(pointsOnCurve[i + 1].y - pointsOnCurve[i].y, -(pointsOnCurve[i + 1].x - pointsOnCurve[i].x),
						pointsOnCurve[i + 1].z - pointsOnCurve[i].z));
	}
	// last one same as second last one, wont be used anyway but it will make some other code easier
	tangents.push_back(tangents[normOnCurve.size() - 1]);

	// create 2 normals for each face so we can do smooth lighting
	normOnCurve.push_back(tangents[0]); // the first one will not be averaged with anything
	for (unsigned i = 0; i < tangents.size() - 2; i++) {
		// for each vector normal that has a line on both sides of it
		Vector n = tangents[i].averageVect(tangents[i + 1]); //compute the average of the 2 normals
		normOnCurve.push_back(n);
	}
	tangents[tangents.size()].normalize();
	normOnCurve.push_back(tangents[tangents.size()]);
}

void BezierCurve::fillInVerticesAndNormalsToDraw() {
	Matrix rot;
	rot.rotate(1, 0, 0, 180); // it starts upside down otherwise, for some reason

	Matrix rotHalfAngle;
	rotHalfAngle.rotate(1,0,0,stepRotation/2);

	pointsOnSurface.resize(angleOfRotation / stepRotation);
	normalsOnSurface.resize(angleOfRotation / stepRotation);
	for (unsigned i = 0; i < angleOfRotation / stepRotation; i++) {
		for (unsigned j = 0; j < pointsOnCurve.size(); j++) {
			GLfloat v[4];
			pointsOnCurve[j].build4tuple(v);
			rot.multiply_vector(v);
			pointsOnSurface[i].push_back(Point(v[0], v[1], v[2]));

			// now the normals are averaged along the curve, need to average them along the rotation as well
			normOnCurve[j].build4tuple(v);
			rot.multiply_vector(v);
			if (1 < i && i < angleOfRotation / stepRotation){
				rotHalfAngle.multiply_vector(v); // rotate v a little further so it will be between the 2
			}
			normalsOnSurface[i].push_back(Vector(v[0], v[1], v[2]));
		}
		rot.rotate(1, 0, 0, stepRotation);
	}
}
void BezierCurve::draw() {
	if (mode == TWO_D) {
		glBegin(GL_LINE_STRIP);
		glColor3f(0, 0, 1);
		glLineWidth(3);
		for (unsigned i = 0; i < pointsOnCurve.size(); i++) {
			glVertex2f(pointsOnCurve[i].x, pointsOnCurve[i].y);
		}
		glLineWidth(1);
		glEnd();
		glBegin(GL_LINES);
//		for (unsigned i = 0; i < normOnCurve.size(); i++) {
//			glVertex2f(pointsOnCurve[i].x, pointsOnCurve[i].y);
//			glVertex2f(pointsOnCurve[i].x + normOnCurve[i].x, pointsOnCurve[i].y + normOnCurve[i].y);
//		}
		glEnd();
	} else if (mode == MESH) {
		glPushMatrix();
		ctm_multiply();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		pushPointsToGL(false);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPopMatrix();
	} else if (mode == GL_SHADE || mode == GLSL_SHADE) {

		glPushMatrix();
		ctm_multiply();
		pushPointsToGL(true);
		glPopMatrix();
	}
}
void BezierCurve::pushPointsToGL(bool pushNormals) {
	for (unsigned i = 0; i < (angleOfRotation / stepRotation) - 1; i++) {
		glBegin(GL_QUAD_STRIP);
		for (unsigned j = 0; j < pointsOnCurve.size() - 1; j += 2) {
			GLfloat v[4], n0[4];
			pointsOnSurface[i][j].build4tuple(v);
			if (pushNormals) {
				normalsOnSurface[i][j].build4tuple(n0);
				glNormal3fv(n0);
			}
			glVertex3fv(v);
			if (pushNormals){
				normalsOnSurface[i+1][j].build4tuple(n0);
				glNormal3fv(n0);
			}
			pointsOnSurface[i + 1][j].build4tuple(v);
			glVertex3fv(v);
			if (pushNormals){
				normalsOnSurface[i][j+1].build4tuple(n0);
				glNormal3fv(n0);
			}
			pointsOnSurface[i][j + 1].build4tuple(v);
			glVertex3fv(v);
			if (pushNormals){
				normalsOnSurface[i+1][j+1].build4tuple(n0);
				glNormal3fv(n0);
			}
			pointsOnSurface[i + 1][j + 1].build4tuple(v);
			glVertex3fv(v);
		}
		glEnd();

	}
	// normals, for debugging... they look fine, idk why its still so dark
//	for (unsigned i = 0; i < (angleOfRotation / stepRotation) - 1; i++) {
//		glBegin(GL_LINES);
//		for (unsigned j = 0; j < pointsOnCurve.size() - 1; j += 2) {
//			GLfloat v[4], n[4];
//			pointsOnSurface[i][j].build4tuple(v);
//			normalsOnSurface[i][j].build4tuple(n);
//			glVertex3fv(v);
//			glVertex3f(v[0]+n[0], v[1]+n[1],v[2]+n[2]);
//		}
//		glEnd();
//
//	}
}
