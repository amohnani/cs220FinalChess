#include "Chess.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::pair;
/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess() : is_white_turn(true) {
	// Add the pawns
	for (int i = 0; i < 8; i++) {
		board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
		board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
	}

	// Add the rooks
	board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
	board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
	board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
	board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

	// Add the knights
	board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
	board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
	board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
	board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

	// Add the bishops
	board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
	board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
	board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
	board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

	// Add the kings and queens
	board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
	board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
	board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
	board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
}

bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end) {
  
  // checks start and end are valid
  if (!(is_valid_pos(start) && is_valid_pos(end))) {
    std::cout << "Invalid start or end positions" << std::endl; 
    return false;
  }
  
  // stores the piece on start to toMove
  const Piece * toMove = (this->board)(start);

  // checks that there is a piece there
  if (toMove == nullptr) {
    std::cout << "There is not a piece there" << endl;
    return false;
  }
  
  // stores the piece type in a char
  char type = toMove->to_ascii();
  
  // checks that the piece is on the same side as the player
  if (toMove->is_white() != this->is_white_turn) {
    std::cout << "The piece you moved is not the right color" << std::endl;
    return false;
  }
  // checks if a move is being made
  if (start == end) {
    cout << "The piece has to be moved" << endl;
    return false;
  }

  // checks whether there's a piece in between when the
  // piece moves horizontally, vertically, or diagonally
  char path1;
  char path2;
  // checks for vertical movement
  if (start.first - end.first == 0) {
    // iterates through the vertical path
    for (int i = (start.second-end.second)/abs(start.second-end.second);
         abs(i) < abs(start.second - end.second);
         i += (start.second-end.second)/abs(start.second-end.second)) {
      path1 = start.first;
      path2 = end.second + i;
      pair<char, char> posBt (path1, path2);
      const Piece* bt = (this->board)(posBt);
      // if there's a piece thats not a nullptr, error
      if (bt != nullptr) {
        cout << "there's a piece inbetween" << endl;
        return false;
      }
    }
  }

  // check for travelling horizontally
  else if (start.second - end.second == 0) {
    // iterates through the horizontal path
    for (int i = (start.second-end.second)/abs(start.second-end.second);
       abs(i) < abs(start.first - end.first);
       i += (start.first - end.first)/abs(start.first - end.first)) {
    path1 = end.first + i;
    path2 = start.second;
    pair <char, char> posBt (path1, path2);
    const Piece *bt = (this->board)(posBt);
    if (bt != nullptr) {
      cout << "there's a piece inbetween" << endl;
      return false;
    }
   }
  }
  else if (abs(start.second-end.second) == abs(start.first-end.first)) {
    // iterates through the diagonal path
    for (int i = (end.first - start.first)/abs(end.first - start.first);
         abs(i) < abs(end.first-start.first);
         i += (end.first - start.first)/abs(end.first - start.first)) {
      int j = abs(i) * (end.second-start.second)/abs(end.second-start.second);
      path1 = start.first + i;
      path2 = start.second + j;
      pair <char, char> posBt (path1, path2);
      const Piece *bt = (this->board)(posBt);
      if (bt != nullptr) {
        cout << "there's a piece inbetween" << endl;
        return false;
      }
    }
  }


  // checks if there is a piece on end, and then checks legal
  // move shape or legal capture shape in accordance
  const Piece * target = (this->board)(end);
  // for the case that there is nothing at the end
  if (target == nullptr) {
    // checks if the move shape is valid
    if (!(toMove->legal_move_shape(start, end))) {
      cout << "Not a valid move for the piece" << endl;
      return false;
    }
    // adds the piece if it is valid
    board.add_piece(end, type);
    board.delete_piece(start);
    this->is_white_turn = !(this->is_white_turn);
  }
  else {
    // checks if the capture shape is valid
    if (target->is_white() == this->turn_white()) {
      cout << "you can't capture your own piece" << endl;
      return false;
    }
    if (!(toMove->legal_capture_shape(start, end))) {
      cout << "can't move to capture this way" << endl;
      return false;
    }
    else {
      // moves the piece and removes the captured piece
      board.delete_piece(start);
      board.delete_piece(end);
      board.add_piece(end, type);
      this->is_white_turn = !(this->is_white_turn);
    }
  }
  // checks if a pawn should be promoted
  if (type == 'P' && end.second == '8') {
    board.delete_piece(end);
    board.add_piece(end, 'Q');
  }
  else if (type == 'p' && end.second == '1') {
    board.delete_piece(end);
    board.add_piece(end, 'q');
  }
  // checks if the move would result in a check
  if (in_check(this->is_white_turn)) {
    // reverts the move if so
    board.delete_piece(end);
    if (!(target == nullptr)) {
      board.add_piece(end, target->to_ascii());
    }
    board.add_piece(start, type);
    cout << "if you make this move, you would be in check" << endl;
    return false;
  }
  
  return true;
}


bool Chess::in_check(bool white) const {
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return false;
}


bool Chess::in_mate(bool white) const {
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return false;
}


bool Chess::in_stalemate(bool white) const {
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return false;
}


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<< (std::ostream& os, const Chess& chess) {
	// Write the board out and then either the character 'w' or the character 'b',
	// depending on whose turn it is
	return os << chess.get_board() << (chess.turn_white() ? 'w' : 'b');
}


std::istream& operator>> (std::istream& is, Chess& chess) {
  char temp;
  Board board;
  
  for (int i = '8'; i >= '1'; i--){
    for (int j = 'A'; j <= 'H'; j++){
      is >> temp;
      if (temp != '-'){
        std::pair<char,char> pos(j,i);
        board.add_piece(pos, temp);
      }
    }
  }
  is >> temp;
  chess.set_turn(temp);
  chess.set_board(&board);
  return is;
}

bool Chess::set_turn(char color) {
  
  if (color != 'b' ||
      color != 'w') {
    return false;
  }
  else if (color == 'b') {
    this->is_white_turn = false;
    return true;
  }
  else {
    this->is_white_turn = true;
    return true;
  }
}

void Chess::set_board(Board *b){
  board.clear_board();
  board = *b;
}
