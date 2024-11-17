#include "tree.h"

// insert methods
void Tree::insert(const Person &value) { insertRecursive(this->root, value); }

void Tree::insertRecursive(Node *&node, Person value) {
  if (!node) {
    node = new Node(value);
  } else if (value.genre == 'f') {
    insertRecursive(node->left, value);
  } else if (value.genre == 'm') {
    insertRecursive(node->right, value);
  }
}

// updateRelations
void Tree::updateRelations() const {
  updateRelationsRecursive(this->root);
  std::cout << std::endl;
}

void Tree::updateRelationsRecursive(Node *node) const {
  if (node == nullptr) {
    return;
  }
  updateRelationsRecursive(node->left);
  if (node->left != nullptr) node->data.mother = node->left->data.id;
  if (node->right != nullptr) node->data.father = node->right->data.id;
  updateRelationsRecursive(node->right);
}

// updateRelations vector
void Tree::inorderVector(std::vector<Node *> &nodes) const {
  inorderRecursiveVector(this->root, nodes);
  std::cout << std::endl;
}

void Tree::inorderRecursiveVector(Node *node,
                                  std::vector<Node *> &nodes) const {
  if (node == nullptr) {
    return;
  }
  inorderRecursiveVector(node->left, nodes);
  nodes.push_back(node);
  inorderRecursiveVector(node->right, nodes);
}

// Print2D
void Tree::print2D() const {
  std::cout << "\x1b[32mTree Visualization\x1b[0m" << std::endl << std::endl;
  print2DRecursive(this->root, 0);
  std::cout << std::endl << std::endl;
}

void Tree::print2DRecursive(Node *root, int space) const {
  if (root == nullptr) {
    return;
  }

  const int kSpace = 10;
  space += kSpace;

  print2DRecursive(root->right, space);
  std::cout << std::endl;
  for (int i = kSpace; i < space; i++) std::cout << "   ";
  if (root->left != nullptr || root->right != nullptr)
    std::cout << root->data << " <\n";
  else
    std::cout << root->data << "\n";
  print2DRecursive(root->left, space);
}

// findSubTree methods

Node *Tree::findSubTree(const int &target) const {
  return findSubTreeRecursive(root, target);
}

Node *Tree::findSubTreeRecursive(Node *node, const int &value) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->data.id == value) {
    return node;
  }

  Node *aux = findSubTreeRecursive(node->left, value);

  if (aux == nullptr) {
    return findSubTreeRecursive(node->right, value);
  }

  return aux;
}

void InsertFamilyMember(Tree *&root, int targetPosition, Person newMember) {
  Tree *subtree = new Tree();
  subtree->root = root->findSubTree(targetPosition);

  root->setLastMember(root->getLastMember() + 1);
  newMember.id = root->getLastMember();

  // if (subtree_root->root == nullptr) {
  if (subtree == nullptr) {
    std::cout << "\x1b[31mTarget family member not found\x1b[0m" << std::endl;
    return;
  }

  subtree->insert(newMember);

  // subtree_root->insert(newMember);
}

// findSubTree level methods
int Tree::findLevel(const Person &value) const {
  return findLevelRecursive(this->root, value, 0);
}

int Tree::findLevelRecursive(Node *node, const Person &value, int level) const {
  if (node == nullptr) {
    return -1;  // Devuelve -1 si el nodo no se encuentra.
  }

  if (node->data == value) {
    return level;
  }

  // Busca en el subárbol izquierdo.
  int leftLevel = findLevelRecursive(node->left, value, level + 1);
  if (leftLevel != -1) {
    return leftLevel;
  }

  // Si no se encuentra en la izquierda, busca en el derecho.
  return findLevelRecursive(node->right, value, level + 1);
}

// Search Functions
int GetTargetIDFromKeyBoard() {
  int targetID = 0;
  std::cout << "\x1b[33mtarget id: \x1b[0m";
  std::cin >> targetID;
  return targetID;
}

struct Node *SearchByID(std::vector<Node *> &inorderVector, int targetID) {
  auto it = std::find_if(
      inorderVector.begin(), inorderVector.end(),
      [&](Node *&currentNode) { return currentNode->data.id == targetID; });

  if (*it == nullptr) {
    std::cout << "\x1b[31mNot Found\x1b[0m" << std::endl;
    return nullptr;
  }

  return *it;
}

std::vector<Node *> SearchByName(std::vector<Node *> &inorderVector,
                                 struct Person targetMember) {
  if (inorderVector.empty()) {
    std::cout << "\x1b[31mThere are not members on the tree\x1b[0m"
              << std::endl;
    return {};
  }

  std::vector<Node *> subVector;

  for (auto &element : inorderVector) {
    if (element->data.first_name == targetMember.first_name) {
      subVector.push_back(element);
    }
  }

  std::sort(inorderVector.begin(), inorderVector.end());
  return subVector;
}

std::vector<Node *> SearchByLastName(std::vector<Node *> &inorderVector,
                                     struct Person targetMember) {
  if (inorderVector.empty()) {
    std::cout << "\x1b[31mThere are not members on the tree\x1b[0m"
              << std::endl;
    return {};
  }

  std::vector<Node *> subVector;

  for (auto &element : inorderVector) {
    if (element->data.last_name == targetMember.last_name) {
      subVector.push_back(element);
    }
  }

  std::sort(inorderVector.begin(), inorderVector.end());
  return subVector;
}

// Create functions
struct Person CreateMemberFromKeyBoard(Tree *root) {
  struct Person newMember;
  newMember.id = 0;

  std::cin.ignore();
  std::cout << "first name: " << std::endl;
  std::getline(std::cin, newMember.first_name);

  std::cout << "last name: " << std::endl;
  std::getline(std::cin, newMember.last_name);

  std::cout << "genre: " << std::endl;
  std::cin >> newMember.genre;

  newMember.father = -1;
  newMember.mother = -1;

  return newMember;
}

struct Person GetMemberNamesFromKeyBoard() {
  struct Person targetMember;
  std::cin.ignore();
  std::cout << "first name: " << std::endl;
  std::getline(std::cin, targetMember.first_name);

  std::cout << "first name: " << std::endl;
  std::getline(std::cin, targetMember.first_name);
  return targetMember;
}

void PrintInorderNodes(std::vector<Node *> inorderNodesCollection) {
  for (size_t i = 0; i < inorderNodesCollection.size(); ++i) {
    printPerson(inorderNodesCollection[i]->data);
  }
}