#include "animal_e.h"
#include <stdio.h>

namespace external_linkage
{

  int animals = 8;
  const int i = 5;

  void call_me()
  {
    printf("const int i=%d, static int animals = %d\n", i, animals);
    printf("in Animal.cpp &i = %p,&animals = %p\n", &i, &animals);
  }

  void call()
  {

    // external linkage
    printf("<external linkage>");
    printf("before change animals:");
    call_me();
    animals = 2;
    printf("after change animals:");
    printf("animals = %d\n", animals);
    call_me();

    printf("in Feed.cpp &i = %p,&animals = %p\n", &i, &animals);
  }
}