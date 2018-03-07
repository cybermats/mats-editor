#include "piece_table.h"
#include <stdexcept>
#include <vector>

// Empty
piece_table::piece_table() : _original(), _add(), _pieces() {}
// Sequence
piece_table::piece_table(const std::string value)
    : _original(value), _add(), _pieces({{false, 0, value.size()}}) {}
// Insert
void piece_table::insert(size_t position, unsigned char item) {
  auto added = _pieces.end();

  for (auto it = _pieces.begin(); it != _pieces.end(); ++it) {
    if (position < it->length) {
      if (position > 0) {
        // we are in the middle of a segment so need to split it up in two.
        _pieces.emplace(it, it->add, it->offset, position);
        it->offset += position;
        it->length -= position;
      }
      added = _pieces.emplace(it, true, _add.size(), 1);
      _add.push_back(item);
      break;
    }
    position -= it->length;
  }

  if (added == _pieces.end()) {
    // handle the situation where we insert something at the end of the total
    // range
    if (position == 0) {
      _pieces.push_back({true, _add.size(), 1});
      added = std::prev(_pieces.end());
      _add.push_back(item);
    }
  }

  if (added == _pieces.end()) {
    throw std::out_of_range(
        "Tries to insert outside of the size of the piece_table.");
  } else {
    // See if we can optimize this insert.
    if (added != _pieces.begin()) {
      auto p = std::prev(added);
      if (p->add && (p->offset + p->length == added->offset)) {
        p->length += 1;
        _pieces.erase(added);
        added = _pieces.end();
      }
    }
  }
}
// Delete
void piece_table::erase(size_t position) {
  for (auto it = _pieces.begin(); it != _pieces.end(); ++it) {
    if (position < it->length) {
      // We're at the end of a segment. May just shrink the size
      if (position == it->length - 1) {
        it->length -= 1;
      } else if (position == 0) {
        it->offset += 1;
        it->length -= 1;
      } else {
        _pieces.emplace(it, it->add, it->offset, position);
        it->offset += (position + 1);
        it->length -= (position + 1);
      }
      return;
    }
    position -= it->length;
  }
  throw std::out_of_range(
      "Tries to delete outside of the size of the piece_table.");
}
// ItemAt
short piece_table::item_at(size_t position) {
  for (auto it : _pieces) {
    if (position < it.length) {
      if (it.add) {
        return _add[it.offset + position];
      } else {
        return _original[it.offset + position];
      }
    }
    position -= it.length;
  }
  return -1;
}
