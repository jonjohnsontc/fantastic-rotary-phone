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

  thinking about the rules of friends and enemies, can their sets abide
  by the same rules?

  i don't think so
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

// returns the root of the set that person lies in, by checking
// the parent array
int find(int person, int parent[]) {
  int root = person;
  while (root != parent[root]) {
    root = parent[root];
  }
  return root;
}

void setFriends(int *enemies, int *friends, int x, int y) {

  printf("set friends b/w %d and %d\n", x, y);
}
void setEnemies(int *enemies, int *friends, int x, int y) {
  printf("set enemies b/w %d and %d\n", x, y);
}
bool areEnemies(int *enemies, int *friends, int x, int y) {
  printf("are enemies b/w %d and %d\n", x, y);

  int x_rep_friend, y_rep_friend;
  int x_rep_hater, y_rep_hater;

  x_rep_friend = find(x, friends);
  y_rep_friend = find(y, friends);

  x_rep_hater = find(x, enemies);
  y_rep_hater = find(y, enemies);
  /*
   if x * y then y * x
   not x * x (can't hate yourself)

   if x * y and y * z then x ~ z (enemy of my enemy is my friend)
   if x ~ y and y * z then x * z (i hate your haters)
  */
  if (x_rep_friend == y_rep_friend || y_rep_hater == x_rep_hater)
    return false;
  else if (x_rep_hater == y_rep_friend || y_rep_hater == x_rep_friend)
    return true;
  return false;
}
bool areFriends(int *enemies, int *friends, int x, int y) {
  printf("are friends b/w %d and %d\n", x, y);
  return false;
}
