/*

Implementing a Social Network supporting three different types of queries:

- A x y - x sends a friend request to y
- E x y - check whether x and y are part of the same community
- S x - prints the size of the community x belongs to

Friend requests are excepted if the merger of the two communities is less than
the maximum size of the community 'm'.

First line contains n and m
next line is q (no of queries)
q lines of queries follows

In my head, I would want to only have one copy of the entire social network
available, and then associate some value with what communities it was a part of

Initially, every member of the social network will be a part of their own
community of 1. It will then grow according to the number of friend requests it
and associated members gets

Queries are 1-indexed

The book intros this as a problem for the union-find data structure,
an expansion on the adjacency list data structure used to help solve graph
problems in chapters 5 and 6.

An adjacency list maps edges between nodes out in an array, where each node
is an index in the edge array, and the edges have an integer representing the
node they travel to, as well as a length and reference to the next edge.
*/
#include <stdio.h>
#define M_MAX 100000
#define QUERY_MAX 200000
typedef struct community {
  int to_user;
  struct community *next;
} community;

int add_friend(int from_user, int to_user);
void examine(int user1, int user2);
int get_size(int user);

int main(void) {
  community network[M_MAX + 1]; // represents users communities
  int sizes[M_MAX + 1];
  int no_people, community_max;
  int no_ops;
  scanf("%d %d ", &no_people, &community_max);
  scanf("%d", &no_ops);

  while (no_ops) {
    no_ops--;
  }
  return 0;
}