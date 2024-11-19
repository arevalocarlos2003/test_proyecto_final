#include <algorithm>
#include <iostream>
#include <limits>

#include "cli_menu.h"
#include "tree.h"

int main(int argc, char const *argv[]) {
  int option = 0;
  int target = 0;
  std::string fileName;

  Person currentMember = {0, "Carlos", "Arevalo", 'm', -1, -1};
  Person targetMember;
  Person newMember;

  std::vector<Node *> inorderNodes;
  std::vector<Node *> inorderNodesSubVector;
  std::vector<Person> inorderPerson;
  Tree *root = new Tree(currentMember);

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
    option = intInputHandler();

    switch (option) {
      case 1:
        root->print2D();
        std::cout << std::endl
                  << "\x1b[32mInsert Family Member\x1b[0m" << std::endl
                  << std::endl;
        std::cout << std::endl
                  << "\x1b[33mTarget ID\x1b[0m" << std::endl
                  << std::endl;
        target = GetTargetIDFromKeyBoard();
        std::cout << std::endl;
        newMember = CreateMemberFromKeyBoard(root);
        InsertFamilyMember(root, target, newMember);
        break;

      case 2:
        inorderPerson.clear();
        root->inorderPersonVector(inorderPerson);
        std::sort(inorderPerson.begin(), inorderPerson.end());
        root->deleteTree();
        root = BuildTreeFromVector(inorderPerson);
        root->updateRelations();
        root->print2D();
        break;

      case 3:
        do {
          inorderNodes.clear();
          inorderNodesSubVector.clear();
          ShowCLISearchOptions();
          option = intInputHandler();
          switch (option) {
            case 1:
              root->inorderVector(inorderNodes);
              std::cout << "Search By ID" << std::endl << std::endl;
              node = new Node();
              node = SearchByID(inorderNodes, GetTargetIDFromKeyBoard());
              if (node == nullptr) {
                break;
              }
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
        std::cout << std::endl
                  << "\x1b[32mTree Visualization\x1b[0m" << std::endl
                  << std::endl;
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

      case 6:
        inorderPerson.clear();
        ListCurrentPathFiles();
        std::cin.ignore();
        std::cout << std::endl << "filename: ";
        std::getline(std::cin, fileName);

        GetInorderPeopleFromFile(fileName, inorderPerson);
        std::sort(inorderPerson.begin(), inorderPerson.end());
        root->deleteTree();
        root = BuildTreeFromVector(inorderPerson);
        root->updateRelations();
        std::cout << std::endl
                  << "\x1b[33mImported data\x1b[0m" << std::endl
                  << std::endl;
        root->print2D();
        break;

      case 7:
        inorderPerson.clear();
        root->inorderPersonVector(inorderPerson);
        std::cin.ignore();
        do {
          std::cout << "Enter name for the new family tree export: ";
          std::getline(std::cin, fileName);
        } while (!VerifyFileNameAvailability(fileName));
        ExportInorderPeopleFromVector(fileName, inorderPerson);
        break;

      default:
        break;
    }
  } while (option != 8);

  root->deleteTree();
  delete root;
  return 0;
}