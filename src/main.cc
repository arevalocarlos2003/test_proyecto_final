#include <algorithm>
#include <iostream>

#include "tree.h"

int main(int argc, char const *argv[]) {
  int option = 0;

  Person currentMember = {0, "Carlos", "Arevalo", 'm', -1, -1};
  Person targetMember;
  std::vector<Node *> inorderNodes;
  Tree *root = new Tree();
  root->insert(currentMember);

  do {
  } while (option != 8);

  delete root;
  return 0;
}
