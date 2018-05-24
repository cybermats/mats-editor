#include "piece_table/piece_table.h"
#include "piece_table/impl/piece_table_impl.h"
#include <fstream>
#include <vector>


// Empty
piece_table::piece_table() : _original(), _impl(new piece_table_impl(nullptr, 0)) {}

// Sequence
piece_table::piece_table(const std::string &value)
        : _original(value), _impl(new piece_table_impl(_original.c_str(), _original.size())) {}

// Insert
void piece_table::insert(size_t position, unsigned char item) {
  _impl->insert(position, item);
}

// Delete
void piece_table::erase(size_t position) {
  _impl->erase(position);
}

// ItemAt
short piece_table::item_at(size_t position) const {
  return _impl->item_at(position);
}

std::ostream &operator<<(std::ostream &stream, const piece_table &table) {
  table._impl->stream_out(stream);
  return stream;
}

size_t piece_table::size() const {
  return _impl->size();
}
