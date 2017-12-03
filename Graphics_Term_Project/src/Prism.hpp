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

class Prism: public Shape{
public:
	Prism(std::vector<Point> points, GLfloat height);
	virtual ~Prism();
	void draw();
private:
	vector<Point> points;
	GLfloat height;
};

#endif /* PRISM_HPP_ */
