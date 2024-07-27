/*
  My first stab at the War problem (war.pdf)

  ~ friends
  * enemies

  setFriends and setEnemies must preserve the following

  if x ~ y and y ~ z then x ~ z
  if x ~ y then y ~ x
  x ~ x

  if x * y then y * x
  not x * x (can't hate yourself)

  if x * y and y * z then x ~ z (enemy of my enemy is my friend)
  if x ~ y and y * z then x * z (i hate your haters)

  the number of possible operations is unconstrained

*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_PEOPLE 10000

void setFriends(int *enemies, int *friends, int x, int y);
void setEnemies(int *enemies, int *friends, int x, int y);
bool areFriends(int *enemies, int *friends, int x, int y);
bool areEnemies(int *enemies, int *friends, int x, int y);

int main(void) {
  int friends[MAX_PEOPLE], enemies[MAX_PEOPLE];
  int no_people;
  int op, x, y;
  // initialize friends and enemies
  scanf("%d ", &no_people);
  printf("Population of %d\n", no_people);
  for (int i = 0; i < no_people; i++) {
    friends[i] = i;
    enemies[i] = -1;
  }
  while (scanf("%d", &op), op != 0) {
    scanf("%d", &x);
    scanf("%d ", &y);
    if (op == 1)
      setFriends(enemies, friends, x, y);
    else if (op == 2)
      setEnemies(enemies, friends, x, y);
    else if (op == 3)
      areFriends(enemies, friends, x, y);
    else if (op == 4)
      areEnemies(enemies, friends, x, y);
    else {
      fprintf(stderr, "Error unknown operation encountered: %d\n", op);
      exit(1);
    };
  }
  printf("Done\n");
}

void setFriends(int *enemies, int *friends, int x, int y) {
  printf("set friends b/w %d and %d\n", x, y);
}
void setEnemies(int *enemies, int *friends, int x, int y) {
  printf("set enemies b/w %d and %d\n", x, y);
}
bool areEnemies(int *enemies, int *friends, int x, int y) {
  printf("are enemies b/w %d and %d\n", x, y);
  return false;
}
bool areFriends(int *enemies, int *friends, int x, int y) {
  printf("are friends b/w %d and %d\n", x, y);
  return false;
}
