#include "source/piece_table.h"
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

TEST(TestInsert, SetConstructor) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.insert(0, 'a'));
}

TEST(TestDelete, EmptyConstructor) {
  piece_table pt;
  EXPECT_ANY_THROW(pt.erase(0));
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

TEST(TestFunctionality, ValueOfInsertIntoEmpty) {
  piece_table pt;
  EXPECT_NO_THROW(pt.insert(0, 'a'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), -1);
}

TEST(TestFunctionality, ValueOfInsertIntoSetBefore) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.insert(0, 'b'));
  EXPECT_EQ(pt.item_at(0), 'b');
  EXPECT_EQ(pt.item_at(1), 'a');
  EXPECT_EQ(pt.item_at(2), -1);
}

TEST(TestFunctionality, ValueOfInsertIntoSetAfter) {
  piece_table pt("a");
  EXPECT_NO_THROW(pt.insert(1, 'b'));
  EXPECT_EQ(pt.item_at(0), 'a');
  EXPECT_EQ(pt.item_at(1), 'b');
  EXPECT_EQ(pt.item_at(2), -1);
}
