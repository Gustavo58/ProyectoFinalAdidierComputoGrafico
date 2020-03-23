#include "Vector2.h"

float Vector2::getX()
{
	return a;
}

void Vector2::setX(float a)
{
	this->a = a;
}

float Vector2::getY()
{
	return b;
}

void Vector2::setY(float b)
{
	this->b = b;
}

Vector2::Vector2(float a, float b)
{
	this->a = a;
	this->b = b;
}

Vector2::Vector2()
{
}