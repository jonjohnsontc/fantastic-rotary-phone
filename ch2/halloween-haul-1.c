#include <stdlib.h>
#define MAX_CANDY 20
#define MAX_LINE_CHARS 256

#include <stdio.h>
/* Spent some time trying to figure out the best way to model a BinaryTree.
Ended up consulting chatgpt which suggested this.

Given that the problem will either give us value nodes or pointer nodes:
    - val = 0 means its a pointer node (road)
    - pointer = NULL means its a value node (house) */
typedef struct node {
  int val;
  struct node *left;
  struct node *right;
} Node;


void parse_hood(Node *root) {
  if (root == NULL) {
    root = malloc(sizeof(Node));
    if (root == NULL) {
      printf("malloc error\n");
      exit(1);
    }
  }
  int c;
  int buf[2];
  while ((c = getchar()) != '\0') {
    continue;
  }
 }

/* 
  Input contains 5 test cases 
  Each test case is a line describing tree < MAX_LINE_CHARS
  Each test case should output R and C
    R minimum num of roads traveled to get all candy starting from top of tree
      and needing not return
    C total num of candy 
*/
int main(void) {
  int r, c;
  Node *neighborhood;
  parse_hood(neighborhood);
  return 0;
}