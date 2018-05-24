//
// Created by mats on 2018-03-08.
//

#ifndef PIECE_TABLE_PIECE_TABLE_IMPL_H

#include <string>
#include <ostream>
#include <list>

class piece_table_impl {
public:
    // Sequence
    piece_table_impl(const char *buffer, size_t length);

    // Insert
    void insert(size_t position, unsigned char item);

    // Delete
    void erase(size_t position);

    // ItemAt
    short item_at(size_t);

    size_t size() const {
      return _size;
    }

    void stream_out(std::ostream &stream);

private:
    struct piece {
        piece() = default;

        piece(bool add, size_t offset, size_t length)
                : add(add), offset(offset), length(length) {}

        bool add;
        size_t offset;
        size_t length;
    };

    const char *_original;
    std::string _add;
    std::list<piece> _pieces;
    size_t _size;
};

#define PIECE_TABLE_PIECE_TABLE_IMPL_H

#endif //PIECE_TABLE_PIECE_TABLE_IMPL_H
