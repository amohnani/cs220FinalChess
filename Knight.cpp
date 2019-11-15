#include "Knight.h"
#include <cstdlib>

using std::pair;

bool Knight::legal_move_shape(pair<char, char> start, pair<char,char> end) const{
  return ( (abs(start.first - end.first) == 1
	&& abs(start.second - end.second) == 2)
       || (abs(start.first - end.first) == 2
	   && abs(start.second - end.second) == 1));
}
