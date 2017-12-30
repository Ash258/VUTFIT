//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Jakub "Ash258" Čábera <xcaber00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Jakub "Ash258" Čábera
 *
 * @brief Implementace testu práce maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLŇTE TESTY **
//
// Zde doplňte testy operací nad maticemi. Cílem testování je:
// 1. Dosáhnout maximálního pokrytí kódu (white_box_code.cpp) testy.
// 2. Ověřit správné chování operací nad maticemi v závislosti na rozměrech matic.
//============================================================================//

class MatrixTestFixture : public ::testing::Test{
protected:
	Matrix *emptyMatrix;
	Matrix *twoRowsSquare;

	virtual void SetUp(){
		emptyMatrix = new Matrix();

		twoRowsSquare = new Matrix(2, 2);

		twoRowsSquare->set(0, 0, 258);
		twoRowsSquare->set(0, 1, 259);
		twoRowsSquare->set(1, 0, 260);
		twoRowsSquare->set(1, 1, 261);
	}

	virtual void TearDown(){
		delete twoRowsSquare;
		delete emptyMatrix;
	}
};

TEST (MatrixTest, Construct){
	Matrix tested, expected(1, 1);

	ASSERT_TRUE(tested == expected);
	ASSERT_THROW(new Matrix(0, 0), std::runtime_error*);
	ASSERT_THROW(new Matrix(1, 0), std::runtime_error*);
	ASSERT_THROW(new Matrix(0, 1), std::runtime_error*);
}

TEST (MatrixTest, Set_Scalar){
	Matrix test(2, 2);

	ASSERT_TRUE(test.set(0, 0, 258));
	ASSERT_TRUE(test.set(1, 1, 258));

	ASSERT_FALSE(test.set(5, 0, 258));
	ASSERT_FALSE(test.set(0, 10, 258));
}

TEST (MatrixTest, Set_Vector){
	Matrix                            test(4, 4);
	std::vector<std::vector<double> > equalSize(4, std::vector<double>(4, 4));
	std::vector<std::vector<double> > differentSize(3, std::vector<double>(4, 4));

	ASSERT_TRUE(test.set(equalSize));
	ASSERT_FALSE(test.set(differentSize));
}

/**
 * @brief Při test.get(1,1), by měla být vyhozena výjimka (podle definice) => Špatně naprogramovaná funkce.
 */
TEST (MatrixTest, Get){
	Matrix test(1, 1);
	test.set(0, 0, 258);

	ASSERT_EQ(258, test.get(0, 0));
	//ASSERT_ANY_THROW(test.get(0,0));
}

TEST (MatrixTest, EQ_Same_Size){
	Matrix matrix(4, 4), matrix2(4, 4);

	ASSERT_TRUE(matrix == matrix2);

	matrix.set(0, 0, 0);
	matrix2.set(0, 0, 0);
	ASSERT_TRUE(matrix == matrix2);

	matrix.set(1, 1, 1);
	matrix2.set(1, 1, 258);
	ASSERT_FALSE(matrix == matrix2);
}

TEST(MatrixTest, EQ_Difference_Size){
	Matrix matrix(2, 2), matrix2(3, 3);

	ASSERT_THROW(matrix == matrix2, std::runtime_error*);
}

TEST_F(MatrixTestFixture, Add){
	Matrix result = (*twoRowsSquare + *twoRowsSquare);

	ASSERT_EQ(516, result.get(0, 0));
	ASSERT_EQ(518, result.get(0, 1));
	ASSERT_EQ(520, result.get(1, 0));
	ASSERT_EQ(522, result.get(1, 1));

	ASSERT_THROW((*emptyMatrix + *twoRowsSquare), std::runtime_error*);

	ASSERT_TRUE(std::isnan(twoRowsSquare->get(2, 0)));
}

TEST_F(MatrixTestFixture, Multiple_Matrix){
	Matrix result = (*twoRowsSquare * *twoRowsSquare);

	ASSERT_EQ(133904, result.get(0, 0));
	ASSERT_EQ(134421, result.get(0, 1));
	ASSERT_EQ(134940, result.get(1, 0));
	ASSERT_EQ(135461, result.get(1, 1));

	ASSERT_THROW((*twoRowsSquare * *emptyMatrix), std::runtime_error*);

	ASSERT_TRUE(std::isnan(twoRowsSquare->get(2, 0)));
}

TEST_F(MatrixTestFixture, SolveEquation){
	std::vector<double> equation;
	std::vector<double> expected;

	equation = {1, 3};
	expected = {258, -257};
	ASSERT_EQ(expected, twoRowsSquare->solveEquation(equation));

	Matrix four(4, 4);
	four.set(std::vector<std::vector<double>> {
			std::vector<double> {4, 1, 2, -3},
			std::vector<double> {-3, 3, -1, 4},
			std::vector<double> {-1, 2, 5, 1},
			std::vector<double> {5, 4, 3, -1}
	});
	equation = {-16, 20, -4, -10};
	expected = {-1, 1, -2, 3};
	ASSERT_EQ(expected, four.solveEquation(equation));
}

TEST_F(MatrixTestFixture, SolveEquation_Fail){
	std::vector<double> bigVector(3, 3);

	Matrix              nonSquare(1, 5);
	std::vector<double> nonSquareStatement(5, 1);

	Matrix              singular(2, 2);
	std::vector<double> singularStatement(2, 2);

	singular.set({});
	singular.set(0, 0, 1);
	singular.set(0, 1, -2);
	singular.set(1, 0, -2);
	singular.set(1, 1, 4);

	ASSERT_THROW(twoRowsSquare->solveEquation(bigVector), std::runtime_error*);
	ASSERT_THROW(nonSquare.solveEquation(nonSquareStatement), std::runtime_error*);
	ASSERT_THROW(singular.solveEquation(singularStatement), std::runtime_error*);
}

TEST_F(MatrixTestFixture, Multiple_Scalar){
	Matrix result = *twoRowsSquare * 5;

	ASSERT_EQ(1290, result.get(0, 0));
	ASSERT_EQ(1295, result.get(0, 1));
	ASSERT_EQ(1300, result.get(1, 0));
	ASSERT_EQ(1305, result.get(1, 1));
}
/*** Konec souboru white_box_tests.cpp ***/
