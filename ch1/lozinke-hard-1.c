// 1st line contains the number of queries, Q (always positive)
// the next Q lines will contain one of two queries
// 1 str: Insert s t r into the password database.
// 2 str: Output the number of users that can log into an account that has
// password s t r .
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char *key, unsigned long len, unsigned long bits) {
  unsigned long hash, i;
  for (hash = 0, i = 0; i < len; i++) {
    hash += key[i];       // add char of key to hash
    hash += (hash << 10); // add to hash bitshifted hash val
    hash ^= (hash >> 6);  // take to the power of hashval bitshifted val
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash & hashmask(bits);
}

#define QUERY_MAX 100000
#define PASSWORD_MAX 10
#define NUM_BITS 20
typedef struct password_node {
  char password[PASSWORD_MAX + 1];
  int total;
  struct password_node *next;
} password_node;

password_node *in_hash_table(password_node *hash_table[], char *find) {
  unsigned password_code;
  password_node *password_ptr;
  password_code = oaat(find, strlen(find), NUM_BITS);
  password_ptr = hash_table[password_code];
  while (password_ptr) {
    if (strcmp(password_ptr->password, find) == 0)
      return password_ptr;
    password_ptr = password_ptr->next;
  }
  return NULL;
}

void add_to_hash_table(password_node *hash_table[], char *find) {
  unsigned password_code;
  password_node *password_ptr;
  password_ptr = in_hash_table(hash_table, find);

  if (!password_ptr) {
    password_code = oaat(find, strlen(find), NUM_BITS);
    password_ptr = malloc(sizeof(password_node));
    if (password_ptr == NULL) {
      fprintf(stderr, "malloc error\n");
      exit(1);
    }
    strcpy(password_ptr->password, find);
    password_ptr->total = 0;
    password_ptr->next = hash_table[password_code];
    hash_table[password_code] = password_ptr;
  }
  password_ptr->total++;
}

// bugged!

int main(void) {
  static password_node *hash_table[1 << NUM_BITS] = {NULL};
  int num_ops, op, op_type, i, j;
  char password[PASSWORD_MAX + 1], substring[PASSWORD_MAX + 1];
  password_node *password_ptr;
  scanf("%d", &num_ops);
  for (op = 0; op < num_ops; op++) {
    scanf("%d%s", &op_type, password);

    if (op_type == 1) {
      for (i = 0; i < strlen(password); i++)
        for (j = i; j < strlen(password); j++) {
          strncpy(substring, &password[i], j - i + 1);
          substring[j - i + 1] = '\0';
          add_to_hash_table(hash_table, substring);
        }
    } else {
      password_ptr = in_hash_table(hash_table, password);
      if (!password_ptr)
        printf("0\n");
      else
        printf("%d\n", password_ptr->total);
    }
  }
  return 0;
}