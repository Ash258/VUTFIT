//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.h
// $Author:     Jakub "Ash258" Čábera <xcaber00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file tdd_code.h
 * @author Jakub "Ash258" Čábera
 * 
 * @brief Definice rozhraní prioritní fronty.
 */

#pragma once

#ifndef TDD_CODE_H_
#define TDD_CODE_H_

/**
 * @brief Třída reprezentující prioritní frontu.
 * Prioritní fronta (položky vždy seřazeny od min po max) implementována pomocí
 * tzv. double-linked listu (každá položka má odkaz na předcházející a následující položku).
 * Dále má každá položka hodnotu typu "int", přičemž fronta může obsahovat více
 * položek se stejnou hodnotou.
 */
class PriorityQueue {
	//region public
	/**
	 * @brief Metody, struktury atd tvoří veřejné "public" rozhraní prioritní fronty.
	 * METODY, STRUKTURY ATD. V TÉTO SEKCI *NEUPRAVUJTE*
	 */
public:
	/** @brief Vytvoří prázdnou frontu. */
	PriorityQueue();

	/** @brief Odstraní všechny položky i frontu samotnou. */
	~PriorityQueue();

	/** @brief Struktura položky ve frontě. */
	struct Element_t {
		/** Ukazatel na následující prvek ve frontě. */
		Element_t *pNext; ///< Ukazatel na následující prvek ve frontě.
		/** Ukazatel na předcházející prvek ve frontě. */
		Element_t *pPrev; ///< Ukazatel na předcházející prvek ve frontě.
		/** Hodnota teto položky ve frontě. */
		int value; ///< Hodnota teto položky ve frontě.
	};

	/**
	 * @brief Zařadí novou položku s hodnotou "value" do fronty na patřičné místo (tak aby bylo zachováno pořadí min->max).
	 * Pokud položka s danou hodnotou již existují zařadí novou položku před/za již existující
	 *
	 * @param value Hodnota nové položky.
	 */
	void Insert(int value);

	/**
	 * @brief Odstraní položku s hodnotou "value" z fronty a vrátí "true", pokud položka není nalezena vrátí "false".
	 * Pokud se ve frontě nachází více položek se stejnou hodnotou "value", pak odstraní libovolnou z nich.
	 *
	 * @param value Hodnota položky, která má být odstraněna.
	 *
	 * @return Vrátí true, pokud byla položka nalezena a odstraněna, jinak vrací false.
	 */
	bool Remove(int value);

	/**
	 * @brief Nalezne libovolnou položku s hodnotou "value" a vrátí ukazatel na tuto položku, nebo NULL pokud taková neexistuje.
	 *
	 * @param value Hodnota hledané položky.
	 *
	 * @return Vrátí ukazatel na položku s hodnotou "value", nebo NULL pokud taková neexistuje.
	 */
	Element_t *Find(int value);

	/**
	 * @brief Vrací ukazatel na první položku ve frontě, která je vždy zároveň položkou s nejmenší hodnotou.
	 *
	 * @return Vrací ukazatel na 1./nejmenší položku fronty, nebo NULL, pokud je fronta prázdná.
	 */
	Element_t *GetHead();
	//endregion

	/** @brief Zde můžete doplnit neveřejné metody a datové položky potřebné pro vaši implementaci. */
protected:
	/** Ukazatel na první prvek fronty. */
	Element_t *head; ///< Ukazatel na první prvek fronty.

	/**
	 * @brief Zjistí zda je fronta prázdná.
	 *
	 * @return Pokud je fronta prázdná vrací "true", jinak "false"
	 */
	bool Empty();

	/**
	 * @brief "Konstruktor" elementu.
	 *
	 * @param value Hodnota nového elementu.
	 *
	 * @return Ukazatel na nově vytvořený prvek.
	 */
	Element_t *CreateElement(int value);
};

#endif // TDD_CODE_H_
