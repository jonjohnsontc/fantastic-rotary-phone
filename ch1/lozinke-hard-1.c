// 1st line contains the number of queries, Q (always positive)
// the next Q lines will contain one of two queries
// 1 str: Insert s t r into the password database.
// 2 str: Output the number of users that can log into an account that has password s t r .
#define QUERY_MAX 100000
#define PASSWORD_MAX 10

// What's the naive way to solve this?
// for each 2 line encountered, search each entry of the password db to see if it
// can be found
