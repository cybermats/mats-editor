#pragma once
#include "piece_table_exception.h"
#include <list>
#include <string>
#include <ostream>

class piece_table {
public:
  // Empty
  piece_table();
  // Sequence
  piece_table(const std::string& value);
  // Insert
  void insert(size_t position, unsigned char item);
  // Delete
  void erase(size_t position);
  // ItemAt
  short item_at(size_t);

  size_t size() const {
    return _size;
  }

  friend std::ostream& operator<< (std::ostream& stream, const piece_table& table);

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
  size_t _size;
};

piece_table piece_table_from_file(const std::string& filename);
