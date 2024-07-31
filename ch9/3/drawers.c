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

void insert(Item *drawers, int id, int left, int right);
int main(void) {
  static Item drawers[MAX_DRAWERS + 1];
  int no_items, no_drawers;
  int item, drawer;
  int left, right;
  scanf("%d%d", &no_items, &no_drawers);
  for (item = 1; item < no_items; item++) {
    scanf("%d%d", &left, &right);
    insert(drawers, item, left, right);
  }
  return 0;
}

void set_drawer(Item *drawers, int id, int location, int other_drawer) {
  drawers[location].id = id;
  drawers[location].other_drawer = other_drawer;
  drawers[location].is_set = true;
  printf("LADICA");
}

void insert(Item *drawers, int item, int left, int right) {
  if (!drawers[left].is_set) {
    set_drawer(drawers, item, left, right);
  } else if (!drawers[right].is_set) {
    set_drawer(drawers, item, right, left);
  } else {
    insert(drawers, drawers[left].id, left, drawers[left].other_drawer);
    insert(drawers, drawers[right].id, right, drawers[right].other_drawer);
  }
}
