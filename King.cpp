#include "King.h"
#include <cstdlib>

using std::pair;

bool King::legal_move_shape(pair<char,char> start, pair<char,char> end) const{
  return abs(start.first - end.first) <= 1
    && abs(start.second - end.second) <= 1;
}
