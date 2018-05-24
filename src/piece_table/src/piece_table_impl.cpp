//
// Created by mats on 2018-03-08.
//

#include "piece_table/impl/piece_table_impl.h"
#include <fstream>
#include <vector>
#include <cassert>


// Sequence
piece_table_impl::piece_table_impl(const char *buffer, size_t length)
        : _original(buffer), _add(),
          _size(length) {
  auto p = piece(false, 0, length, {});
  if (_size == 0)
    return;
  if (_original[0] == '\n') {
    _endings = kUnix;
    p.endings.push_back(1);
  }

  for (size_t i = 1; i < _size; ++i) {
    if (_original[i] == '\n') {
      auto ending = kUnix;
      if (_original[i - 1] == '\r') {
        ending = kWindows;
      }
      if (_endings == kUnknown)
        _endings = ending;
      else if (_endings != kMixed) {
        if (_endings != ending)
          _endings = kMixed;
      }
      p.endings.push_back(i + 1);
    }
  }
  //  p.endings.push_back(_size);
  _row_count = p.endings.size() + 1;
  _pieces.push_back(p);
}

// Insert
void piece_table_impl::insert(size_t position, unsigned char item) {
  auto added = _pieces.end();
  bool linebreak = false;
  if (item == '\n') {
    linebreak = true;
    auto ending = kUnix;
    if (position > 0) {
      auto prev_char = item_at(position - 1);
      if (prev_char == '\r')
        ending = kWindows;
    }
    if (_endings == kUnknown)
      _endings = ending;
    else if (_endings != kMixed) {
      if (_endings != ending) {
        _endings = kMixed;
      }
    }
  }

  for (auto it = _pieces.begin(); it != _pieces.end(); ++it) {
    if (position < it->length) {
      if (position > 0) {
        // we are in the middle of a segment so need to split it up in two.
        auto split = _pieces.emplace(it, it->add, it->offset, position);
        it->offset += position;
        it->length -= position;
        auto e_last = it->endings.begin();
        for (; e_last != it->endings.end(); ++e_last) {
          if (*e_last >= it->offset) {
            break;
          }
        }
        split->endings.splice(split->endings.begin(), it->endings, it->endings.begin(), e_last);
      }

      added = _pieces.emplace(it, true, _add.size(), 1);
      if (linebreak) {
        it->endings.push_front(it->offset);
        _row_count++;
      }
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
      if (linebreak) {
        added->endings.push_back(_add.size());
        _row_count++;
      }
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
      bool linebreak;
      if (it->add) {
        linebreak = (_add[it->offset + position] == '\n');
      } else {
        linebreak = (_original[it->offset + position] == '\n');
      }

      if (position == it->length - 1) {
        it->length -= 1;
        if (linebreak) {
          auto next = std::next(it);
          if (next == _pieces.end()) {
            assert(it->endings.back() == it->offset + it->length + 1);
            it->endings.pop_back();
          } else {
            assert(next->endings.front() == next->offset);
            next->endings.pop_front();
          }
          _row_count--;
        }
      } else if (position == 0) {
        it->offset += 1;
        it->length -= 1;
        if (linebreak) {
          assert(it->endings.front() == it->offset);
          it->endings.pop_front();
          _row_count--;
        }
      } else {
        auto prev = _pieces.emplace(it, it->add, it->offset, position);
        it->offset += (position + 1);
        it->length -= (position + 1);
        auto e_last = it->endings.begin();
        for (; e_last != it->endings.end(); ++e_last) {
          if (*e_last >= it->offset)
            break;
        }
        prev->endings.splice(prev->endings.begin(), it->endings, it->endings.begin(), e_last);

        if (linebreak) {
          assert(it->endings.front() == it->offset);
          it->endings.pop_front();
          _row_count--;
        }
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
short piece_table_impl::item_at(size_t position) const {
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

size_t piece_table_impl::row_count() const {
  return _row_count;
}

size_t piece_table_impl::row_position(size_t row) const {
  if (row == 0)
    return 0;
  assert(row < _row_count);
  size_t row_count = 0;
  size_t position = 0;
  for (auto p: _pieces) {
    for (auto e: p.endings) {
      assert(e >= p.offset);
      assert(e <= (p.offset + p.length));
      row_count++;
      if (row_count == row) {
        auto internal_offset = e - p.offset;
        return position + internal_offset;
      }
    }
    position += p.length;

  }
  return 0;
}
