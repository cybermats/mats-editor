#pragma once
#include <stdexcept>

class piece_table_exception : public std::runtime_error {
public:
  explicit piece_table_exception(const std::string &what_arg)
      : std::runtime_error(what_arg) {}
  explicit piece_table_exception(const char *what_arg)
      : std::runtime_error(what_arg) {}
};