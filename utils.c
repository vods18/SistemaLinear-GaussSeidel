#include "utils.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>


void clean_fgets(char *pos) { //função para "limpar" string
  strtok(pos, "\n");
}