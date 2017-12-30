//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Self balancing Tree public interface
//
// $NoKeywords: $ivs_project_1 $red_black_tree.h
// $Authors:    Filip Vaverka <ivaverka@fit.vutbr.cz>
//              David Grochol <igrochol@fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file red_black_tree.h
 * @author Filip Vaverka
 * @author David Grochol
 * 
 * @brief Definice rozhrani binarniho stromu.
 */

#pragma once

#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include <utility>
#include <vector>

/**
 * @brief The BinaryTree class
 * Samo-vyvazujici se binarni strom, kde hodnoty jsou ulozeny pouze ve vnitrnich
 * uzlech (uzly krom listu). Automaticke vyvazovani stromu je umozneno rozdelenim
 * uzlu do dvou mnozin (cervene a cerne).
 */
class BinaryTree
{
public:
    /**
     * @brief The Color_t enum
     * Barva uzlu stromu. Mimo tridu BinaryTree dostupne jako: "BinaryTree::RED".
     */
    enum Color_t {
        RED = 0,
        BLACK
    };

    /**
     * @brief The Node_t struct
     * Struktura uzlu stromu.
     */
    struct Node_t {
        Node_t(int key, Node_t *pParent, Node_t *pLeft = NULL, Node_t *pRight = NULL,
               Color_t color = BLACK)
            : pParent(pParent), pLeft(pLeft), pRight(pRight), color(color), key(key)
        {
        }

        /**
         * @brief IsLeaf
         * @return Vraci true, pokud je uzel listovym uzlem (nema tedy dalsi potomky).
         */
        bool IsLeaf() const {
            return (!pLeft && !pRight);
        }

        Node_t *pParent;    ///< Ukazatel na rodice uzlu, nebo NULL v pripade korene.
        Node_t *pLeft;      ///< Ukazatel na leveho potomka uzlu, nebo NULL pro listovy uzel.
        Node_t *pRight;     ///< Ukazatel na praveho potomka uzlu, nebo NULL pro listovy uzel.
        Color_t color;      ///< Barva uzlu (Color_t), tj. RED nebo BLACK.

        int key;            ///< Hodnota/klic tohoto uzlu.
    };

	/**
	 * @brief BinaryTree
	 * Konstruktor prazdneho binarniho stromu.
	 */
    BinaryTree();

	/**
	 * @brief BinaryTree
	 * Destruktor binarniho stromu, odstrani vsechny uzly v nem obsazene.
	 */
    ~BinaryTree();

    /**
     * @brief InsertNode
     * Pokusi se vlozit novy uzel s hodnotou "key", nebo nalezne jiz existujici
     * uzel s touto hodnotou (hodnoty uzlu musi byt unikatni).
     * @param key Nova hodnota vkladana do stromu.
     * @return Vraci dvojici (true, ukazatel na novy uzel), pokud uzel jeste
     * neexistoval, nebo (false, ukazatel na existujici uzel), pokud uzel s danou
     * hodnotou jiz existuje.
     */
    std::pair<bool, Node_t *> InsertNode(int key);

    /**
     * @brief DeleteNode
     * Pokusi se odstranit uzel s hodnotou "key"
     * @param key Hodnota uzlu, ktery ma byt odstranen.
     * @return Vraci true, pokud je uzel nalezen a odstranen, jinak false.
     */
    bool DeleteNode(int key);

    /**
     * @brief FindNode
     * Pokusi se nalezt uzel s hodnotou "key"
     * @param key Hodnota hledaneho uzlu
     * @return Vraci ukazatel na nalezeny uzel, nebo NULL, pokud takovy uzel
     * neni nalezen.
     */
    Node_t *FindNode(int key) const;

    /**
     * @brief GetLeafNodes
     * Projde cely strom a sestavi pole listovych uzlu, ktere nemaji potomky.
     * @param outLeafNodes Pole naplnene ukazateli na listove uzly (pole je
     * nejdrive vyprazdneno).
     */
    void GetLeafNodes(std::vector<Node_t *> &outLeafNodes);

    /**
     * @brief GetAllNodes
     * Projde cely strom a sestavi pole ukazatelu na vsechny uzly ve stromu.
     * @param outAllNodes Pole naplnene ukazateli na uzly ve stromu (pole je
     * nejdrive vyprazdneno).
     */
    void GetAllNodes(std::vector<Node_t *> &outAllNodes);

    /**
     * @brief GetNonLeafNodes
     * Projde cely strom a sestavi pole ukazatelu na vsechny NE-listove
     * uzly stromu (tedy s alespon 1 potomkem).
     * @param outNonLeafNodes Pole naplnene ukazateli na NE-listove uzly
     * ve stromu (pole je nejdrive vyprazdneno).
     */
    void GetNonLeafNodes(std::vector<Node_t *> &outNonLeafNodes);

    /**
     * @brief GetRoot
     * @return Vraci ukazatel na korenovy uzel stromu, nebo NULL, pokud je strom prazdny.
     */
    Node_t *GetRoot() { return m_pRoot; }

protected:
    // Pomocne metody pro vnitrni funkci stromu.
    Node_t *GrandParent(Node_t *pNode);
    Node_t *Uncle(Node_t *pNode);
    Node_t *Sibling(Node_t *pNode);
    void RotateRight(Node_t *pNode);
    void RotateLeft(Node_t *pNode);
    void ReplaceNode(Node_t *pReplacedNode, Node_t *pNode);

    // Pomocne metody pro vyvazovani stromu po vlozeni noveho uzlu.
    void InsertFixUpTreeCase1(Node_t *pNewNode);
    void InsertFixUpTreeCase2(Node_t *pNewNode);
    void InsertFixUpTreeCase3(Node_t *pNewNode);
    void InsertFixUpTreeCase4(Node_t *pNewNode);
    void InsertFixUpTreeCase5(Node_t *pNewNode);

    // Pomocne metody pro vyvazovani po odstraneni uzlu.
    void DeleteNodeFixUpCase1(Node_t *pNode);
    void DeleteNodeFixUpCase2(Node_t *pNode);
    void DeleteNodeFixUpCase3(Node_t *pNode);
    void DeleteNodeFixUpCase4(Node_t *pNode);
    void DeleteNodeFixUpCase5(Node_t *pNode);
    void DeleteNodeFixUpCase6(Node_t *pNode);

    Node_t *m_pRoot;    ///< Ukazatel na koren stromu.
};



#endif /* RED_BLACK_TREE_H_ */
