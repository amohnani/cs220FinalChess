#include "Chess.h"
#include <iostream>
#include <cmath>
#include <sstream>
//#incdlue <iostream>

using std::stringstream;
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
    return false;
  }
  // checks if there is a piece on end, and then checks legal
  // move shape or legal capture shape in accordance
  const Piece * target = (this->board)(end);
  char targetType;
  const Piece * toMove = (this->board)(start);
  if (toMove == nullptr) {
    return false;
  }
  if (toMove->is_white() != is_white_turn) {
    return false;
  }
  
  char type = toMove->to_ascii();
  // for the case that there is nothing at the end
  if (target == nullptr) {
    if (!(is_valid_move(start, end, false))) {
      return false;
    }
    // adds the piece if it is valid
    board.add_piece(end, type);
    board.delete_piece(start);
  }
  else {
    targetType = target->to_ascii();
    if (!(is_valid_move(start, end, true))) {
      return false;
    }
    // moves the piece and removes the captured piece
    board.delete_piece(start);
    board.delete_piece(end);
    board.add_piece(end, type);
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
  if (in_check((this->is_white_turn))) {
    // reverts the move if so
    board.delete_piece(end);
    if (target != nullptr) {
      board.add_piece(end, targetType);
    }
    board.add_piece(start, type);
    return false;
  }
  is_white_turn = !is_white_turn;
  return true;
}

// checks whether the move is valid
// pre-condition: start and end must by valid **
bool Chess::is_valid_move(std::pair<char, char> start, std::pair<char, char> end, bool to_capture) const{
  // stores the piece on start to toMove
  // and the piece on end to toTarget
  const Piece * toMove = (this->board)(start);
  const Piece * toTarget = (this->board)(end);
  // checks that there is a piece there
  if (toMove == nullptr) {
    return false;
  }

  // checks that the piece is on the same side as the player
  //if (toMove->is_white() != white) {
  //  return false;
  // }
  // checks if a move is being made
  if (start == end) {
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
	return false;
      }
    }
  }
  // check for travelling horizontally
  else if (start.second - end.second == 0) {
    // iterates through the horizontal path
    for (int i = (start.first-end.first)/abs(start.first-end.first);
	 abs(i) < abs(start.first - end.first);
	 i += (start.first - end.first)/abs(start.first - end.first)) {
      path1 = end.first + i;
      path2 = start.second;
      pair <char, char> posBt (path1, path2);
      const Piece *bt = (this->board)(posBt);
      if (bt != nullptr) {
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
	return false;
	
      }
    }
  }

  if (to_capture) {
    if (!(toMove->legal_capture_shape(start, end))) {
      return false;
    }
    if (toTarget == nullptr) {
      return false;
    }
    if (toTarget->is_white() == toMove->is_white()) {
      return false;
    }
  }
  else {
    if (!(toMove->legal_move_shape(start, end))) {
      return false;
    }
    if (toTarget != nullptr) {
      return false;
    }
  }
  return true;
}


bool Chess::in_check(bool white) const {

  pair<char,char> pos;
  // finds the king
  for (char i = '1'; i <= '8'; i++){
    for (char j = 'A'; j <= 'H'; j++){
      pair<char,char> cur(j,i);
      const Piece* temp = board(cur);
      if (temp == nullptr){ }
      else if (temp->to_ascii() == 'K' && white){
	pos.first = j;
	pos.second = i;
      }else if (temp->to_ascii() == 'k' && !white){
	pos.first = j;
	pos.second = i;
      }
    }
  }

  for (char i = '1'; i <= '8'; i++){
    for (char j = 'A'; j <= 'H'; j++){
      pair<char,char> curPos(j,i);
      const Piece* temp = board(curPos);

      
      if (temp != nullptr){
	if (temp->is_white() != white) {
	  if (is_valid_move(curPos, pos, true)){
	    return true;
	   }
	}
      }
    }
  }
  return false;
}


bool Chess::in_mate(bool white) const {
  if (!(in_check(white))) {
    return false;
  }
  else if (in_stalemate(white)) {
    return true;
  }
  return false;
}


bool Chess::in_stalemate(bool white) const {
  Chess mirror;
  stringstream copy;
  copy << *this;
  copy >> mirror;
  char temp;
  if (white) {
    temp = 'w';
  } else {
    temp = 'b';
  }
    
  mirror.set_turn(temp);
  
  for (char i = 'A'; i <= 'H'; i++) {
    for (char j = '1'; j <= '8'; j++) {
      for (char u = 'A'; u <= 'H'; u++) {
        for (char v = '1'; v <= '8'; v++) {
	  pair <char, char> toMove (i,j);
	  pair <char, char> toTarget (u,v);
	  if (mirror.make_move(toMove, toTarget)){
	    return false;
	  }
	}
      }
    }
  }

  
  return true;
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
  
  chess.board.clear_board();
  for (int i = '8'; i >= '1'; i--){
    for (int j = 'A'; j <= 'H'; j++){
      is >> temp;
      if (temp != '-'){
        std::pair<char,char> pos(j,i);
	chess.board.add_piece(pos, temp);
      }
    }
  }
  is >> temp;
  if (!(chess.set_turn(temp))) {
    cout << "there was an error in the input file" << endl;
  }
  
  return is;
}

bool Chess::set_turn(char color) {;
  if (color != 'b' &&
      color != 'w') {
    return false;
  }
  else if (color == 'b') {
    is_white_turn = false;
    return true;
  }
  else {
    is_white_turn = true;
    return true;
  }
}

