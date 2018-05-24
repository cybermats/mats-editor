//
// Created by mats on 2018-03-08.
//

//
// Created by mats on 2018-03-08.
//

#include "piece_table/large_file_piece_table.h"
#include "piece_table/impl/piece_table_impl.h"
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

// Sequence
large_file_piece_table::large_file_piece_table(const char *filename) {
  auto file_size = boost::filesystem::file_size(filename);
  _file = boost::interprocess::file_mapping(filename, boost::interprocess::read_only);
  _region = boost::interprocess::mapped_region(_file, boost::interprocess::read_only, 0, file_size);
  _impl = std::make_shared<piece_table_impl>((char *) _region.get_address(), _region.get_size());
}

// Insert
void large_file_piece_table::insert(size_t position, unsigned char item) {
  _impl->insert(position, item);
}

// Delete
void large_file_piece_table::erase(size_t position) {
  _impl->erase(position);
}

// ItemAt
short large_file_piece_table::item_at(size_t position) {
  return _impl->item_at(position);
}

std::ostream &operator<<(std::ostream &stream, const large_file_piece_table &table) {
  table._impl->stream_out(stream);
  return stream;
}

size_t large_file_piece_table::size() {
  return _impl->size();
}
