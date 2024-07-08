#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 50000
#define LABEL_LENGTH 16
typedef struct treap_node {
  char *label;
  int priority;
} treap_node;

char *read_label(int size) {
  char *str;
  int ch;
  int len = 0;
  str = malloc(size);
  if (str == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  while ((ch = getchar()) != EOF && (ch != '/')) {
    str[len++] = ch;
    if (len == size) {
      size = size * 2;
      str = realloc(str, size);
      if (str == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
      }
    }
  }
  str[len] = '\0';
  return str;
}

int main(void) {
  static treap_node treap_nodes[MAX_NODES];
  int num_nodes, i;
  scanf("%d", &num_nodes);
  while (num_nodes > 0) {
    for (i = 0; i < num_nodes; i++) {
      treap_nodes[i].label = read_label(LABEL_LENGTH);
      scanf("%d", &treap_nodes[i].priority);
    }
    // sorting the nodes beforehand means that the array will be perfectly
    // sorted to recursively calling the solve function
    qsort(treap_nodes, num_nodes, sizeof(treap_node), compare);
    solve(treap_nodes, 0, num_nodes - 1);
    printf("\n");
    scanf("%d", &num_nodes);
  }
}
