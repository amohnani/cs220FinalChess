#include <iostream>
#include "Board.h"
#include "CreatePiece.h"

using std::pair;

int main(){
  Board x;
  pair <char, char> y ('c', '4');
  x.add_piece(y, 'K');
  x.display();
  return 0;
}
