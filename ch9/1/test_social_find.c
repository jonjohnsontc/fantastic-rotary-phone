#include <assert.h>
int find(int person, int parent[]) {
  int root = person;
  while (root != parent[root]) {
    root = parent[root];
  }
  return root;
}

int main(void) {
  int person = 5;
  int parents[] = {4, 1, 3, 3, 6, 1};
  int result = find(person, parents);
  assert(result == 1);
}