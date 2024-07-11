/*
  Building a treap by using a segment tree
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODES 50000
#define LABEL_LENGTH 16
typedef struct segtree_node {
  int left, right;
  int max_index;
} segtree_node;

// data representation of input which is a character array and
// priority number separated by slash (e.g.,"A/9")
typedef struct treap_node {
  char *label;
  int priority;
} treap_node;

int compare(const void *v1, const void *v2) {
  const treap_node *n1 = v1;
  const treap_node *n2 = v2;
  return strcmp(n1->label, n2->label);
}

void init_segtree(segtree_node segtree[], int node, int left, int right) {
  int mid;
  segtree[node].left = left;
  segtree[node].right = right;
  if (left == right)
    return;
  mid = (left + right) / 2;
  init_segtree(segtree, node * 2, left, mid);
  init_segtree(segtree, node * 2 + 1, mid + 1, right);
}

int fill_segtree(segtree_node segtree[], int node, treap_node treap_nodes[]) {
  int left_max, right_max;
  if (segtree[node].left == segtree[node].right) {
    segtree[node].max_index = segtree[node].left;
    return segtree[node].max_index;
  }
  left_max = fill_segtree(segtree, node * 2, treap_nodes);
  right_max = fill_segtree(segtree, node * 2 + 1, treap_nodes);
  if (treap_nodes[left_max].priority > treap_nodes[right_max].priority)
    segtree[node].max_index = left_max;
  else
    segtree[node].max_index = right_max;
  return segtree[node].max_index;
}

int query_segtree(segtree_node segtree[], int node, treap_node treap_nodes[],
                  int left, int right) {
  int left_max, right_max;
  // if query range does not match the range of the segtree
  // we won't be able to conduct the query
  if (right < segtree[node].left || left > segtree[node].right)
    return -1;
  // if the node's segment completely contains the query range
  // we just need to return the max_index
  if (left <= segtree[node].left && segtree[node].right <= right)
    return segtree[node].max_index;

  left_max = query_segtree(segtree, node * 2, treap_nodes, left, right);
  right_max = query_segtree(segtree, node * 2 + 1, treap_nodes, left, right);

  if (left_max == -1)
    return right_max;
  if (right_max == -1)
    return left_max;
  if (treap_nodes[left_max].priority > treap_nodes[right_max].priority)
    return left_max;
  return right_max;
}

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

void solve(treap_node treap_nodes[], int left, int right,
           segtree_node segtree[]) {
  int root_index;
  treap_node root;
  if (left > right)
    return;
  root_index = query_segtree(segtree, 1, treap_nodes, left, right);
  root = treap_nodes[root_index];
  printf("(");
  solve(treap_nodes, left, root_index - 1, segtree);
  printf("%s/%d", root.label, root.priority);
  solve(treap_nodes, root_index + 1, right, segtree);
  printf(")");
}

int main(void) {
  static treap_node treap_nodes[MAX_NODES];
  // 4x the number of nodes should allow for us to cover all segments
  static segtree_node segtree_nodes[MAX_NODES * 4 + 1];
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
    init_segtree(segtree_nodes, 1, 0, num_nodes - 1);
    fill_segtree(segtree_nodes, 1, treap_nodes);
    solve(treap_nodes, 0, num_nodes - 1, segtree_nodes);
    printf("\n");
    scanf("%d", &num_nodes);
  }
}
