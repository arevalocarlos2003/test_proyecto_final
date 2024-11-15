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

// inorder
void Tree::inorder() const {
  inorderRecursive(this->root);
  std::cout << std::endl;
}

void Tree::inorderRecursive(Node *node) const {
  if (node == nullptr) {
    return;
  }
  inorderRecursive(node->left);
  std::cout << node->data << " ";
  inorderRecursive(node->right);
}

// inorder vector
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
  for (int i = kSpace; i < space; i++) std::cout << "  ";
  if (root->left != nullptr || root->right != nullptr)
    std::cout << root->data << " <\n";
  else
    std::cout << root->data << "\n";
  print2DRecursive(root->left, space);
}

// find methods

Node *Tree::find(const Person &value) const {
  return findRecursive(root, value);
}

Node *Tree::findRecursive(Node *node, const Person &value) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->data.id == value.id) {
    return node;
  }

  Node *aux = findRecursive(node->left, value);

  if (aux == nullptr) {
    return findRecursive(node->right, value);
  }

  return aux;
}

void InsertFamilyMember(Tree *&root, Person targetPosition, Person newMember) {
  Tree *subtree = new Tree();
  subtree->root = root->find(targetPosition);

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

// find level methods
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