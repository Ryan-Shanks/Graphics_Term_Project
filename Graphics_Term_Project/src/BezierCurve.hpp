/*
 * BezierCurve.h
 *
 *  Created on: Nov 11, 2017
 *      Author: ryanw
 */

#ifndef SRC_BEZIERCURVE_HPP_
#define SRC_BEZIERCURVE_HPP_

#include <vector>
#include "Point.hpp"
#include "Shape.hpp"
#define DEFAULT_SLICES 20
enum DrawingMode{
	TWO_D, MESH, GL_SHADE, GLSL_SHADE
};
class BezierCurve: public Shape {
public:
	BezierCurve();
	BezierCurve(std::vector<Point*> controlPoints, int numCurvePoints, int angleOfRotation, int stepAngleOfRotation);
	void draw();
	void setDrawingMode(DrawingMode d);
	virtual ~BezierCurve();
private:
	void computeBezierPoint(GLint n);
	void computeBezierNorms();
	std::vector<Point*> controlPoints;
	std::vector<Point> pointsOnCurve;
	std::vector<Vector> normOnCurve;
	void computePointsOnCurve();
	DrawingMode mode;
	unsigned angleOfRotation;
	void fillInVerticesAndNormalsToDraw();
	std::vector<std::vector<Point> > pointsOnSurface;
	std::vector<std::vector<Vector> > normalsOnSurface;
	unsigned stepRotation;
	void pushPointsToGL(bool pushNormals);
};

#endif /* SRC_BEZIERCURVE_HPP_ */
