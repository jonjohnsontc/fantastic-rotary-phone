/*

  Find the maximum sum in an array of values.

  When finding the maximum sum of two elements in a segment tree, there are
  three options that we can run across:
  - Maximum sum is in the left child
  - Max sum is in the right child
  - max sum includes one element from left child and one element from right
  child

*/
#include <stdio.h>
typedef struct segtree_node {
  int left, right;
  int max_sum;
  int max_element;
} segtree_node;

typedef struct node_info {
  int max_sum, max_element;
} node_info;

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

node_info fill_segtree(segtree_node segtree[], int node, int seq[]) {
  node_info left_info, right_info;
  if (segtree[node].left == segtree[node].right) {
    // We set segtree's of single values to -1, so that
    // our program knows that they can't be used as maximum
    // sum options when picking segments,
    segtree[node].max_sum = -1;
    segtree[node].max_element = seq[segtree[node].left];
    return (node_info){segtree[node].max_sum, segtree[node].max_element};
  }
  left_info = fill_segtree(segtree, node * 2, seq);
  right_info = fill_segtree(segtree, node * 2 + 1, seq);
  segtree[node].max_element =
      max(left_info.max_element, right_info.max_element);

  // both left and right are single number segments
  if (left_info.max_sum == -1 && right_info.max_sum == -1)
    segtree[node].max_sum = left_info.max_element + right_info.max_element;
  // left is a single number segment
  else if (left_info.max_sum == -1)
    segtree[node].max_sum =
        max(left_info.max_element + right_info.max_element, right_info.max_sum);
  // right is a single number segment
  else if (right_info.max_sum == -1)
    segtree[node].max_sum =
        max(left_info.max_element + right_info.max_element, left_info.max_sum);
  else
    // Two max calls give us what we need to find out the largest of the three
    // possible scenarios
    segtree[node].max_sum = max(left_info.max_element + right_info.max_element,
                                max(left_info.max_sum, right_info.max_sum));
  return (node_info){segtree[node].max_sum, segtree[node].max_element};
}

node_info query_segtree(segtree_node segtree[], int node, int seq[], int left,
                        int right) {
  node_info left_info, right_info, ret_info;
  // if a node's segment has nothing in common with the query range
  if (right < segtree[node].left || left > segtree[node].right)
    return (node_info){-1, -1};
  // if a node's segment is completely contained in the query range
  // we just need to return the max's of that segment
  if (left <= segtree[node].left && segtree[node].right <= right)
    return (node_info){segtree[node].max_sum, segtree[node].max_element};

  left_info = query_segtree(segtree, node * 2, seq, left, right);
  right_info = query_segtree(segtree, node * 2 + 1, seq, left, right);

  if (left_info.max_element == -1)
    return right_info;
  if (right_info.max_element == -1)
    return left_info;

  ret_info.max_element = max(left_info.max_element, right_info.max_element);

  if (left_info.max_sum == -1 && right_info.max_sum == -1) {
    ret_info.max_sum = left_info.max_element + right_info.max_element;
    return ret_info;
  } else if (left_info.max_sum == -1) {
    ret_info.max_sum =
        max(left_info.max_element + right_info.max_element, right_info.max_sum);
    return ret_info;
  } else if (right_info.max_sum == -1) {
    ret_info.max_sum =
        max(left_info.max_element + right_info.max_element, left_info.max_sum);
    return ret_info;
  } else {
    ret_info.max_sum = max(left_info.max_element + right_info.max_element,
                           max(left_info.max_sum, right_info.max_sum));
    return ret_info;
  }
}

// Update segtree at node passed through (typically 1). Note that this should be
// called after the array element has been updated
node_info update_segtree(segtree_node segtree[], int node, int seq[],
                         int index) {
  segtree_node left_node, right_node;
  node_info left_info, right_info;

  // if our segtree only contains one element, we need to replace it
  if (segtree[node].left == segtree[node].right) {
    segtree[node].max_element = seq[index];
    return (node_info){segtree[node].max_sum, segtree[node].max_element};
  }

  left_node = segtree[node * 2];
  right_node = segtree[node * 2 + 1];

  // if the index comes before the left child's segment ends, that means that
  // it's contained in the left segment, so we should update it otherwise,
  // we should update the right child's segment
  if (index <= left_node.right) {
    left_info = update_segtree(segtree, node * 2, seq, index);
    right_info = (node_info){right_node.max_sum, right_node.max_element};
  } else {
    right_info = update_segtree(segtree, node * 2 + 1, seq, index);
    left_info = (node_info){left_node.max_sum, left_node.max_element};
  }

  segtree[node].max_element =
      max(left_info.max_element, right_info.max_element);

  if (left_info.max_sum == -1 && right_info.max_sum == -1)
    segtree[node].max_sum = left_info.max_element + right_info.max_element;
  else if (left_info.max_sum == -1)
    segtree[node].max_sum =
        max(left_info.max_element + right_info.max_element, right_info.max_sum);
  else if (right_info.max_sum == -1)
    segtree[node].max_sum =
        max(left_info.max_element + right_info.max_element, left_info.max_sum);
  else
    segtree[node].max_sum = max(left_info.max_element + right_info.max_element,
                                max(left_info.max_sum, right_info.max_sum));
  return (node_info){segtree[node].max_sum, segtree[node].max_element};
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

#define MAX_SEQ 100000

int main(void) {
  static int seq[MAX_SEQ + 1];
  static segtree_node segtree[MAX_SEQ * 4 + 1];
  int num_seq, num_ops, i, op, x, y;
  char c;
  scanf("%d", &num_seq);
  for (i = 1; i <= num_seq; i++)
    scanf("%d", &seq[i]);
  init_segtree(segtree, 1, 1, num_seq);
  fill_segtree(segtree, 1, seq);
  scanf("%d", &num_ops);
  for (op = 0; op < num_ops; op++) {
    scanf(" %c%d%d ", &c, &x, &y);

    if (c == 'U') {
      seq[x] = y;
      update_segtree(segtree, 1, seq, x);
    } else {
      printf("%d\n", query_segtree(segtree, 1, seq, x, y).max_sum);
    }
  }

  return 0;
}
