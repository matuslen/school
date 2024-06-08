//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     MATUS LENGVARSKY <xlengv00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Matus Lengvarsky
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

class EmptyTable :public::testing::Test
{
    protected:
    hash_map_t* map;

    void virtual SetUp(){
        map = hash_map_ctor();
    }
    void virtual TearDown(){
        hash_map_dtor(map);
    }
};

class NonEmptyTable :public::testing::Test
{
    protected:
    hash_map_t* map;

    void virtual SetUp(){
        map = hash_map_ctor();
        hash_map_put(map, "test1", 2);
        hash_map_put(map, "test2", 4);
        hash_map_put(map, "test3", 6);
    }
    void virtual TearDown(){
        hash_map_dtor(map);
    }
};

TEST_F(EmptyTable, capacity){
    EXPECT_EQ(hash_map_capacity(map), 8);
}

TEST_F(EmptyTable, contains){
    EXPECT_FALSE(hash_map_contains(map, "test1"));
}

TEST_F(EmptyTable, get){
    int get = 5;
    EXPECT_EQ(hash_map_get(map, "test1", &get), KEY_ERROR);
}

TEST_F(EmptyTable, size){
    EXPECT_EQ(hash_map_size(map), 0);
}

TEST_F(EmptyTable, remove){
    EXPECT_EQ(hash_map_remove(map, "test1"), KEY_ERROR);
}

TEST_F(EmptyTable, reserve){
    EXPECT_EQ(hash_map_reserve(map, 20), OK);
    EXPECT_EQ(hash_map_capacity(map), 20);
}

TEST_F(EmptyTable, pop){
    int pop = 2;
    EXPECT_EQ(hash_map_pop(map, "test1", &pop), KEY_ERROR);
}

TEST_F(EmptyTable, put){
    EXPECT_EQ(hash_map_put(map, "test1", 2), OK);
    EXPECT_EQ(hash_map_size(map), 1);
    EXPECT_EQ(hash_map_contains(map, "test1"), true);
    EXPECT_EQ(hash_map_capacity(map), 8);
}

TEST_F(NonEmptyTable, contains){
    EXPECT_TRUE(hash_map_contains(map, "test1"));
    EXPECT_FALSE(hash_map_contains(map, "test4"));
}

TEST_F(NonEmptyTable, capacity){
    EXPECT_EQ(hash_map_capacity(map), 8);
}

TEST_F(NonEmptyTable, get){
    int get;
    EXPECT_EQ(hash_map_get(map, "test1", &get), OK);
    EXPECT_EQ(get, 2);
    EXPECT_EQ(hash_map_get(map, "test4", &get), KEY_ERROR);
}

TEST_F(NonEmptyTable, size){
    EXPECT_EQ(hash_map_size(map), 3);
}

TEST_F(NonEmptyTable, remove){
    EXPECT_EQ(hash_map_remove(map, "test1"), OK);
    EXPECT_FALSE(hash_map_contains(map, "test1"));
    EXPECT_EQ(hash_map_remove(map, "test4"), KEY_ERROR);
}

TEST_F(NonEmptyTable, reserve){
    EXPECT_EQ(hash_map_reserve(map, 20), OK);
    EXPECT_EQ(hash_map_capacity(map), 20);
    EXPECT_EQ(hash_map_reserve(map, 2), VALUE_ERROR);
}

TEST_F(NonEmptyTable, pop){
    int pop;
    EXPECT_EQ(hash_map_pop(map, "test1", &pop), OK);
    EXPECT_EQ(pop, 2);
    EXPECT_FALSE(hash_map_contains(map, "test1"));
    EXPECT_EQ(hash_map_pop(map, "test4", &pop), KEY_ERROR);
}

TEST_F(NonEmptyTable, put){
    EXPECT_EQ(hash_map_put(map, "test1", 2), KEY_ALREADY_EXISTS);
    EXPECT_EQ(hash_map_put(map, "test4", 2), OK);
    EXPECT_EQ(hash_map_contains(map, "test4"), true);
    EXPECT_EQ(hash_map_capacity(map), 8);
}






/*** Konec souboru white_box_tests.cpp ***/
