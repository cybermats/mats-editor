#pragma once
#include "piece_table_exception.h"
#include <list>
#include <string>
#include <ostream>
#include <memory>

class piece_table_impl;

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

  size_t size();

  friend std::ostream& operator<< (std::ostream& stream, const piece_table& table);
private:
  const std::string _original;
    const std::shared_ptr<piece_table_impl> _impl;
};

piece_table piece_table_from_file(const std::string& filename);
