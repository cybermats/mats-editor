//
// Created by mats on 2018-05-24.
//


#include "piece_table/piece_table.h"
#include "gtest/gtest.h"


TEST(TestRows, Empty) {
  piece_table pt("");
  EXPECT_EQ(pt.row_count(), 1);
  EXPECT_EQ(pt.row_position(0), 0);
}

TEST(TestRowsCounter, OneRow) {
  piece_table pt("abc");
  EXPECT_EQ(pt.row_count(), 1);
  EXPECT_EQ(pt.row_position(0), 0);
}

TEST(TestRowsCounter, OneRowEndingNewline) {
  piece_table pt("abc\n");
  EXPECT_EQ(pt.row_count(), 2);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
}

TEST(TestRowsCounter, TwoRowsUnix) {
  piece_table pt("abc\ndef");
  EXPECT_EQ(pt.row_count(), 2);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
}

TEST(TestRowsCounter, TwoRowsWindows) {
  piece_table pt("abc\r\ndef");
  EXPECT_EQ(pt.row_count(), 2);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 5);
}

TEST(TestRowsCounter, ThreeRowsUnix) {
  piece_table pt("abc\ndef\nghi");
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 8);
}

TEST(TestRowsCounter, ThreeRowsWindows) {
  piece_table pt("abc\r\ndef\r\nghi");
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 5);
  EXPECT_EQ(pt.row_position(2), 10);
}

TEST(TestRowsCounter, ThreeRowsMixed) {
  piece_table pt("abc\ndef\r\nghi");
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 9);
}

TEST(TestRowsEdit, InsertChar) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(1, 'a');
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 5);
  EXPECT_EQ(pt.row_position(2), 9);
}

TEST(TestRowsEdit, InsertCharEnd) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(11, 'a');
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 8);
}

TEST(TestRowsEdit, InsertCharEndAfterNewLine) {
  piece_table pt("abc\ndef\nghi\n");
  pt.insert(12, 'a');
  EXPECT_EQ(pt.row_count(), 4);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 8);
  EXPECT_EQ(pt.row_position(3), 12);
}

TEST(TestRowsEdit, InsertNewLineFirst) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(0, '\n');
  EXPECT_EQ(pt.row_count(), 4);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 1);
  EXPECT_EQ(pt.row_position(2), 5);
  EXPECT_EQ(pt.row_position(3), 9);
}


TEST(TestRowsEdit, InsertNewLineMiddleMiddle) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(1, '\n');
  EXPECT_EQ(pt.row_count(), 4);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 2);
  EXPECT_EQ(pt.row_position(2), 5);
  EXPECT_EQ(pt.row_position(3), 9);
}

TEST(TestRowsEdit, InsertNewLineMiddleEnd) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(3, '\n');
  EXPECT_EQ(pt.row_count(), 4);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 5);
  EXPECT_EQ(pt.row_position(3), 9);
}

TEST(TestRowsEdit, InsertNewLineLast) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(11, '\n');
  EXPECT_EQ(pt.row_count(), 4);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 8);
  EXPECT_EQ(pt.row_position(3), 12);
}

TEST(TestRowsEdit, EraseCharBegin) {
  piece_table pt("abc\ndef\nghi");
  pt.erase(0);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 3);
  EXPECT_EQ(pt.row_position(2), 7);
}

TEST(TestRowsEdit, EraseCharMiddleMiddle) {
  piece_table pt("abc\ndef\nghi");
  pt.erase(5);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 7);
}

TEST(TestRowsEdit, EraseCharMiddleStart) {
  piece_table pt("abc\ndef\nghi");
  pt.erase(4);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 7);
}

TEST(TestRowsEdit, EraseCharEnd) {
  piece_table pt("abc\ndef\nghi");
  pt.erase(10);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 8);
}

TEST(TestRowsEdit, EraseNewlineBegin) {
  piece_table pt("\nabc\ndef\n");
  pt.erase(0);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 4);
  EXPECT_EQ(pt.row_position(2), 8);
}

TEST(TestRowsEdit, EraseNewlineMiddle) {
  piece_table pt("\nabc\ndef\n");
  pt.erase(4);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 1);
  EXPECT_EQ(pt.row_position(2), 8);
}

TEST(TestRowsEdit, EraseNewlineEnd) {
  piece_table pt("\nabc\ndef\n");
  pt.erase(8);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 1);
  EXPECT_EQ(pt.row_position(2), 5);
}

