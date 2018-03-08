//
// Created by mats on 2018-03-08.
//

#include "piece_table/file_piece_table.h"
#include "piece_table/piece_table_exception.h"
#include "piece_table/impl/piece_table_impl.h"
#include <fstream>
#include <vector>


// Sequence
file_piece_table::file_piece_table(const char *filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, std::ios::end);
    auto size = in.tellg();
    _original.resize(size);
    in.seekg(0, std::ios::beg);
    in.read(&_original[0], _original.size());
    in.close();
    _impl = std::make_shared<piece_table_impl>(_original.c_str(), _original.size());
    return;
  }
  throw piece_table_exception("Unable to open file.");
}

// Insert
void file_piece_table::insert(size_t position, unsigned char item) {
  _impl->insert(position, item);
}
// Delete
void file_piece_table::erase(size_t position) {
  _impl->erase(position);
}
// ItemAt
short file_piece_table::item_at(size_t position) {
  return _impl->item_at(position);
}

std::ostream &operator<<(std::ostream &stream, const file_piece_table &table) {
  table._impl->stream_out(stream);
  return stream;
}

size_t file_piece_table::size() {
  return _impl->size();
}
