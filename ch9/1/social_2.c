/*
  Solving social network with a union-find data structure

  A union-find data structure takes advantage of set theory to check whether
  elements are part of the same collection.

  O(Log(n)) (best case) for set union and find operations
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_PEOPLE 100000

int find(int person, int parent[]);
void union_communities(int person1, int person2, int parent[], int size[],
                       int num_community);

int main(void) {
  static int parent_arr[MAX_PEOPLE + 1], size_arr[MAX_PEOPLE + 1];
  int num_people, num_community, num_ops, i;
  char op;
  int person1, person2;
  scanf("%d%d", &num_people, &num_community);

  for (i = 1; i <= num_people; i++) {
    parent_arr[i] = i;
    size_arr[i] = 1;
  }
  scanf("%d", &num_ops);

  for (i = 0; i < num_ops; i++) {
    scanf(" %c", &op);

    if (op == 'A') {
      scanf("%d%d", &person1, &person2);
      union_communities(person1, person2, parent_arr, size_arr, num_community);
    } else if (op == 'E') {
      scanf("%d%d", &person1, &person2);
      if (find(person1, parent_arr) == find(person2, parent_arr))
        printf("Yes\n");
      else
        printf("No\n");
    } else {
      scanf("%d", &person1);
      printf("%d\n", size_arr[find(person1, parent_arr)]);
    }
  }
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

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  return v2;
}

void union_communities(int person1, int person2, int parent[], int size[],
                       int num_community) {
  int community1, community2;
  community1 = find(person1, parent);
  community2 = find(person2, parent);
  if (community1 != community2 &&
      size[community1] + size[community2 <= num_community]) {
    if (size[community1] > size[community2]) {
      // The book example swaps community1 with community2 if it's larger
      // so it always makes community2 the parent of community1
      parent[community1] = community2;
      size[community2] = size[community2] + size[community1];
    } else {
      parent[community2] = community1;
      size[community1] = size[community2] + size[community1];
    }
  }
}
