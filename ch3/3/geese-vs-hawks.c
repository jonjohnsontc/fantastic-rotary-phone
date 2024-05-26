// This is my blind approach before consulting the book
// What would be my brute force approach, knowing what I know?
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define GAMES_MAX 1000

int valid_game(char gg, int gs, char hg, int hs) {
  if ((gg == 1 && hg == 0 && gg > hg) || (hg == 1 && gg == 0 && hg > gg))
    return 1;
  return 0;
}

int compute_highest_score(int no_games, char hawks_games[], int hawks_scores[],
                          char geese_games[], int geese_scores[]) {
  int i, j;
  return -1;
}

// I know that I have to maintain an order between the games
// i.e.,
// Geese Game 2 can't count as a win against 
int main(void) {
  int games; // no of games played
  size_t sz, size = 0;
  char *GEESE = NULL;
  char *INTRO = NULL;
  // char *HAWKS = NULL;

  sz = getline(&INTRO, &size, stdin);
  sscanf(INTRO, "%d", &games);
  size = 0;
  sz = getline(&GEESE, &size, stdin);
  printf("Scanning through %d games\n", games);
  printf("First set of Games look like %s", GEESE);
  printf("There are %lu of them\n", sz / sizeof(char) - 1);

  free(GEESE);
  free(INTRO);
}