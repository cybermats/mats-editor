#include "piece_table/piece_table.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "piece_table/impl/piece_table_impl.h"


// Empty
piece_table::piece_table() : _original(), _impl(new piece_table_impl(nullptr, 0)) {}
// Sequence
piece_table::piece_table(const std::string &value)
    : _original(value), _impl(new piece_table_impl(_original.c_str(), _original.size())){}
// Insert
void piece_table::insert(size_t position, unsigned char item) {
  _impl->insert(position, item);
}
// Delete
void piece_table::erase(size_t position) {
  _impl->erase(position);
}
// ItemAt
short piece_table::item_at(size_t position) {
  return _impl->item_at(position);
}

std::ostream &operator<<(std::ostream &stream, const piece_table &table) {
  table._impl->stream_out(stream);
  return stream;
}

size_t piece_table::size() {
  return _impl->size();
}

piece_table piece_table_from_file(const std::string& filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    auto size = in.tellg();
    contents.resize(size);
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return piece_table(contents);
  }
  throw piece_table_exception("Unable to open file.");
}
