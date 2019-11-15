#include "Rook.h"

using std::pair;

bool Rook::legal_move_shape(pair<char,char> start, pair<char,char> end)
  const{
  return start.first == end.first || start.second == end.second;
}
