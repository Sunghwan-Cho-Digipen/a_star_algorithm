/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.cpp
Purpose: Source file for Transform Matrix
Project: CS230
Author: Kevin Wright
Creation date: 4/09/2020
-----------------------------------------------------------------*/
#include <cmath>   //std::sin & std::cos

#include "TransformMatrix.h"

TransformMatrix::TransformMatrix() { 
	Reset();
}

void TransformMatrix::Reset(){
	matrix[0][0] = 1.0; 	matrix[0][1] = 0.0; 	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0; 	matrix[1][1] = 1.0; 	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0; 	matrix[2][1] = 0.0; 	matrix[2][2] = 1.0;
}

TranslateMatrix::TranslateMatrix(Vector2DInt translate) {
	matrix[0][0] = 1;		matrix[0][1] = 0;		matrix[0][2] = translate.x;
	matrix[1][0] = 0;		matrix[1][1] = 1;		matrix[1][2] = translate.y;
	matrix[2][0] = 0;		matrix[2][1] = 0;		matrix[2][2] = 1;
}

TranslateMatrix::TranslateMatrix(Vector2D translate) {
	matrix[0][0] = 1;		matrix[0][1] = 0;		matrix[0][2] = translate.x;
	matrix[1][0] = 0;		matrix[1][1] = 1;		matrix[1][2] = translate.y;
	matrix[2][0] = 0;		matrix[2][1] = 0;		matrix[2][2] = 1;
}

RotateMatrix::RotateMatrix(double radians) {
	matrix[0][0] = std::cos(radians);	matrix[0][1] = -std::sin(radians);		matrix[0][2] = 0;
	matrix[1][0] = std::sin(radians);	matrix[1][1] = std::cos(radians);		matrix[1][2] = 0;
	matrix[2][0] = 0;					matrix[2][1] = 0;						matrix[2][2] = 1;
}

ScaleMatrix::ScaleMatrix(Vector2D scale) {
	matrix[0][0] = scale.x;		matrix[0][1] = 0;			matrix[0][2] = 0;
	matrix[1][0] = 0;			matrix[1][1] = scale.y;		matrix[1][2] = 0;
	matrix[2][0] = 0;			matrix[2][1] = 0;			matrix[2][2] = 1;
}

TransformMatrix TransformMatrix::operator * (TransformMatrix rhs) const {
	TransformMatrix result;

	result[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
	result[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
	result[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
	result[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
	result[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
	result[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
	result[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
	result[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
	result[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

	return result;
}

Vector2D TransformMatrix::operator * (Vector2D rhs) const {
	Vector2D result;
	result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y;
	result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y;
	return result;
}

TransformMatrix& TransformMatrix::operator *= (TransformMatrix rhs) {
	(*this) = (*this) * rhs;
	return (*this);
}