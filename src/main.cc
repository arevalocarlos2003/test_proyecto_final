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

  Node *node = nullptr;
  Tree *subTree = nullptr;
  std::string kinshipTitles;
  std::string aux_name;
  int currentLevel = 0;

  do {
    node = nullptr;
    subTree = nullptr;
    target = 0;
    inorderNodes.clear();
    inorderNodesSubVector.clear();
    root->updateRelations();
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
        root->inorderVector(inorderNodes);
        for (auto element : inorderNodes) {
          printPerson(element->data);
        }
        break;

      case 3:
        do {
          inorderNodesSubVector.clear();
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

      case 5:
        std::cout << std::endl
                  << "\x1b[32mPrint relations\x1b[0m" << std::endl
                  << std::endl;
        root->inorderVector(inorderNodes);
        std::cout << std::endl
                  << "\x1b[32mFrom Member\x1b[0m" << std::endl
                  << std::endl;
        target = GetTargetIDFromKeyBoard();
        subTree = new Tree();
        subTree->root = SearchByID(inorderNodes, target);
        aux_name = subTree->root->data.first_name;
        std::cout << "Member get: " << aux_name << std::endl;
        std::cout << std::endl
                  << "\x1b[32mTo Member\x1b[0m" << std::endl
                  << std::endl;
        target = GetTargetIDFromKeyBoard();
        currentLevel =
            subTree->findLevel(SearchByID(inorderNodes, target)->data);
        if (currentLevel == -1) {
          std::cout << std::endl
                    << "\x1b[31mNot Found\x1b[0m" << std::endl
                    << std::endl;
          break;
        }

        if (SearchByID(inorderNodes, target)->data.genre == 'm') {
          kinshipTitles = "father";
        } else if (SearchByID(inorderNodes, target)->data.genre == 'f') {
          kinshipTitles = "mother";
        }

        if (currentLevel >= 2) {
          kinshipTitles.insert(0, "Grand");
        }

        if (currentLevel > 2) {
          for (int i = 0; i < currentLevel - 2; ++i) {
            kinshipTitles.insert(0, "great-");
          }
        }

        std::cout << SearchByID(inorderNodes, target)->data.first_name
                  << " is: " << aux_name << " " << kinshipTitles << std::endl;

        break;

      default:
        break;
    }
  } while (option != 8);

  delete root;
  return 0;
}
