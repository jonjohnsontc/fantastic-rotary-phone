#include <stdio.h>
#include <stdlib.h>

/* Using the Stack based solution proposed first */

typedef struct node {
  int candy;
  struct node *left, *right;
} node;

#define SIZE 255

typedef struct stack {
  node *values[SIZE];
  int highest_used;
} stack;

stack *new_stack(void) {
  stack *s = malloc(sizeof(stack));
  if (s == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  s->highest_used = -1;
  return s;
}

void push_stack(stack *s, node *value) {
  s->highest_used++;
  s->values[s->highest_used] = value;
}

node *pop_stack(stack *s) {
  node *ret = s->values[s->highest_used];
  s->highest_used--;
  return ret;
}

int is_empty_stack(stack *s) { return s->highest_used == -1; }

node *new_house(int candy) {
  node *house = malloc(sizeof(node));
  if (house == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  house->candy = candy;
  house->left = NULL;
  house->right = NULL;
  return house;
}

node *new_street(node *left, node *right) {
  node *street = malloc(sizeof(node));
  if (street == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  street->left = left;
  street->right = right;
  return street;
}

int tree_candy(node *tree) {
  int total = 0;
  stack *s = new_stack();
  while (tree != NULL) {
    if (tree->left && tree->right) { /* street traversal */
      push_stack(s, tree->left);
      tree = tree->right;
    } else {                         /* at house */
      total = total + tree->candy;
      if (is_empty_stack(s))
        tree = NULL;
      else
        tree = pop_stack(s);
    }
  }
  return total;
}

int main(void) {
  // node *four = new_house(4);
  // node *nine = new_house(9);
  // node *B = new_street(four, nine);
  // node *fifteen = new_house(15);
  // node *C = new_street(B, fifteen);
  // node *two = new_house(2);
  // node *D = new_street(C, two);
  // node *six = new_house(6);
  // node *E = new_street(six, D);
  // node *seventy_two = new_house(72);
  // node *three = new_house(3);
  // node *A = new_street(seventy_two, three);
  // node *F = new_street(A, E);
  // node *seven = new_house(7);
  // node *forty_one = new_house(41);
  // node *G = new_street(seven, forty_one);
  // node *H = new_street(F, G);

  stack *s;
  s = new_stack();
  node *n, *n1, *n2, *n3;
  n1 = new_house(20);
  n2 = new_house(30);
  n3 = new_house(10);
  push_stack(s, n1);
  push_stack(s, n2);
  push_stack(s, n3);
  while (!is_empty_stack(s)) {
    n = pop_stack(s);
    printf("%d\n", n->candy);
  }
  return 0;
}