#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "node.h"

using namespace std;

int hashID(int id, int size) {
  return id % size;
}
