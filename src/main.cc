#include <algorithm>
#include <iostream>
#include <limits>

#include "cli_menu.h"
#include "tree.h"

int main(int argc, char const *argv[]) {
  int option = 0;
  int target = 0;

  Person currentMember = {0, "Carlos", "Arevalo", 'm', -1, -1};
  Person targetMember;
  Person newMember;

  std::vector<Node *> inorderNodes;
  Tree *root = new Tree();
  root->insert(currentMember);

  do {
    target = 0;
    inorderNodes.clear();
    ShowCLIMenuOptions();
    std::cout << "\x1b[34mOption: \x1b[0m";
    std::cin >> option;
    switch (option) {
      case 1:
        root->print2D();
        std::cout << std::endl
                  << "\x1b[35mInsert Family Member\x1b[0m" << std::endl;
        newMember = CreateMemberFromKeyBoard(root);
        target = GetTargetIDFromKeyBoard();
        InsertFamilyMember(root, target, newMember);
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
              root->inorderVector(inorderNodes);
              std::cout << "Search By ID" << std::endl << std::endl;
              Node *node = new Node(
                  SearchByID(inorderNodes, GetTargetIDFromKeyBoard())->data);
              printPerson(node->data);
              break;

              // case 2:
              //   /* code */
              //   break;

              // case 3:
              //   /* code */
              //   break;
          }
        } while (option != 4);
        break;

      case 4:
        root->print2D();
        break;

      default:
        break;
    }
  } while (option != 8);

  delete root;
  return 0;
}
