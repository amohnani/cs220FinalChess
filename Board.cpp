
#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

const Piece* Board::operator()(std::pair<char, char> position) const {
  // retruns a const pointer to the piece, or null ptr if there's nothing
  const Piece* output = nullptr;
  // checks if the given pair is a valid board position
  if (position.first < 'A' ||
      position.first > 'H' ||
      position.second < '1' ||
      position.second > '8') {
    return output;
  }
  
  if (this->occ[position] != nullptr) {
    *output = this->occ[position];
  }
  return output;
}


bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
  // checks if the board position is valid
  if (position.first < 'A' ||
      position.first > 'H' ||
      position.second < '1' ||
      position.second > '8') {
    return false;
  }
  // checks if the piece to be aded is valid
  char temp = tolower(piece_designator);
  if (temp != 'k' && temp != 'q' &&
      temp != 'b' && temp != 'n' &&
      temp != 'r' && temp != 'p' &&
      temp != 'm') {
    return false;
  }
  // if there is a piece there return false
  if (this(position) != nullptr) {
    return false;
  }
  // add the piece otherwise
  occ[position] = create_piece(piece_designator);
  return true;
}

bool Board::has_valid_kings() const {
  int count = 0;

  for (int i = 'A', i < 'H'; i++) {
    for (int j = '1', j < '8'; j++) {
      std::pair<i, j> position;
      char temp = this(position);
    }
  }
  
  return true;
}

void Board::display() const {
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Board& board) {
	for(char r = '8'; r >= '1'; r--) {
		for(char c = 'A'; c <= 'H'; c++) {
			const Piece* piece = board(std::pair<char, char>(c, r));
			if (piece) {
				os << piece->to_ascii();
			} else {
			  os << '-';
			}
		}
		os << std::endl;
	}
	return os;
}

