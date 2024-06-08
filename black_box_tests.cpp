//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Matus Lengvarsky
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class empty :public::testing::Test
{
protected:
    BinaryTree tree;

};

class nonempty :public::testing::Test
{
protected:
    virtual void SetUp(){
    for(int i = 0; i < 20; i++)
    {
        tree.InsertNode(i);
    }
    }
    BinaryTree tree;
};

class treeaxioms :public::testing::Test
{
protected:
    virtual void SetUp(){
    for(int i = 0; i < 20; i++)
    {
        tree.InsertNode(i);
    }
    }
    BinaryTree tree;
};

TEST_F(empty, InsertNode){
    auto insert = tree.InsertNode(5);
    EXPECT_TRUE(insert.first);
    EXPECT_EQ(insert.second->key, 5);

    auto insert2 = tree.InsertNode(5);
    EXPECT_FALSE(insert2.first);
    EXPECT_EQ(insert2.second, insert2.second); 
};

TEST_F(empty, DeleteNode){
    auto deletenode = tree.DeleteNode(5);
    EXPECT_FALSE(deletenode);

    auto deletenode2 = tree.DeleteNode(1);
    EXPECT_FALSE(deletenode2);
};

TEST_F(empty, FindNode){
    auto find = tree.FindNode(5);
    EXPECT_EQ(find, nullptr);

    auto find2 = tree.FindNode(1);
    EXPECT_EQ(find2, nullptr);
};

TEST_F(nonempty, InsertNode){
    auto insert = tree.InsertNode(4);
    EXPECT_FALSE(insert.first);
    auto ptr = tree.FindNode(4); 
    EXPECT_EQ(insert.second, ptr);
};

TEST_F(nonempty, DeleteNode){
    EXPECT_TRUE(tree.DeleteNode(4));
    EXPECT_FALSE(tree.DeleteNode(32));
};

TEST_F(nonempty, FindNode){
    EXPECT_NE(tree.FindNode(4), nullptr);
    EXPECT_EQ(tree.FindNode(32), nullptr);
};

TEST_F(treeaxioms, Axiom1){
    std::vector<Node_t *> leafs{};
    tree.GetLeafNodes(leafs);
    for (auto leaf : leafs)
    {
        EXPECT_EQ(leaf->color, BLACK);
    }
}

TEST_F(treeaxioms, Axiom2){
    std::vector<Node_t *> nodes{};
    tree.GetAllNodes(nodes);
    for (auto node : nodes) 
    {
        if (node->color == RED)
        {
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);            

        }
    }
}
/*** Konec souboru black_box_tests.cpp ***/
