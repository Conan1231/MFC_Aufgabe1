#include "pch.h"
#include "Vektor3.h"


// Standardkonstruktor
Vektor3::Vektor3() {

}

/*Vektor3::Vektor3(double x, double y, double z) {
	cube[0] = x;
	cube[1] = y;
	cube[2] = z;
	cube[3] = 1;
}*/

void setRotationX(float x) {
	cube[1][1] = cos(x);
	cube[1][2] = sin(x);
	cube[2][1] = -sin(x);
	cube[2][2] = cos(x);
}

void setRotationY(float y) {
	cube[0][0] = cos(y);
	cube[0][2] = -sin(y);
	cube[2][0] = sin(y);
	cube[2][2] = cos(y);
}

void setRotationZ(float Z) {
	cube[0][0] = cos(z);
	cube[0][1] = sin(z);
	cube[1][0] = -sin(z);
	cube[1][1] = cos(z);
}