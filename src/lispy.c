#include <editline/readline.h>

#include "eval.h"
#include "lispy.h"
#include "mpc.h"

void lispy() {
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *String = mpc_new("string");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT, "\
    number   : /-?[0-9]+/;\
    string   : /\"[A-Za-z0-9]*\"/;\
    operator : '+' | '-' | '*' | '/' | '^' | '%';\
    expr     : <number> | <string> | '(' <operator> <expr>+ ')';\
    lispy    : /^/ <operator> <expr>+ /$/;\
  ",
            Number, String, Operator, Expr, Lispy);

  while (1) {
    char *input = readline("Lispy> ");

    add_history(input);

    mpc_result_t r;

    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
}
