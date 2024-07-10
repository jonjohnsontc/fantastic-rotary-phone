/*
  Building a treap by using a segment tree
*/
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