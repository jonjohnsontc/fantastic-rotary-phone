#include <stdio.h>
#include <stdlib.h>
#define MAX_PEOPLE 100000

typedef struct edge {
  int to_person;
  struct edge *next;
} edge;

void find_distances(edge *adj_list[], int person, int num_people,
                    int min_moves[]);
int size(int num_people, int min_moves[]);

int main(void) {
  static edge *adj_list[MAX_PEOPLE + 1] = {NULL};
  static int min_moves[MAX_PEOPLE + 1];
  int num_people, num_community, num_ops, i;
  char op;
  int person1, person2;
  edge *e;
  int size1, size2, same_community;

  // Read in the essential input
  scanf("%d%d", &num_people, &num_community);
  scanf("%d", &num_ops);

  for (i = 0; i < num_ops; i++) {
    scanf(" %c", &op);
    if (op == 'A') {
      scanf("%d%d", &person1, &person2);
      // fill min_moves array with distances b/w person1 and all others
      find_distances(adj_list, person1, num_people, min_moves);
      // determine size based on total size of population and min_moves
      size1 = size(num_people, min_moves);
      same_community = 0;
      // if person2 is reachable from person1, we mark them in the same
      // community
      if (min_moves[person2] != -1)
        same_community = 1;
      // Determine the same for person2
      find_distances(adj_list, person2, num_people, min_moves);
      size2 = size(num_people, min_moves);
      if (same_community || size1 + size2 <= num_community) {
        // create the edges that point to each person in their respective
        // adjacency arrays
        e = malloc(sizeof(edge));
        if (e == NULL) {
          fprintf(stderr, "malloc error\n");
          exit(1);
        }
        e->to_person = person2;
        e->next = adj_list[person1];
        adj_list[person1] = e;
        e = malloc(sizeof(edge));
        if (e == NULL) {
          fprintf(stderr, "malloc error\n");
          exit(1);
        }
        e->to_person = person1;
        e->next = adj_list[person2];
        adj_list[person2] = e;
      }
    } else if (op == 'E') {
      scanf("%d%d", &person1, &person2);
      // we just need to find distances from one person to make sure they
      // can connect
      find_distances(adj_list, person1, num_people, min_moves);
      if (min_moves[person2] != -1)
        printf("Yes\n");
      else
        printf("No\n");
    } else { // 'S' - size query
      scanf("%d", &person1);
      find_distances(adj_list, person1, num_people, min_moves);
      printf("%d\n", size(num_people, min_moves));
    }
  }
  return 0;
}

void add_position(int from_person, int to_person, int new_positions[],
                  int *num_new_positions, int min_moves[]) {
  if (min_moves[to_person] == -1) {
    min_moves[to_person] = 1 + min_moves[from_person];
    new_positions[*num_new_positions] = to_person;
    (*num_new_positions)++;
  }
}

void find_distances(edge *adj_list[], int person, int num_people,
                    int min_moves[]) {
  static int cur_positions[MAX_PEOPLE + 1], new_positions[MAX_PEOPLE + 1];
  int num_cur_positions, num_new_positions;
  int i, from_person;
  edge *e;
  for (i = 1; i <= num_people; i++)
    min_moves[i] = -1;
  min_moves[person] = 0;
  cur_positions[0] = person;
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;
    for (i = 0; i < num_cur_positions; i++) {
      from_person = cur_positions[i];
      e = adj_list[from_person];

      while (e) {
        add_position(from_person, e->to_person, new_positions,
                     &num_new_positions, min_moves);
        e = e->next;
      }
    }

    num_cur_positions = num_new_positions;
    for (i = 0; i < num_cur_positions; i++)
      cur_positions[i] = new_positions[i];
  }
}

int size(int num_people, int min_moves[]) {
  int i, total = 0;
  for (i = 1; i <= num_people; i++)
    if (min_moves[i] != -1)
      total++;
  return total;
}