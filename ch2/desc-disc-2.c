/*
    input with n test cases
    first line indicates n
        each test case starts with two integers n and d
            n - num of lines containing info about family tree
            d - specific info being asked about the tree
                1 - Want persons with most children (1 Generation away)
                2 - most grandchildren / 2 gens away
        The next n lines describe a single connected family tree:
            name m dname-to-the-m-1...etc

    output:
        for each test test case
            output three names with the largest num of specified descendents in
              descending order, ties should sort alphabetically
            If fewer than three names match test criteria, just print the names
              that match
            If there is a tie at the bottom of the list, print more than three
            Each case should start with "Tree i:"

*/
#include <stdio.h>
#define MAX_FAMILY 1000
#define MAX_NAME 10

// Seems like any family member can have any number of children
// only hard cap is a total family size of 1000
// So a node with a linked-list of children might be the easiest way to handle
// this HOWEVER, we also get the count of children to come, so that makes me
// think we could just use an array
typedef struct family_m {
  char *name;
  int no_children;
  struct family_m *children[];
} family_m;

// given a current gen lineup, how would I construct a family_m node?
family_m *give_birth() {
  int size;
  char *name;
  scanf("%s %d", name, &size);
  
}

int main(void) {}