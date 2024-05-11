// from https://codeforces.com/problemset/problem/39/J

// input data contains two strings, all lower-case letters
// length of each string is 1 to 10,000,000 inclusive
// first string contains 1 more symbol than second

// print number of positions you can delete from first string
// print in order each position you can delete

// abdrakadabra
// abrakadabra

// 1
// 3

// This problem is looking for us to compare the string, and then figure out how
// many ways we can deviate from one string to get to the next

// We could brake this into two steps:
// - comparing the strings, if successful:
//  - removing a single index from one string and compare them
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_MAX 10000000

int check_for_left(char *string, int idx) {
  int count;
  char char_in_question = string[idx];
  for (count = 0; idx - 1 >= 0; idx--, count++) {
    if (char_in_question != string[idx - 1])
      break;
  }
  return count;
}

int check_for_right(char *string, int idx) {
  int count;
  char char_in_question = string[idx];
  for (count = 0; idx + 1 < strlen(string); count++, idx++) {
    if (char_in_question != string[idx + 1])
      break;
  }
  return count;
}

int main(void) {
  char *word = malloc(sizeof(char) * STRING_MAX);
  char *corrected = malloc(sizeof(char) * STRING_MAX - 1);
  scanf("%s%s", word, corrected);
  
  int i = 0, j = i;
  int num_indices = 0;
  int *corrected_idx;
  char *corrected_char;

  while (i < strlen(word)) {
    if (i > j + 1) {
      printf("0\n");
      exit(0);
    } 
    if (word[i] != corrected[j]) {
      corrected_idx = malloc(sizeof(int));
      corrected_char = malloc(sizeof(char));
      *corrected_idx = i;
      *corrected_char = corrected[j];
      num_indices++;
      i++;
      continue;
    }
    i++; // increase ptr to word
    j++; // increase ptr to corrected
  }

  if (corrected_idx != NULL) {
    int left_indices = 0;
    int right_indices = 0;
    left_indices += check_for_left(word, *corrected_idx);
    right_indices += check_for_right(word, *corrected_idx); 

    int no_ways = left_indices + right_indices + 1;
    printf("%d\n", no_ways);

    if (left_indices > 0) {
      for (; left_indices > 0; left_indices--) 
        printf("%d ", (*corrected_idx) - left_indices + 1);
    }
    printf("%d ", *corrected_idx + 1);
    
    if (right_indices > 0) {
      for (int idx = 1; idx <= right_indices; idx++)
        printf("%d ", (*corrected_idx) + idx + 1);
    }
    printf("\n");
  }

  free(word);
  free(corrected);
  return 0;
}