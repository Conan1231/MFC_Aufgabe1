#include "pch.h"
#include "Vektor2.h"

// Standardkonstruktor
Vektor2::Vektor2() {
	vek[0] = 0;
	vek[1] = 0;
	vek[2] = 0;
}

// Initialisierungskonstruktor
Vektor2::Vektor2(double x, double y) {
	vek[0] = x;
	vek[1] = y;
	vek[2] = 1;

}

// Konstruktor Matrix
Matrix2::Matrix2() {
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
Vektor2 Matrix2::operator * (const Vektor2& v) {
	Vektor2 temp;
	for (int j = 0; j < DIM; j++) {
		for (int i = 0; i < DIM; i++) {
			temp.vek[j] = temp.vek[j] + mat[i][j] * v.vek[i]; // Zeilenweise vektor befüllen/ausrechnen
		}
	}
	return temp;
}

void Matrix2::setTrans(double dx, double dy) {
	mat[DIM - 1][0] = dx;
	mat[DIM - 1][1] = dy;
}