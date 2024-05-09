#include <stdio.h>
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

int main(void) {
    char word[] = "hello";
    // 2 ^17 is the smallest power of 2 that is at least 100000
    unsigned long code = oaat(word, strlen(word), 17);
    printf("%lu\n", code);
    return 0;
}   