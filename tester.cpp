#include <iostream>
#include "Board.h"
#include "CreatePiece.h"

using std::pair;

int main(){
  Board x;
  //pair <char, char> y ('C', '4');
  pair <char, char> z ('F', '5');
  x.add_piece(z, 'r');
  pair <char, char> y ('C', '4');
  x.add_piece(y, 'R');
  
  x.display();
  return 1;
}
