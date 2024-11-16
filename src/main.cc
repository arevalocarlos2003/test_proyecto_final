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
  std::vector<Node *> inorderNodesSubVector;
  Tree *root = new Tree();
  root->insert(currentMember);

  do {
    target = 0;
    inorderNodes.clear();
    inorderNodesSubVector.clear();
    ShowCLIMenuOptions();
    std::cout << "\x1b[34mOption: \x1b[0m";
    std::cin >> option;
    switch (option) {
      case 1:
        root->print2D();
        std::cout << std::endl
                  << "\x1b[35mInsert Family Member\x1b[0m" << std::endl;
        std::cout << "\x1b[33mTarget ID\x1b[0m" << std::endl;
        target = GetTargetIDFromKeyBoard();
        newMember = CreateMemberFromKeyBoard(root);
        InsertFamilyMember(root, target, newMember);
        break;

      case 2:
        /* code */
        break;

      case 3:
        do {
          inorderNodesSubVector.clear();
          Node *node = nullptr;
          ShowCLISearchOptions();
          std::cin >> option;
          switch (option) {
            case 1:
              root->inorderVector(inorderNodes);
              std::cout << "Search By ID" << std::endl << std::endl;
              node = new Node(
                  SearchByID(inorderNodes, GetTargetIDFromKeyBoard())->data);
              printPerson(node->data);
              break;
            case 2:
              root->inorderVector(inorderNodes);
              std::cout << std::endl
                        << "Search by member names" << std::endl
                        << std::endl;
              std::cin.ignore();
              std::getline(std::cin, targetMember.first_name);
              inorderNodesSubVector = SearchByName(inorderNodes, targetMember);

              if (inorderNodesSubVector.empty()) {
                std::cout << "\x1b[31mNo member was found that met the "
                             "condition.\x1b[0m"
                          << std::endl;
                break;
              }

              std::cout << std::endl
                        << "Members with this name" << std::endl
                        << std::endl;
              PrintInorderNodes(inorderNodesSubVector);
              node = new Node(
                  SearchByID(inorderNodesSubVector, GetTargetIDFromKeyBoard())
                      ->data);

              std::cout << "\x1b[33mFound By Name and ID\x1b[0m" << std::endl;
              printPerson(node->data);
              break;

            case 3:
              root->inorderVector(inorderNodes);
              std::cout << std::endl
                        << "Search by member last names" << std::endl
                        << std::endl;
              std::cin.ignore();
              std::getline(std::cin, targetMember.last_name);
              inorderNodesSubVector =
                  SearchByLastName(inorderNodes, targetMember);

              if (inorderNodesSubVector.empty()) {
                std::cout << "\x1b[31mNo member was found that met the "
                             "condition.\x1b[0m"
                          << std::endl;
                break;
              }

              std::cout << std::endl
                        << "\x1b[32mMembers with this last name\x1b[0m"
                        << std::endl
                        << std::endl;
              PrintInorderNodes(inorderNodesSubVector);
              node = new Node(
                  SearchByID(inorderNodesSubVector, GetTargetIDFromKeyBoard())
                      ->data);

              std::cout << "\x1b[33mFound By Last Name and ID\x1b[0m"
                        << std::endl;
              printPerson(node->data);
              break;
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
