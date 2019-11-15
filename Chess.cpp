#include "Chess.h"

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
  // stores the board to field
  Board field = this->get_board();

  // stores the piece on start to toMove
  const Piece * toMove = field(start);

  // stores the piece type in a char
  char type = toMove->to_ascii();
  
  // checks start and end are valid
  if (!(is_valid_pos(start) && is_valid_pos(end))) {
    return false;
  }
  // checks that there is a piece there
  if (toMove == nullptr) {
    return false;
  }
  // checks that the piece is on the same side as the player
  if (toMove->is_white() != this->is_white_turn) {
    return false;
  }
  // checks if there is a piece on end, and then checks legal
  // move shape or legal capture shape in accordance
  const Piece * target = field(end);

  if (target == nullptr) {
    if (!(toMove->legal_move_shape(start, end))) {
      return false;
    }
    else {
      field.add_piece(end, type);
      delete toMove;
      return true;
    }
  }
  else {
    if (!(toMove->legal_capture_shape(start, end))) {
      return false;
    }
    else {
      delete target;
      delete toMove;
      field.add_piece(end, type);
      return true;
    }
  } 
  return false;
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
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return is;
}
