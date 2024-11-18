#include "iohandlers.h"

int intInputHandler() {
  std::string wrongInput;
  int input = 0;
  while (true) {
    std::cin >> input;
    if (!std::cin.good()) {
      std::cin.clear();
      std::cin >> wrongInput;
      std::cout << "Debes ingresar un numero ingresaste: [" << wrongInput << "]"
                << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else
      break;
  }
  return input;
}

char genderInputHandler() {
  char gender = '0';
  while (true) {
    std::cin >> gender;
    if (gender == 'm') break;
    if (gender == 'f') break;
    std::cout << "Debes ingresar un caracter ya sea m o f ingresaste: "
              << gender << std::endl;
  }
  return gender;
}