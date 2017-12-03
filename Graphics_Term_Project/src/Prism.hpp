/*
 * Prism.h
 *
 *  Created on: Dec 2, 2017
 *      Author: ryanw
 */

#ifndef PRISM_HPP_
#define PRISM_HPP_
#include "Shape.hpp"
#include <vector>
#include "Vector.hpp"

class Prism: public Shape{
public:
	Prism(std::vector<Point> points, GLfloat height);
	virtual ~Prism();
	void draw();
private:
	vector<Point> points;
	vector<Vector> normalsOnSideFaces;
	GLfloat height;
	int wrapPoints(int i);
};

#endif /* PRISM_HPP_ */
