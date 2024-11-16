#include <algorithm>
#include <iostream>

#include "cli_menu.h"
#include "tree.h"

int main(int argc, char const *argv[]) {
  int option = 0;

  Person currentMember = {0, "Carlos", "Arevalo", 'm', -1, -1};
  Person targetMember;
  std::vector<Node *> inorderNodes;
  Tree *root = new Tree();
  root->insert(currentMember);

  do {
    ShowCLIMenuOptions();
    std::cout << "\x1b[34mOption: \x1b[0m";
    std::cin >> option;
    switch (option) {
      case 1:
        /* code */
        break;

      case 2:
        /* code */
        break;

      case 3:
        do {
          ShowCLISearchOptions();
          std::cin >> option;
          switch (option) {
            case 1:
              /* code */
              break;

            case 2:
              /* code */
              break;

            case 3:
              /* code */
              break;
          }
        } while (option != 4);
        break;

      default:
        break;
    }
  } while (option != 8);

  delete root;
  return 0;
}
