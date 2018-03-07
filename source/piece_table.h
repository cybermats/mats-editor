#pragma once
#include <list>
#include <string>

class piece_table {
public:
  // Empty
  piece_table();
  // Sequence
  piece_table(const std::string value);
  // Insert
  void insert(size_t position, unsigned char item);
  // Delete
  void erase(size_t position);
  // ItemAt
  short item_at(size_t);

private:
  struct piece {
    piece() {}
    piece(bool add, size_t offset, size_t length)
        : add(add), offset(offset), length(length) {}

    bool add;
    size_t offset;
    size_t length;
  };

  const std::string _original;
  std::string _add;
  std::list<piece> _pieces;
};