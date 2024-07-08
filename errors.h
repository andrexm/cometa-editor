#pragma once

#include <stdio.h>
#include <stdlib.h>

// exit the program when an error is found
void die(char *msg) {
  perror(msg);
  exit(1);
}
