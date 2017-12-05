/**
 *	File Matrix.cpp
 *	Description: implementation of Matrix class
 *
 */

#include "Matrix.hpp"

// construct an identity matrix as mat
Matrix::Matrix() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				this->mat[i][j] = 1;
			else
				this->mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrix_pre_multiply(Matrix* m) {
	Matrix* temp = new Matrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLfloat sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += m->mat[i][k] * this->mat[k][j];
			}
			temp->mat[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->mat[i][j] = temp->mat[i][j];
		}
	}
	delete temp;
}

// translate the origin of MC
void Matrix::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	this->mat[0][3] += tx;
	this->mat[1][3] += ty;
	this->mat[2][3] += tz;
	this->mat[3][3] = 1;
}

void Matrix::transpose() {
	GLfloat tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			tmp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = tmp;
		}
	}
}

// normalize MC
void Matrix::normalize() {
	GLfloat vectLen = sqrt(mat[0][0] * mat[0][0] + mat[1][0] * mat[1][0] + mat[2][0] * mat[2][0]);
	//normalize first 3
	mat[0][0] /= vectLen;
	mat[1][0] /= vectLen;
	mat[2][0] /= vectLen;

	//take determinants for first 3 values in col 2
	mat[0][2] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
	mat[1][2] = mat[2][0] * mat[0][1] - mat[0][0] * mat[2][1];
	mat[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];

	vectLen = sqrt(mat[0][2] * mat[0][2] + mat[1][2] * mat[1][2] + mat[2][2] * mat[2][2]);
	// normalize first 3 in column 2
	mat[0][2] /= vectLen;
	mat[1][2] /= vectLen;
	mat[2][2] /= vectLen;

	//set fisrt 3 in column 1 to the determinants calcululated from column 0 and column 2
	mat[0][1] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
	mat[1][1] = mat[2][2] * mat[0][0] - mat[2][0] * mat[0][2];
	mat[2][1] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];
	//reset column 3
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

// v  <- mat * v. V must have 4 elements
void Matrix::multiply_vector(GLfloat* v) {
	double sum, temp[4];
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += v[j] * this->mat[j][i];
		}
		temp[i] = sum;
	}
	for (int i = 0; i < 4; i++) {
		v[i] = temp[i];
	}
}

// MC <= rotation matrix * MC, i.e., rotate cordinate vectors and the origin
void Matrix::rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
	GLfloat radAngle = angle * 3.1415926 / 180;
	GLfloat vectLen = sqrt(x * x + y * y + z * z);
	GLfloat cosA = cos(radAngle);
	GLfloat sinA = sin(radAngle);
	GLfloat ux = x / vectLen, uy = y / vectLen, uz = z / vectLen;

	Matrix r; // rotation matrix to be multiplied as this*r
	r.mat[0][0] = ux * ux * (1 - cosA) + cosA;
	r.mat[0][1] = ux * uy * (1 - cosA) - uz * sinA;
	r.mat[0][2] = ux * uz * (1 - cosA) + uy * sinA;

	r.mat[1][0] = uy * ux * (1 - cosA) + uz * sinA;
	r.mat[1][1] = uy * uy * (1 - cosA) + cosA;
	r.mat[1][2] = uy * uz * (1 - cosA) - ux * sinA;

	r.mat[2][0] = uz * ux * (1 - cosA) - uy * sinA;
	r.mat[2][1] = uz * uy * (1 - cosA) + ux * sinA;
	r.mat[2][2] = uz * uz * (1 - cosA) + cosA;

	matrix_pre_multiply(&r);
}

void Matrix::printMatrix() {
	std::cout << "Matrix:" << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}
Vector Matrix::getPosVect() {
	Vector v;
	v.x = mat[0][3];
	v.y = mat[1][3];
	v.z = mat[2][3];
	return v;
}

void Matrix::copy(Matrix from) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = from.mat[i][j];
		}
	}
}

void Matrix::ctm_multiply(){
	GLfloat M[16];
	M[0] = mat[0][0];
	M[1] = mat[1][0];
	M[2] = mat[2][0];
	M[3] = 0;
	M[4] = mat[0][1];
	M[5] = mat[1][1];
	M[6] = mat[2][1];
	M[7] = 0;
	M[8] = mat[0][2];
	M[9] = mat[1][2];
	M[10] = mat[2][2];
	M[11] = 0;
	M[12] = mat[0][3];
	M[13] = mat[1][3];
	M[14] = mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);
}
