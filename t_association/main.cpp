#include <iostream>

#include "car_driver.h"
#include "doctor_patient.h"

void doctor_patient() {
  Patient dave{"Dave"};
  Patient frank{"Frank"};
  Patient betsy{"Betsy"};

  Doctor james{"James"};
  Doctor scott{"Scott"};

  james.addPatient(dave);

  scott.addPatient(dave);
  scott.addPatient(betsy);

  std::cout << james << std::endl;
  std::cout << scott << std::endl;
  std::cout << dave << std::endl;
  std::cout << frank << std::endl;
  std::cout << betsy << std::endl;
}

void car_driver() {
  Driver d{"Franz", 17};

  Car* car{CarLot::getCar(d.getCarId())};

  if (car)
    std::cout << d.getName() << " is driving a " << car->getName() << std::endl;
  else
    std::cout << d.getName() << " couldn't find his car" << std::endl;
}

int main() {
  doctor_patient();

  car_driver();

  return 0;
}
