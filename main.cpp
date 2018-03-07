#include "source/piece_table.h"
#include <iostream>

int main() {
  piece_table pt("ab");
  pt.erase(1);

  piece_table pta("ab");
  pta.insert(1, 'x');
  pta.erase(1);

  return 0;
}