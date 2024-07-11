/*
  Find the maximum sum in an array of updating values. The underlying
  implementation for how the sum is found is made using a segment tree

  Input will be an array and a number of operations on the array.
  If the operation is a query operation, return the maximum sum for that
  operation.
  If the operation is an update operation, change the integer at location 1 to 2
*/
#define OPTS_MAX 100000
#define ARRAY_MAX 100000
#define INT_MAX 100000000

typedef struct segtree_node {
  int left, right;
  int max_index;
} segtree_node;

// Establish boundaries of each segment in the segment tree
// At completion, each segtree node will represent a range
// of indices
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

// Traverse through segtree recursively, and determine the max_index for each
// node based on the previous max values returned
int fill_segtree(segtree_node segtree[], int node, int sequence[]) {
  int left_max, right_max;
  if (segtree[node].left == segtree[node].right) {
    segtree[node].max_index = segtree[node].left;
    return segtree[node].max_index;
  }
  left_max = fill_segtree(segtree, node * 2, sequence);
  right_max = fill_segtree(segtree, node * 2 + 1, sequence);
  if (sequence[left_max] > sequence[right_max])
    segtree[node].max_index = left_max;
  else
    segtree[node].max_index = right_max;
  return segtree[node].max_index;
}

// Query segment range and return maximum sum of nodes
int query_segtree(segtree_node segtree[], int left, int right) { return -1; }

void update_segtree(segtree_node segtree[], int node, int value) {}

int main(void) {
  int input[ARRAY_MAX];
  int segtree[ARRAY_MAX * 4 + 1];
  // we first want to read the input into an array
  // we then want to split the array into the segment tree
  // We'll then iterate through all of the operations
  // Q opts will give us a range sum query
  // U opts will cause us to update segment tree
}