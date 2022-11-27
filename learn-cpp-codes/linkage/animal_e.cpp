#include "animal_e.h"
#include <stdio.h>

namespace external_linkage
{

int animals_e = 6;
const int i_e = 3;

void call_me()
{
  printf("const int i=%d, static int animals = %d\n", i_e, animals_e);
  printf("in animal_e.cpp &i = %p, &animals = %p\n", &i_e, &animals_e);
}

} // namespace external_linkage