#include "Pawn.h"

using std::pair;

bool Pawn::legal_move_shape(pair<char,char> start, pair<char,char> end) const{
  if (start.first != end.first){
    return false;
  }
  if (is_white()){
    if (start.second == '2'){
      return (end.second - start.second == 2) || end.second - start.second == 1;
    }else{
      return (end.second - start.second == 1);
    }
  }else{
    if (start.second == '7'){
      return (start.second - end.second == 2) || start.second - end.second == 1;
    }else{
      return (start.second - end.second == 1);
    }
  }
}

bool Pawn::legal_capture_shape(pair<char,char> start, pair<char,char> end) const{
  if  (!(end.first - start.first == 1 || end.first - start.first == -1)){
    return false;
  }
  if (is_white()){
    return end.second - start.second == 1;
  }else{
    return start.second - end.second == 1;
  }
}
