/*

*/
#include <stdbool.h>
#include <stdio.h>
#define MAX_DRAWERS 300000
typedef struct {
  int id;
  int other_drawer;
  bool is_set;
} Item;

void insert(Item *drawers, int left, int right);
int main(void) {
  static Item drawers[MAX_DRAWERS + 1];
  int no_items, no_drawers;
  int item, drawer;
  int left, right;
  scanf("%d%d", &no_items, &no_drawers);
  for (item = 1; item < no_items; item++) {
    scanf("%d%d", &left, &right);
    insert(drawers, left, right);
  }
  return 0;
}

void insert(Item *drawers, int item, int left, int right) {
  if (!drawers[left].is_set) {
    drawers[left].id = item;
    drawers[left].other_drawer = right;
    drawers[left].is_set = true;

  } else if (!drawers[right].is_set) {
  }
}

void set_drawer(Item *drawers, int id, int location, int other_drawer) {

  printf("LADICA\n");
}