#include <stdio.h>
#define MAX_PEOPLE 10000

int are_enemies(int person1, int person2, int *parent, int *enemy_of);
int are_friends(int person1, int person2, int *parent);
void set_friends(int person1, int person2, int *parent, int *size,
                 int *enemy_of);
void set_enemies(int person1, int person2, int *parent, int *size,
                 int *enemy_of);

int main(void) {
  static int parent[MAX_PEOPLE], size[MAX_PEOPLE];
  static int enemy_of[MAX_PEOPLE];
  int num_people, i;
  int op, person1, person2;
  scanf("%d", &num_people);
  for (i = 0; i < num_people; i++) {
    parent[i] = i;
    size[i] = i;
    enemy_of[i] = -1;
  }
  scanf("%d%d%d", &op, &person1, &person2);

  while (op != 0) {
    if (op == 1) // set friends
      if (are_enemies(person1, person2, parent, enemy_of))
        printf("-1\n");
      else
        set_friends(person1, person2, parent, size, enemy_of);
    else if (op == 2) // set enemies
      if (are_friends(person1, person2, parent))
        printf("-1\n");
      else
        set_enemies(person1, person2, parent, size, enemy_of);
    else if (op == 3) // are friends
      if (are_friends(person1, person2, parent))
        printf("-1\n");
      else
        printf("0\n");
    else if (op == 4) { // are enemies
      if (are_enemies(person1, person2, parent, enemy_of))
        printf("1\n");
      else
        printf("0\n");
    }
    scanf("%d%d%d", &op, &person1, &person2);
  }
  return 0;
}