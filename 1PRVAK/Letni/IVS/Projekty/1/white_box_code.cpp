//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Code under test
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Authors:    Filip Vaverka <ivaverka@fit.vutbr.cz>
//              David Grochol <igrochol@fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_code.cpp
 * @author Filip Vaverka
 * @author David Grochol
 *
 * @brief Definice metod třídy reprezentující matici.
 */

#include <iostream>

#include "white_box_code.h"

Matrix::Matrix() {
	matrix = std::vector<std::vector<double> >(1, std::vector<double>(1, 0));
}

Matrix::Matrix(size_t row, size_t col) {
	if (row < 1 || col < 1) {
		throw new std::runtime_error("Minimální velikost matice je 1x1");
	}
	matrix = std::vector<std::vector<double> >(row, std::vector<double>(col, 0));
}

Matrix::~Matrix() {
}

bool Matrix::set(size_t row, size_t col, double value) {
	if (!checkIndexes(row, col)) {
		return false;
	}
	matrix[row][col] = value;
	return true;
}

bool Matrix::set(std::vector<std::vector<double>> values) {
	if (matrix.size() > values.size() || matrix[0].size() > values.size()) {
		return false;
	}
	for (int r = 0; r < matrix.size(); r++) {
		for (int c = 0; c < matrix[0].size(); c++) {
			matrix[r][c] = values[r][c];
		}
	}
	return true;
}

double Matrix::get(size_t row, size_t col) {
	if (!checkIndexes(row, col)) {
		return std::numeric_limits<double>::quiet_NaN();
	}
	return matrix[row][col];
}

bool Matrix::operator==(const Matrix m) const {
	if (!checkEqualSize(m)) {
		throw new std::runtime_error("Matice musi mit stejnou velikost.");
	}
	for (int r = 0; r < matrix.size(); r++) {
		for (int c = 0; c < matrix[r].size(); c++) {
			if (matrix[r][c] != m.matrix[r][c]) {
				return false;
			}
		}
	}
	return true;
}

Matrix Matrix::operator+(const Matrix m) const {
	if (!checkEqualSize(m)) {
		throw new std::runtime_error("Matice musi mit stejnou velikost.");
	}
	Matrix result = Matrix(matrix.size(), matrix[0].size());
	for (int r = 0; r < matrix.size(); r++) {
		for (int c = 0; c < matrix[r].size(); c++) {
			result.set(r, c, matrix[r][c] + m.matrix[r][c]);
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix m) const {
	if (matrix[0].size() == m.matrix.size()) {
		Matrix result = Matrix(matrix.size(), m.matrix[0].size());
		for (int r = 0; r < matrix.size(); r++) {
			for (int c = 0; c < m.matrix[0].size(); c++) {
				for (int i = 0; i < matrix[r].size(); i++) {
					result.set(r, c, result.get(r, c) + matrix[r][i] * m.matrix[i][c]);
				}
			}
		}
		return result;
	} else {
		throw new std::runtime_error("Prvni matice musi mit stejný počet sloupcu jako druha radku.");
	}
}

Matrix Matrix::operator*(const double value) const {
	Matrix result = Matrix(matrix.size(), matrix[0].size());

	for (int r = 0; r < matrix.size(); r++) {
		for (int c = 0; c < matrix[r].size(); c++) {
			result.set(r, c, matrix[r][c] * value);
		}
	}
	return result;
}

std::vector<double> Matrix::solveEquation(std::vector<double> b) {
	std::vector<double> res = std::vector<double>(matrix.size(), 0);
	std::vector<std::vector<double>> temp =
			std::vector<std::vector<double> >(matrix.size(),
			                                  std::vector<double>(matrix.size(), 0));
	if (matrix[0].size() != b.size()) {
		throw new std::runtime_error("Pocet prvku prave strany rovnice musi odpovidat poctu radku matice.");
	}
	if (!checkSquare()) {
		throw new std::runtime_error("Matice musi byt ctvercova.");
	}
	int determinatAll = determinant();
	if (determinatAll == 0) {
		throw new std::runtime_error("Matice je singularni.");
	}
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			temp[i][j] = matrix[i][j];
		}
	}
	for (int i = 0; i < matrix.size(); i++) {
		for (int k = 0; k < matrix[i].size(); k++) {
			temp[k][i] = b[k];
		}
		res[i] = deter(temp, temp.size()) / determinatAll;
		for (int k = 0; k < matrix[i].size(); k++) {
			temp[k][i] = matrix[k][i];
		}
	}
	return res;
}

bool Matrix::checkIndexes(size_t row, size_t col) {
	if (row >= matrix.size() || col >= matrix[0].size()) {
		return false;
	}
	return true;
}

bool Matrix::checkSquare() {
	if (matrix.size() == matrix[0].size()) {
		return true;
	}
	return false;
}

bool Matrix::checkEqualSize(const Matrix m) const {
	if (m.matrix.size() == matrix.size() && m.matrix[0].size() == matrix[0].size()) {
		return true;
	}
	return false;
}

double Matrix::determinant() {
	if (matrix.size() == matrix[0].size()) {
		if (matrix.size() == 1) {
			return matrix[0][0];
		} else if (matrix.size() == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		} else if (matrix.size() == 3) {
			return matrix[0][0] * matrix[1][1] * matrix[2][2] +
			       matrix[0][1] * matrix[1][2] * matrix[2][0] +
			       matrix[0][2] * matrix[1][0] * matrix[2][1] -
			       matrix[2][0] * matrix[1][1] * matrix[0][2] -
			       matrix[2][1] * matrix[1][2] * matrix[0][0] -
			       matrix[2][2] * matrix[0][1] * matrix[1][0];
		} else {
			return deter(matrix, matrix.size());
		}
	}
	return 0;
}

std::vector<std::vector<double>> getMinimo(std::vector<std::vector<double>> src, int I, int J, int ordSrc) {

	std::vector<std::vector<double>> minimo(ordSrc - 1, std::vector<double>(ordSrc - 1, 0));

	int rowCont = 0;
	for (int i = 0; i < ordSrc; i++) {
		int colCont = 0;
		if (i != I) {
			for (int j = 0; j < ordSrc; j++) {
				if (j != J) {
					minimo[rowCont][colCont] = src[i][j];
					colCont++;
				}
			}
			rowCont++;
		}
	}
	return minimo;
}

double Matrix::deter(std::vector<std::vector<double>> m, size_t n) {

	if (n == 2) {
		double mainDiag = m[0][0] * m[1][1];
		double negDiag = m[1][0] * m[0][1];

		return mainDiag - negDiag;
	} else {
		double det = 0;
		for (int J = 0; J < n; J++) {
			std::vector<std::vector<double>> min = getMinimo(m, 0, J, n);
			if ((J % 2) == 0) {
				det += m[0][J] * deter(min, n - 1);
			} else {
				det -= m[0][J] * deter(min, n - 1);
			}
		}
		return det;
	}
	return 0;
}

/*** Konec souboru white_box_code.cpp ***/
