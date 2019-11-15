#include "Helper.h"

bool is_valid_pos(std::pair<char, char> position) {
  if (position.first < 'A'  ||
      position.forst > 'H'  ||
      position.second < '1' ||
      position.second > '8')  {
    return true;
  }
  else {
    return false;
  }
}
