#include "piece_table/piece_table.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(TestConstructors, EmptyConstructor) { EXPECT_NO_THROW(piece_table pt); }

TEST(TestConstructors, SetConstructor) { EXPECT_NO_THROW(piece_table pt("a")); }

TEST(TestItemAt, EmptyConstructor) {
  piece_table pt;
  EXPECT_NO_THROW(pt.item_at(0));
}

TEST(TestItemAt, SetConstructor) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.item_at(0));
  EXPECT_NO_THROW(pt.item_at(1));
}

TEST(TestInsert, EmptyConstructor) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'a'));
}

TEST(TestInsert, InvalidInsert) {
  piece_table pt;
  EXPECT_THROW(pt.insert(1, 'a'), std::out_of_range);
}

TEST(TestInsert, SetConstructor) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.insert(0, 'a'));
}

TEST(TestDelete, InvalidDelete) {
  piece_table pt;
  EXPECT_THROW(pt.erase(0), std::out_of_range);
}

TEST(TestDelete, SetConstructor) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.erase(0));
}

TEST(TestFunctionality, ValueOfEmpty) {
  piece_table pt;
  EXPECT_EQ(pt.item_at(0), -1);
}

TEST(TestFunctionality, ValueOfSet) {
  piece_table pt("a");
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), -1);
}

TEST(TestFunctionality, InsertIntoEmpty) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'a'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), -1);
}

TEST(TestFunctionality, InsertIntoEmptyBefore) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'a'));
  EXPECT_NO_THROW(pt.insert(0, 'b'));
  EXPECT_EQ(pt.item_at(0), 'b');
  EXPECT_EQ(pt.item_at(1), 'a');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, InsertIntoEmptyAfter) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'a'));
  EXPECT_NO_THROW(pt.insert(1, 'b'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, InsertIntoSetBefore) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(0, 'x'));
  EXPECT_EQ(pt.item_at(0), 'x');
  EXPECT_EQ(pt.item_at(1), 'a');
  EXPECT_EQ(pt.item_at(2), 'b');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestFunctionality, InsertIntoSetMiddle) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(1, 'x'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'x');
  EXPECT_EQ(pt.item_at(2), 'b');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestFunctionality, InsertIntoSetAfter) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(2, 'x'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), 'x');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestFunctionality, InsertThenDelete) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'a'));
  EXPECT_NO_THROW(pt.erase(0));
  EXPECT_EQ(pt.item_at(0), -1);
}

TEST(TestFunctionality, DeleteThenInsert) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.erase(0));
  EXPECT_NO_THROW(pt.insert(0, 'x'));
  EXPECT_EQ(pt.item_at(0), 'x');
  EXPECT_EQ(pt.item_at(1), -1);
}

TEST(TestFunctionality, DeleteIntoSetBefore) {
  piece_table pt("abc");
  EXPECT_NO_THROW(pt.erase(0));
  EXPECT_EQ(pt.item_at(0), 'b');
  EXPECT_EQ(pt.item_at(1), 'c');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, DeleteIntoSetMiddle) {
  piece_table pt("abc");
  EXPECT_NO_THROW(pt.erase(1));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'c');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, DeleteIntoSetAfter) {
  piece_table pt("abc");
  EXPECT_NO_THROW(pt.erase(2));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, InsertThenDeleteBefore) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(1, 'x'));
  EXPECT_NO_THROW(pt.erase(0));
  EXPECT_EQ(pt.item_at(0), 'x');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, InsertThenDeleteMiddle) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(1, 'x'));
  EXPECT_NO_THROW(pt.erase(1));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, InsertThenDeleteAfter) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(1, 'x'));
  EXPECT_NO_THROW(pt.erase(2));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'x');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, DeleteThenInsertBefore) {
  piece_table pt("abc");
  EXPECT_NO_THROW(pt.erase(1));
  EXPECT_NO_THROW(pt.insert(0, 'x'));
  EXPECT_EQ(pt.item_at(0), 'x');
  EXPECT_EQ(pt.item_at(1), 'a');
  EXPECT_EQ(pt.item_at(2), 'c');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestFunctionality, DeleteThenInsertMiddle) {
  piece_table pt("abc");
  EXPECT_NO_THROW(pt.erase(1));
  EXPECT_NO_THROW(pt.insert(1, 'x'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'x');
  EXPECT_EQ(pt.item_at(2), 'c');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestFunctionality, DeleteThenInsertAfter) {
  piece_table pt("abc");
  EXPECT_NO_THROW(pt.erase(1));
  EXPECT_NO_THROW(pt.insert(2, 'x'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'c');
  EXPECT_EQ(pt.item_at(2), 'x');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestAdvancedFunctionality, ManyInsertsFromEmpty) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'x'));
  EXPECT_NO_THROW(pt.insert(1, 'y'));
  EXPECT_NO_THROW(pt.insert(2, 'z'));
  EXPECT_EQ(pt.item_at(0), 'x');
  EXPECT_EQ(pt.item_at(1), 'y');
  EXPECT_EQ(pt.item_at(2), 'z');
  EXPECT_EQ(pt.item_at(3), -1);
}

TEST(TestAdvancedFunctionality, ManyInsertsFromSetBefore) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(0, 'x'));
  EXPECT_NO_THROW(pt.insert(1, 'y'));
  EXPECT_EQ(pt.item_at(0), 'x');
  EXPECT_EQ(pt.item_at(1), 'y');
  EXPECT_EQ(pt.item_at(2), 'a');
  EXPECT_EQ(pt.item_at(3), 'b');
  EXPECT_EQ(pt.item_at(4), -1);
}

TEST(TestAdvancedFunctionality, ManyInsertsFromSetMiddle) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(1, 'x'));
  EXPECT_NO_THROW(pt.insert(2, 'y'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'x');
  EXPECT_EQ(pt.item_at(2), 'y');
  EXPECT_EQ(pt.item_at(3), 'b');
  EXPECT_EQ(pt.item_at(4), -1);
}

TEST(TestAdvancedFunctionality, ManyInsertsFromSetAfter) {
  piece_table pt("ab");
  EXPECT_NO_THROW(pt.insert(2, 'x'));
  EXPECT_NO_THROW(pt.insert(3, 'y'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), 'x');
  EXPECT_EQ(pt.item_at(3), 'y');
  EXPECT_EQ(pt.item_at(4), -1);
}

TEST(TestSize, Empty) {
  piece_table pt;
  EXPECT_EQ(pt.size(), 0);
}

TEST(TestSize, Set) {
  piece_table pt("abc");
  EXPECT_EQ(pt.size(), 3);
}

TEST(TestSize, EmptyInsert) {
  piece_table pt;
  pt.insert(0, 'a');
  EXPECT_EQ(pt.size(), 1);
}

TEST(TestSize, SetInsert) {
  piece_table pt("abc");
  pt.insert(0, 'x');
  EXPECT_EQ(pt.size(), 4);
}

TEST(TestSize, SetDelete) {
  piece_table pt("abc");
  pt.erase(0);
  EXPECT_EQ(pt.size(), 2);
}
