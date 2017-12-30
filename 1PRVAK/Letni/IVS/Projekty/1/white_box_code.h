//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Code under test
//
// $NoKeywords: $ivs_project_1 $white_box_code.h
// $Authors:    Filip Vaverka <ivaverka@fit.vutbr.cz>
//              David Grochol <igrochol@fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_code.h
 * @author Filip Vaverka
 * @author David Grochol
 *
 * @brief Deklarace třídy matice umožňující základní maticové operace.
 */

#pragma once

#ifndef MATRIX_H_
#define MATRIX_H_

#include <utility>
#include <vector>
#include <limits>
#include <cmath>

/** @brief Třída reprezentující matici. */
class Matrix {
public:
	/** @brief Konstruktor vytvoří nulovou matici velikosti 1x1. */
	Matrix();

	/**
	 * @brief Konstruktor vytvoří nulovou matici velikosti "row" x "col".
	 *
	 * @param row Řádek matice.
	 * @param col Sloupec matice.
	 */
	Matrix(size_t row, size_t col);

	/**
	 * @brief Destruktor.
	 */
	~Matrix();

	/**
	 * @brief Nastaví hodnotu v matici na pozici x,y.
	 *
	 * @param row Řádek matice.
	 * @param col Sloupec matice.
	 * @param value Hodnota uložena na pozici x,y.
	 *
	 * @return Pokud bylo vložení úspěšné vrátí true, jinak false.
	 */
	bool set(size_t row, size_t col, double value);

	/**
	 * @brief Nastaví matici hodnotami z pole.
	 *
	 * @param values Hodnoty pro inicializaci matice.
	 *
	 * @return Pokud bylo vložení úspěšné vrátí true, jinak false.
	 */
	bool set(std::vector<std::vector<double>> values);

	/**
	 * @brief Vrátí hodnotu v matici na pozici x,y.
	 *
	 * @param row Řádek matice.
	 * @param col Sloupec matice.
	 *
	 * @return Hodnota v matici na pozici x,y.
	 */
	double get(size_t row, size_t col);

	/**
	 * @brief Porovnání dvou matic.
	 *
	 * @param Matrix Matice pro porovnání.
	 *
	 * @return Pokud jsou matice shodné tak vrátí true, jinak false.
	 */
	bool operator==(const Matrix) const;

	/**
	 * @brief Sčítání dvou matice.
	 *
	 * @param Matrix Druhý sčítanec.
	 *
	 * @return Výsledná matice po sečtení matic.
	 */
	Matrix operator+(const Matrix) const;

	/**
	 * @brief Násobení matic.
	 *
	 * @param Matrix Druhy činitel.
	 *
	 * @return Výsledná matice po vynásobení matic.
	 */
	Matrix operator*(const Matrix) const;

	/**
	 * @brief Vynásobí matici skalární hodnotou.
	 *
	 * @param value Skalární činitel.
	 *
	 * @return Výsledná matice po vynásobení matice skalárem.
	 */
	Matrix operator*(const double value) const;

	/**
	 * @brief Řešení soustavy lineárních rovnic.
	 * Soustava rovnic je řešená pomocí Cramerova pravidla.
	 *
	 * @param b Pravá strana rovnice.
	 *
	 * @return Pole výsledků x1, x2, ...
	 */
	std::vector<double> solveEquation(std::vector<double> b);

protected:
	/** @brief 2D pole reprezentující matici */
	std::vector<std::vector<double>> matrix;

	/**
	 * @brief Kontrola zda indexy row, col jsou v matici.
	 *
	 * @param row Řádek matice.
	 * @param col Sloupec matice.
	 *
	 * @return Pokud je alespoň jeden index mimo matici vrátí false, jinak true.
	 */
	bool checkIndexes(size_t row, size_t col);

	/**
	 * @brief Kontrola zda mají matice shodnou velikost.
	 *
	 * @param m Matice pro porovnání.
	 *
	 * @return Pokud mají matice shodnou velikost vrátí true, jinak false.
	 */
	bool checkEqualSize(const Matrix m) const;

	/**
	 * @brief Kontrola zda je matice čtvercová.
	 *
	 * @return Pokud je matice čtvercová tak vrátí true, jinak false.
	 */
	bool checkSquare();

	/**
	 * @brief Vypočte determinant matice.
	 *
	 * @return Vrátí hodnotu determinantu matice.
	 */
	double determinant();

	/**
	 * @brief Pomocná funkce pro výpočet determinantu matice vyšších řádů.
	 *
	 * @param m Matice.
	 * @param n Řád matice.
	 *
	 * @return Vrátí hodnotu determinantu matice.
	 */
	double deter(std::vector<std::vector<double>> m, size_t n);
};

#endif /* MATRIX_H_ */
