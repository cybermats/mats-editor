//
// Created by mats on 2018-03-08.
//

#ifndef PIECE_TABLE_PIECE_TABLE_IMPL_H

#include <string>
#include <ostream>
#include <list>
#include <utility>
#include <piece_table/pt_types.h>

class piece_table_impl {
public:
    // Sequence
    piece_table_impl(const char *buffer, size_t length);

    // Insert
    void insert(size_t position, unsigned char item);

    // Delete
    void erase(size_t position);

    // ItemAt
    short item_at(size_t) const;

    size_t size() const {
      return _size;
    }

    size_t row_count() const;

    size_t row_position(size_t row) const;

    ending_t ending_type() const {
      if (_endings == kUnknown || _endings == kUnix)
        return ending_t::UNIX;
      else if (_endings == kWindows)
        return ending_t::WINDOWS;
      else
        return ending_t::MIXED;
    }

    void stream_out(std::ostream &stream);

private:
    struct piece {
//        piece() {}

        piece(bool add, size_t offset, size_t length, std::list<size_t> endings = std::list<size_t>())
                : add(add), offset(offset), length(length), endings(std::move(endings)) {}

        bool add;
        size_t offset;
        size_t length;
        std::list<size_t> endings;
    };

    enum line_ending_type {
        kUnknown,
        kWindows,
        kUnix,
        kMixed
    };

    const char *_original;
    std::string _add;
    std::list<piece> _pieces;
    size_t _size;
    size_t _row_count = 1;
    line_ending_type _endings = kUnknown;

};

#define PIECE_TABLE_PIECE_TABLE_IMPL_H

#endif //PIECE_TABLE_PIECE_TABLE_IMPL_H
