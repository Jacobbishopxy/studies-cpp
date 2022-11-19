
#include "animal_i.h"
#include "animal_e.h"

#include <stdio.h>

// external linkage
void call_e()
{
  printf("<external linkage>");
  printf("before change animals:");
  external_linkage::call_me();
  external_linkage::animals_e = 2;
  printf("after change animals:");
  printf("animals = %d\n", external_linkage::animals_e);
  external_linkage::call_me();

  printf("in animal_e.cpp &i = %p, &animals = %p\n", &external_linkage::i_e, &external_linkage::animals_e);
}

// internal linkage
void call_i()
{
  printf("<internal linkage>");
  printf("before change animals:");
  internal_linkage::call_me();
  internal_linkage::animals_i = 2;
  printf("after change animals:");
  printf("animals = %d\n", internal_linkage::animals_i);
  internal_linkage::call_me();

  printf("in animal_i.cpp &i = %p, &animals = %p\n", &internal_linkage::i_i, &internal_linkage::animals_i);
}

int main()
{

  call_i();

  call_e();

  return 0;
}
