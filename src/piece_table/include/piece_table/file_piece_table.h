//
// Created by mats on 2018-03-08.
//

#ifndef PIECE_TABLE_FILE_PIECE_TABLE_H
#define PIECE_TABLE_FILE_PIECE_TABLE_H

#include <string>
#include <ostream>
#include <memory>

class piece_table_impl;

class file_piece_table {
public:
    // Sequence
    explicit file_piece_table(const char *filename);

    // Insert
    void insert(size_t position, unsigned char item);

    // Delete
    void erase(size_t position);

    // ItemAt
    short item_at(size_t);

    size_t size();

    friend std::ostream &operator<<(std::ostream &stream, const file_piece_table &table);

private:
    std::string _original;
    std::shared_ptr<piece_table_impl> _impl;
};

#endif //PIECE_TABLE_FILE_PIECE_TABLE_H
