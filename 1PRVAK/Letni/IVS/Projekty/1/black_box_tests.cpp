//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Jakub "Ash258" Čábera <xcaber00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Jakub "Ash258" Čábera
 * 
 * @brief Implementace testu binárního stromu.
 */

#include <vector>
#include "gtest/gtest.h"
#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLŇTE TESTY **
//
// Zde doplňte testy Red-Black Tree, testujte následující:
// 1. Veřejné rozhraní stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chování těchto metod testuje pro prázdný i neprázdný strom.
// 2. Axiomy (tedy vždy platné vlastnosti) Red-Black Tree:
//    - Všechny listové uzly stromu jsou *VŽDY* černé.
//    - Každý červený uzel může mit *POUZE* černé potomky.
//    - Všechny cesty od každého listového uzlu ke kořeni stromu obsahují
//      *STEJNÝ* počet černých uzlů.
//============================================================================//

class BinaryTreeTestFixture : public ::testing::Test{
protected:
	BinaryTree *binaryTree;
	BinaryTree *emptyTree;

	virtual void TearDown() {
		delete binaryTree;
		delete emptyTree;
	}

	virtual void SetUp() {
		emptyTree  = new BinaryTree();
		binaryTree = new BinaryTree();
		binaryTree->InsertNode(0);
		binaryTree->InsertNode(5);
		binaryTree->InsertNode(7);
	}
};

class BinaryTreeTestFix : public ::testing::Test{
protected:
	BinaryTree tree;
};

TEST_F(BinaryTreeTestFixture, InsertNode_Not_Empty){
	std::pair<bool, BinaryTree::Node_t *> newV = binaryTree->InsertNode(0),
	                                      old  = binaryTree->InsertNode(1);

	ASSERT_FALSE(newV.first);
	ASSERT_TRUE(old.first);
}

TEST_F(BinaryTreeTestFix, InsertNode_Empty){
	std::pair<bool, BinaryTree::Node_t *> newV = tree.InsertNode(1),
	                                      old  = tree.InsertNode(1);

	ASSERT_TRUE(newV.first);
	ASSERT_FALSE(old.first);

	ASSERT_EQ(newV.second, old.second);
}

TEST_F(BinaryTreeTestFixture, FindNode_Not_Empty){
	ASSERT_FALSE(NULL == binaryTree->FindNode(0));
	ASSERT_TRUE(NULL == binaryTree->FindNode(1));

	binaryTree->InsertNode(1);
	ASSERT_FALSE(NULL == binaryTree->FindNode(1));
}

TEST_F(BinaryTreeTestFix, FindNode_Empty){
	ASSERT_TRUE(NULL == tree.FindNode(0));

	tree.InsertNode(0);
	ASSERT_FALSE(NULL == tree.FindNode(0));
}

TEST_F(BinaryTreeTestFixture, DeleteNode_Not_Empty){
	ASSERT_TRUE(binaryTree->DeleteNode(0));
	ASSERT_FALSE(binaryTree->DeleteNode(1));

	binaryTree->InsertNode(1);
	ASSERT_TRUE(binaryTree->DeleteNode(1));
}

TEST_F(BinaryTreeTestFix, DeleteNode_Empty){
	ASSERT_FALSE(tree.DeleteNode(0));

	tree.InsertNode(0);
	ASSERT_TRUE(tree.DeleteNode(0));
}

TEST_F(BinaryTreeTestFixture, Test_Leafs_Colors){
	std::vector<BinaryTree::Node_t *> leafs;
	binaryTree->GetLeafNodes(leafs);

	for(int i = 0; i < leafs.size(); ++i){
		ASSERT_EQ(BinaryTree::BLACK, leafs[i]->color);
	}
}

/*** Konec souboru black_box_tests.cpp ***/
