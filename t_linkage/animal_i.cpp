
#include "animal_i.h"

#include <stdio.h>

namespace internal_linkage
{

  void call_me()
  {
    printf("const int i=%d, static int animals = %d\n", i, animals);
    printf("in Animal.cpp &i = %p,&animals = %p\n", &i, &animals);
  }

  void call()
  {

    // internal linkage
    printf("<internal linkage>");
    printf("before change animals:");
    call_me();
    animals = 2;
    printf("after change animals:");
    printf("animals = %d\n", animals);
    call_me();

    printf("in main.cpp &i = %p, &animals = %p\n", &i, &animals);
  }
}
