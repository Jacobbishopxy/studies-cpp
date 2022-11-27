#include "box_label_button.h"
#include "person_employee_teacher.h"

int main(int argc, char const* argv[])
{
  Teacher t{"Mary", 45, "Boo", 14.3, 8};

  Button button{};
  button.Box::setTopLeft({1, 1});
  button.Box::setBottomRight({10, 10});
  button.Label::setText("Username: ");
  button.Label::setFontSize(6);

  return 0;
}
