#pragma once

#include <string>
#include <ostream>
#include <memory>
#include "pt_types.h"

class piece_table_impl;

class piece_table {
public:
    // Empty
    piece_table();

    // Sequence
    explicit piece_table(const std::string &value);

    // Insert
    void insert(size_t position, unsigned char item);

    // Delete
    void erase(size_t position);

    // ItemAt
    short item_at(size_t) const;

    size_t size() const;

    size_t row_count() const;

    size_t row_position(size_t row) const;

    ending_t ending_type() const;

    friend std::ostream &operator<<(std::ostream &stream, const piece_table &table);

private:
    const std::string _original;
    const std::shared_ptr<piece_table_impl> _impl;
};


piece_table make_from_string(const std::string &value);

piece_table make_from_file(const char *filename);