TEST(TestRowEndTypes, BasicEmpty) {
  piece_table pt("abc");
  EXPECT_EQ(pt.ending_type(), ending_t::UNIX);
}

TEST(TestRowEndTypes, BasicUnix) {
  piece_table pt("abc\ndef\nghi");
  EXPECT_EQ(pt.ending_type(), ending_t::UNIX);
}

TEST(TestRowEndTypes, BasicWindows) {
  piece_table pt("abc\r\ndef\r\nghi");
  EXPECT_EQ(pt.ending_type(), ending_t::WINDOWS);
}

TEST(TestRowEndTypes, BasicMixedOne) {
  piece_table pt("abc\ndef\r\nghi");
  EXPECT_EQ(pt.ending_type(), ending_t::MIXED);
}

TEST(TestRowEndTypes, BasicMixedTwo) {
  piece_table pt("abc\r\ndef\nghi");
  EXPECT_EQ(pt.ending_type(), ending_t::MIXED);
}

TEST(TestRowEndTypes, BasicMixedThree) {
  piece_table pt("abc\r\ndef\nghi\r\njkl");
  EXPECT_EQ(pt.ending_type(), ending_t::MIXED);
}

TEST(TestRowEndTypes, BasicMixedFour) {
  piece_table pt("abc\r\ndef\nghi\njkl");
  EXPECT_EQ(pt.ending_type(), ending_t::MIXED);
}


TEST(TestRowEndTypes, InsertUnixEmpty) {
  piece_table pt("abc");
  pt.insert(3, '\n');
  EXPECT_EQ(pt.ending_type(), ending_t::UNIX);
}

TEST(TestRowEndTypes, InsertWindowsEmpty) {
  piece_table pt("abc");
  pt.insert(3, '\r');
  pt.insert(4, '\n');
  EXPECT_EQ(pt.ending_type(), ending_t::WINDOWS);
}

TEST(TestRowEndTypes, InsertUnixIntoUnix) {
  piece_table pt("ab\n");
  pt.insert(3, '\n');
  EXPECT_EQ(pt.ending_type(), ending_t::UNIX);
}


TEST(TestRowEndTypes, InsertWindowsIntoUnix) {
  piece_table pt("ab\n");
  pt.insert(3, '\r');
  pt.insert(4, '\n');
  EXPECT_EQ(pt.ending_type(), ending_t::MIXED);
}

TEST(TestRowEndTypes, InsertUnixIntoWindows) {
  piece_table pt("a\r\n");
  pt.insert(3, '\n');
  EXPECT_EQ(pt.ending_type(), ending_t::MIXED);
}


TEST(TestRowEndTypes, InsertWindowsIntoWindows) {
  piece_table pt("a\r\n");
  pt.insert(3, '\r');
  pt.insert(4, '\n');
  EXPECT_EQ(pt.ending_type(), ending_t::WINDOWS);
}


TEST(TestRowsAdvancedEdit, InsertErase) {
  piece_table pt("abc\ndef\nghi");
  pt.insert(1, 'd');
  pt.erase(6);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 5);
  EXPECT_EQ(pt.row_position(2), 8);
}

TEST(TestRowsAdvancedEdit, InsertEraseNewLines) {
  piece_table pt("abc\ndef\nghi");
  pt.erase(7);
  pt.insert(1, '\n');
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 2);
  EXPECT_EQ(pt.row_position(2), 5);
}

TEST(TestRowsAdvancedEdit, InsertAll) {
  piece_table pt("");
  pt.insert(0, '\n');
  pt.insert(0, 'a');
  pt.insert(0, '\n');
  pt.insert(0, 'b');
  pt.insert(0, '\n');
  EXPECT_EQ(pt.row_count(), 4);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 1);
  EXPECT_EQ(pt.row_position(2), 3);
  EXPECT_EQ(pt.row_position(3), 5);
}

TEST(TestRowsAdvancedEdit, InsertAllEraseNewLine) {
  piece_table pt("");
  pt.insert(0, '\n');
  pt.insert(0, 'a');
  pt.insert(0, '\n');
  pt.insert(0, 'b');
  pt.insert(0, '\n');
  pt.erase(2);
  EXPECT_EQ(pt.row_count(), 3);
  EXPECT_EQ(pt.row_position(0), 0);
  EXPECT_EQ(pt.row_position(1), 1);
  EXPECT_EQ(pt.row_position(2), 4);
}

