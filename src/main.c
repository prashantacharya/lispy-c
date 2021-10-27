#include <editline/readline.h>
#include <stdio.h>
#include <stdlib.h>

#include "lispy.h"
#include "mpc.h"
#include "utils.h"

int main(int argc, char **argv) {
  printInfo();

  lispy();

  return 0;
}
