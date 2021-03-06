#include "eval.h"
#include "mpc.h"

#include <math.h>

long eval_op(long x, char *op, long y) {
  if (strcmp(op, "+") == 0)
    return x + y;
  if (strcmp(op, "-") == 0)
    return x - y;
  if (strcmp(op, "*") == 0)
    return x * y;
  if (strcmp(op, "/") == 0)
    return x / y;
  if (strcmp(op, "%") == 0)
    return x % y;
  if (strcmp(op, "^") == 0)
    return pow(x, y);
  if (strcmp(op, "min") == 0)
    return x < y ? x : y;
  if (strcmp(op, "max") == 0)
    return x > y ? x : y;

  return 0;
}

long eval(mpc_ast_t *t) {
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  char *op = t->children[1]->contents;

  long x = eval(t->children[2]);

  int i = 3;

  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}
