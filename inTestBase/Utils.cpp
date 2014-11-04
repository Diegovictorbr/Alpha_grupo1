#include "Utils.h"

bool file_exists(const char *filename) {
  std::ifstream ifile(filename);
  return ifile;
}