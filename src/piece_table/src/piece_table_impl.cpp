//
// Created by mats on 2018-03-08.
//

#include "piece_table/impl/piece_table_impl.h"
#include <fstream>
#include <vector>


// Sequence
piece_table_impl::piece_table_impl(const char *buffer, size_t length)
        : _original(buffer), _add(), _pieces({{false, 0, length}}),
          _size(length) {}

// Insert
void piece_table_impl::insert(size_t position, unsigned char item) {
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
      _pieces.emplace_back(true, _add.size(), 1);
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
  ++_size;
}

// Delete
void piece_table_impl::erase(size_t position) {
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
      --_size;
      return;
    }
    position -= it->length;
  }
  throw std::out_of_range(
          "Tries to delete outside of the size of the piece_table.");
}

// ItemAt
short piece_table_impl::item_at(size_t position) {
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

void piece_table_impl::stream_out(std::ostream &stream) {
  for (auto p : _pieces) {
    const char *buffer;
    if (p.add) {
      buffer = &_add[p.offset];
    } else {
      buffer = &_original[p.offset];
    }
    size_t len = p.length;
    stream.write(buffer, len);
  }
}
