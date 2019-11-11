
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
  if (!(is_valid_pos(position))) {
    return output;
  }
  // if there is something there, set output to that
  if (this->occ[position] != nullptr) {
    *output = this->occ[position];
  }
  return output;
} 


bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
  // checks if the board position is valid
  if (!(is_valid_pos(position))) {
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
  int bcount = 0;
  int wcount = 0;
  // iterate through the board, counting
  // number of black and white kings
  for (int i = 'A', i < 'H'; i++) {
    for (int j = '1', j < '8'; j++) {
      std::pair<char, char> position (i, j);
      const Piece temp* = this(position);
      if (temp.to_ascii() == 'K') {
	wcount++;
      }
      else if (temp.to_ascii() == 'k') {
	bcount++;
      }
    }
  }
  // if there's 1 of both, return true
  if (bcount == 1 && wcount == 1) {
    return true;
  }
  return false;
}

void Board::display() const {
  // iterates through the board
  for (int i = 'A', i < 'H'; i++) {
    for (int j = '1', j < '8'; j++) {
      std::pair<char, char> position (i, j);
      const Piece temp* = this(position);
      // sets color of the board in a grid pattern
      if ( (i + j) % 2 == 0) {
	Terminal::color_bg(false, Terminal::MAGENTA);
      }
      else {
	Terminal::color_bg(true, Terminal::YELLOW);
      }
      // types nothing but background if there is no piece
      if (temp == NULL) {
	cout << " ";
      }
      else {
        char Out = toupper(temp.to_ascii());
        // if it's white use the color white
        if (temp.iswhite()) { 
  	  Terminal::color_fg(true, Terminal::WHITE);
	  cout << Out;
        }
	// if it's black use the color black
        else {
	  Terminal::color_fg(false, Terminal::BLACK);
	  cout << Out;
	}
      }
    }
    Terminal::set_default();
  }					
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

bool is_valid_pos(std::pair<char, char> position) {
  if (position.first < 'A' ||
      position.first > 'H' ||
      position.second < '1' ||
      position.second > '8') {
    return true;
  }
  else {
    return false;
  }
}
