#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"
#include "Terminal.h"
#include "Helper.h"

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

const Piece* Board::operator()(std::pair<char, char> position) const {
  // retruns a const pointer to the piece, or null ptr if there's nothing
  
  // checks if the given pair is a valid board position
  if (!(is_valid_pos(position))) {
    return nullptr;
  }
  // if there is something there, set output to that
  //const Piece* output = this->occ[position];

  std::map<std::pair<char, char>, Piece*> temp = this->occ;
  const Piece* output = temp[position];
  
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
  const Piece * Prior = (*this)(position);
  if (Prior != nullptr) {
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
  for (int i = 'A'; i < 'H'; i++) {
    for (int j = '1'; j < '8'; j++) {
      std::pair<char, char> position (i, j);
      const Piece * temp = (*this)(position);
      if (temp->to_ascii() == 'K') {
	wcount++;
      }
      else if (temp->to_ascii() == 'k') {
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
  for (int i = 'A'; i < 'H'; i++) {
    for (int j = '1'; j < '8'; j++) {
      std::pair<char, char> position (i, j);

      const Piece *temp = (*this)(position);
      
      // sets color of the board in a grid pattern
      if ( (i + j) % 2 == 0) {
	Terminal::color_bg(Terminal::MAGENTA);
      }
      else {
	Terminal::color_bg(Terminal::YELLOW);
      }
      // types nothing but background if there is no piece
      if (temp != nullptr) {
	std::cout << " ";
      }
      else {
        char Out = temp->to_ascii();
        // if it's white use the color white
        if (temp->is_white()) { 
  	  Terminal::color_fg(true, Terminal::WHITE);
	  std::cout << Out;
        }
	// if it's black use the color black
        else {
	  Terminal::color_fg(false, Terminal::BLACK);
	  std::cout << Out;
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
