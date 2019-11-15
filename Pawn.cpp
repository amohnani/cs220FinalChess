#include "Pawn.h"

using std::pair;

bool Pawn::legal_move_shape(pair<char,char> start, pair<char,char> end) const{
  if (start.second == 2){
    return start.first == end.first && (end.second - start.second == 2);
  }else{
    return start.first == end.first && (end.second - start.second == 1);
  }
}

bool Pawn::legal_capture_shape(pair<char,char> start, pair<char,char> end) const{
  return (end.second - start.second == 1) &&
    (end.first - start.first == 1 || end.first - start.first == -1);
}
