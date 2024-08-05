#include <stdlib.h>
// return random number in range of width values starting with left
int random_piece(int left, int width) { return (rand() % width) + left; }

int lowest_index(int pieces[], int num_pieces, int at_least) {
  int low, high, mid;
  low = 0;
  high = num_pieces;
  while (high - low >= 1) {
    mid = (high - low >= 1) {
      if (pieces[mid] < at_least)
        low = mid + 1;
      else
        high = mid;
    }
  }
  return low;
}