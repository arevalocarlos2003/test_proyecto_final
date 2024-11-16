#include "cli_menu.h"

void ShowCLIMenuOptions() {
  std::cout << std::endl
            << "\x1b[33mMain Menu\x1b[0m" << std::endl
            << std::endl;
  std::cout << "1. Insert Family Members" << std::endl;
  std::cout << "2. Delete Family Members" << std::endl;
  std::cout << "3. Search Family Member" << std::endl;
  std::cout << "4. Family Tree Visualization" << std::endl;
  std::cout << "5. Print Relation Between Family Members" << std::endl;
  std::cout << "6. Import Family Tree" << std::endl;
  std::cout << "7. Export Family Tree" << std::endl;
  std::cout << "8. \x1b[31mExit\x1b[0m" << std::endl << std::endl;
}

void ShowCLISearchOptions() {
  std::cout << std::endl
            << "\x1b[31mSearch Options\x1b[0m" << std::endl
            << std::endl;
  std::cout << "1. Search By ID" << std::endl;
  std::cout << "2. Search By first name" << std::endl;
  std::cout << "3. Search By last name" << std::endl;
  std::cout << "4. Back Main Menu" << std::endl << std::endl;
}