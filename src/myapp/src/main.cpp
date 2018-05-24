#include "piece_table/large_file_piece_table.h"
#include <iostream>

int main() {
  const char *filename = "LICENSE";

  large_file_piece_table pt(filename);
  std::cout << pt << std::endl;
  return 0;
}