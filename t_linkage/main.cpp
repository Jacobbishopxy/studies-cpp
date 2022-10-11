
#include "animal_i.h"
#include "animal_e.h"

#include <stdio.h>

int main()
{

  internal_linkage::call();

  external_linkage::call();

  return 0;
}
