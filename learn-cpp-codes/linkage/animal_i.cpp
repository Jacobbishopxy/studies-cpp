
#include "animal_i.h"

#include <stdio.h>

namespace internal_linkage
{

void call_me()
{
  printf("const int i=%d, static int animals = %d\n", i_i, animals_i);
  printf("in animal_i.cpp &i = %p, &animals = %p\n", &i_i, &animals_i);
}

} // namespace internal_linkage
