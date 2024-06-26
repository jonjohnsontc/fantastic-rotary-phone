/*
    Reach for the Top
    https://dmoj.ca/problem/wc18c1s3

    Bob needs to climb a rope in gym class

    - required height >= H meters
    - he can go up (jump) J meters
    - he can fall down any # of meters
    - he can't touch any portions w/ itching powder

   min number of moves to get to height h or heigher
   if impossible, return -1

    Input Format

    h j n
    n lines of segments of itching powder

    Number of moves available to Bob is based on his height, as he can drop
    from any # of meters

    They say we can get to height h or higher, so what is the max height we
    should search against? The author says 2h

    This is bacause one move prior, Bob would be at:

    2h - j >= h and we'd already be at h, so 2h will definitely not be optimal
    (but earlier ones may be)
*/
#include <stdio.h>
#define SIZE 1000000

typedef int board[SIZE * 2];
typedef int positions[SIZE * 2];

void add_position(int from_height, int to_height, int max_height,
                  positions new_positions, int *num_new_positions,
                  int itching[], board min_moves) {
  if (to_height <= max_height && itching[to_height] == 0 &&
      min_moves[to_height] == -1) {
    min_moves[to_height] = 1 + min_moves[from_height];
    new_positions[*num_new_positions] = to_height;
    (*num_new_positions)++;
  }
}

/*
Finding distances from different nodes in this manner acumulates function
calls in two manners, from jump edges and from fall edges

Fall edges accumulate at a rate of h(h + 1)/2, which looks quadratic to me
*/
void find_distances(int target_height, int jump_distance, int itching[],
                    board min_moves) {
  static positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions;
  int i, j, from_height;
  for (i = 0; i < target_height * 2; i++)
    min_moves[i] = -1;
  min_moves[0] = 0;
  cur_positions[0] = 0;
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;
    for (i = 0; i < num_cur_positions; i++) {
      from_height = cur_positions[i];
      add_position(from_height, from_height + jump_distance,
                   target_height * 2 - 1, new_positions, &num_new_positions,
                   itching, min_moves);
      for (j = 0; j < from_height; j++)
        add_position(from_height, j, target_height * 2 - 1, new_positions,
                     &num_new_positions, itching, min_moves);
    }
    num_cur_positions = num_new_positions;
    for (i = 0; i < num_cur_positions; i++)
      cur_positions[i] = new_positions[i];
  }
}

void solve(int target_height, board min_moves) {
  int best = -1;
  int i;
  for (i = target_height; i < target_height * 2; i++)
    if (min_moves[i] != -1 && (best == -1 || min_moves[i] < best))
      best = min_moves[i];
  printf("%d\n", best);
}

int main(void) {
  int target_height, jump_distance, num_itching_sections;
  static int itching[SIZE * 2] = {0};
  static board min_moves;
  int i, j, itch_start, itch_end;
  scanf("%d%d%d", &target_height, &jump_distance, &num_itching_sections);
  for (i = 0; i < num_itching_sections; i++) {
    scanf("%d%d", &itch_start, &itch_end);
    for (j = itch_start; j <= itch_end; j++)
      itching[j] = 1;
  }
  find_distances(target_height, jump_distance, itching, min_moves);
  solve(target_height, min_moves);

  return 0;
}