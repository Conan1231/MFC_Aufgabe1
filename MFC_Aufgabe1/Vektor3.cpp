#include "pch.h"
#include "Vektor3.h"


// Standardkonstruktor
Vektor3::Vektor3() {
	vek[0] = 0;
	vek[1] = 0;
	vek[2] = 0;
	vek[3] = 0;
}

// Initialisierungskonstruktor
Vektor3::Vektor3(double x, double y, double z) {
	vek[0] = x;
	vek[1] = y;
	vek[2] = z;
	vek[3] = 1;

}

// Konstruktor Matrix
Matrix3::Matrix3() {
	for (int i = 0; i < DIM; i++) {  // j = Zeile ; i = Spalte
		for (int j = 0; j < DIM; j++) {
			if (i == j) {
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}
}

// Definition der Operatorüberschreibung, immer in Klasse des rechten Operanden!
Vektor3 Matrix3::operator * (const Vektor3& v) {
	Vektor3 temp;
	for (int j = 0; j < DIM; j++) {
		for (int i = 0; i < DIM; i++) {
			temp.vek[j] = temp.vek[j] + mat[i][j] * v.vek[i]; // Zeilenweise vektor befüllen/ausrechnen
		}
	}
	return temp;
}

void Matrix3::setTrans(double dx, double dy) {
	mat[DIM - 1][0] = dx;
	mat[DIM - 1][1] = dy;
	//mat[DIM - 1][2] = dz;
}

void Matrix3::setRotationX(float x) { // Um den Punkt X Rotieren -> Koordinaten Y und Z übergeben | xneu = xalt | yneu = y*cos(a) + z * sin(a) | zneu = y * -sin(a) + z * cos(a)
	mat[1][1] = cos(x);
	mat[1][2] = sin(x);
	mat[2][1] = -sin(x);
	mat[2][2] = cos(x);
	mat[0][0] = mat[3][3] = 1;
	mat[0][1] = mat[0][2] = mat[0][3] = mat[1][0] = mat[1][3] = mat[2][0] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
}

void Matrix3::setRotationY(float y) {
	mat[0][0] = cos(y);
	mat[0][2] = -sin(y);
	mat[2][0] = sin(y);
	mat[2][2] = cos(y);
	mat[1][1] = mat[3][3] = 1;
	mat[0][1] = mat[0][3] = mat[1][0] = mat[1][2] = mat[1][3] = mat[2][1] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
}

void Matrix3::setRotationZ(float z) {
	mat[0][0] = cos(z);
	mat[0][1] = sin(z);
	mat[1][0] = -sin(z);
	mat[1][1] = cos(z);
	mat[2][2] = mat[3][3] = 1;
	mat[0][2] = mat[0][3] = mat[1][2] = mat[1][3] = mat[2][0] = mat[2][1] = mat[2][3] = mat[3][0] = mat[3][1] = mat[3][2] = 0;
}