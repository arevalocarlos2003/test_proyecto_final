#include <iostream>

#include "tree.h"

struct Person CreateMember(Tree *root) {
  std::cout << std::endl
            << "\x1b[32mNew Member\x1b[0m" << std::endl
            << std::endl;

  struct Person newMember;
  newMember.id = 0;
  std::cout << "name: ";
  std::cin.ignore();
  std::getline(std::cin, newMember.name);
  std::cout << "f:(mom) m(dad): ";
  std::cin >> newMember.genre;
  newMember.relation = 0;
  std::cout << std::endl;
  return newMember;
}
struct Person addRelation(struct Person &id);
struct Person addRelation(struct Person &id){
  struct Person targetMember; 
  targetMember.relation = targetMember.id + 1;
  return targetMember;

};

struct Person GetTargetData() {
  std::cout << std::endl
            << "\x1b[33mTarget position\x1b[0m" << std::endl
            << std::endl;

  struct Person targetMember;
  std::cout << "id: ";
  std::cin >> targetMember.id;

  std::cout << "name: ";
  std::cin.ignore();
  std::getline(std::cin, targetMember.name);

  std::cout << "genre: ";
  std::cin >> targetMember.genre;
  targetMember.relation = targetMember.id +1;

  addRelation(targetMember);

  return targetMember;
}

int main(int argc, char const *argv[]) {
  int option = 0;

  Person currentMember = {0, "Carlos", 'm', 0};
  Person targetMember;
  Tree *root = new Tree();
  root->insert(currentMember);

  do {
    std::cout << "1. Visualization Tree" << std::endl;
    std::cout << "2. Add member" << std::endl;
    std::cout << "3. Search member" << std::endl;
    std::cout << "4. Delete member" << std::endl;
    std::cout << "8. exit" << std::endl;

    std::cin >> option;
    switch (option) {
      case 1:
        root->print2D();
        break;

      case 2:
        targetMember = GetTargetData();
        if (root->find(targetMember) == nullptr) {
          std::cout << "\x1b[31mNot found\x1b[0m" << std::endl << std::endl;
          break;
        }

        currentMember = CreateMember(root);
        InsertFamilyMember(root, targetMember, currentMember);
        break;

      case 3:
        targetMember = GetTargetData();
        if (root->find(targetMember) == nullptr) {
          std::cout << "Member: " << targetMember.name
                    << "\x1b[31m Not found\x1b[0m" << std::endl;
          break;
        }
        currentMember = root->find(targetMember)->data;
        std::cout << std::endl
                  << "\x1b[32mFound: \x1b[0m" << currentMember << std::endl;
        break;
      case 4:
      targetMember = GetTargetData();
      if (root->find(targetMember) == nullptr){
          std::cout << "Member not found" << std::endl;
          break;
        }
        root->deleteMember(targetMember);
        root->RelationSiblings(root->root, targetMember);
        std::cout << "Member deleted and relation adjusted" << std::endl;
      break;
      default:
        break;
    }
  } while (option != 8);

  delete root;
  return 0;
}
