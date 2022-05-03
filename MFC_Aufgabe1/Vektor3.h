#pragma once

#define DIM 4

class Vektor3
{
public:
	double vek[DIM];
	Vektor3();
	Vektor3(double x, double y, double z);
};

class Matrix3
{
	double mat[DIM][DIM];
public:
	Matrix3();
	Vektor3 operator * (const Vektor3& v); // Operator überschreiben -> vektor2 = matrix * vektor1
	void setTrans(double dx, double dy);
	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float Z);
};

