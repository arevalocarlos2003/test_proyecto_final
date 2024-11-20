#include "tree.h"

// insert methods
void Tree::insert(const Person &value) { insertRecursive(this->root, value); }

void Tree::insertRecursive(Node *&node, Person value) {
  if (!node) {
    node = new Node(value);
  } else if (value.gender == 'f') {
    insertRecursive(node->left, value);
  } else if (value.gender == 'm') {
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

void Tree::inorderPersonVector(std::vector<Person> &memberVector) const {
  inorderPersonRecursiveVector(this->root, memberVector);
  std::cout << std::endl;
}

void Tree::inorderPersonRecursiveVector(Node *node,
                                        std::vector<Person> &nodes) const {
  if (node == nullptr) {
    return;
  }
  inorderPersonRecursiveVector(node->left, nodes);
  nodes.push_back(node->data);
  inorderPersonRecursiveVector(node->right, nodes);
}

// Print2D
void Tree::print2D() const {
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

  if (subtree->root == nullptr) {
    std::cout << std::endl
              << "\x1b[31mMember with id: " << targetPosition
              << " not found\x1b[0m" << std::endl
              << std::endl;
    return;
  }

  if ((newMember.gender == 'm') && (subtree->root->data.father != -1)) {
    std::cout << std::endl
              << "\x1b[33mThis member already has a father\x1b[0m" << std::endl
              << std::endl;
    return;
  }

  if ((newMember.gender == 'f') && (subtree->root->data.mother != -1)) {
    std::cout << std::endl
              << "\x1b[33mThis member already has a mother\x1b[0m" << std::endl
              << std::endl;
    return;
  }

  if (subtree == nullptr) {
    std::cout << "\x1b[31mTarget family member not found\x1b[0m" << std::endl;
    return;
  }
  root->setLastMember(root->getLastMember() + 1);
  newMember.id = root->getLastMember();
  subtree->insert(newMember);
}

void InsertFamilyMemberFromVector(Tree *&root, int targetPosition,
                                  Person newMember, int id) {
  Tree *subtree = new Tree();
  subtree->root = root->findSubTree(targetPosition);

  newMember.id = id;

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
  targetID = intInputHandler();
  return targetID;
}

struct Node *SearchByID(std::vector<Node *> &inorderVector, int targetID) {
  auto it = std::find_if(
      inorderVector.begin(), inorderVector.end(),
      [&](Node *&currentNode) { return currentNode->data.id == targetID; });

  if (*it == nullptr) {
    std::cout << std::endl << "\x1b[31mNot Found\x1b[0m" << std::endl;
    return nullptr;
  }

  return *it;
}

struct Person SearchPersonByID(std::vector<Person> &inorderVector,
                               int targetID) {
  auto it = std::find_if(
      inorderVector.begin(), inorderVector.end(),
      [&](Person &currentNode) { return currentNode.id == targetID; });

  if (it == inorderVector.end()) {
    return {};
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

  std::cout << "gender: " << std::endl;
  newMember.gender = genderInputHandler();

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
  const int kMaxSpace = 15;
  std::sort(inorderNodesCollection.begin(), inorderNodesCollection.end());
  Person currentPerson;
  std::cout << std::endl
            << std::left << std::setw(kMaxSpace) << "id: " << std::left
            << std::setw(kMaxSpace) << "first name" << std::left
            << std::setw(kMaxSpace) << "last name" << std::endl;
  for (size_t i = 0; i < inorderNodesCollection.size(); ++i) {
    currentPerson = inorderNodesCollection[i]->data;
    std::cout << std::left << std::setw(kMaxSpace) << currentPerson.id
              << std::left << std::setw(kMaxSpace) << currentPerson.first_name
              << std::left << std::setw(kMaxSpace) << currentPerson.last_name
              << std::endl;
  }
}

Tree *BuildTreeFromVector(std::vector<Person> &personCollection) {
  std::sort(personCollection.begin(), personCollection.end());
  Person currentMember;
  Person mother;
  Person father;
  // Inserts root
  Tree *treeFromVector = new Tree(personCollection[0]);
  int lastMember = 0;

  for (size_t i = 0; i < personCollection.size(); ++i) {
    currentMember = personCollection[i];
    if (currentMember.father != -1) {
      father = SearchPersonByID(personCollection, currentMember.father);
      InsertFamilyMemberFromVector(treeFromVector, currentMember.id, father,
                                   currentMember.father);
    }
    if (currentMember.mother != -1) {
      mother = SearchPersonByID(personCollection, currentMember.mother);
      InsertFamilyMemberFromVector(treeFromVector, currentMember.id, mother,
                                   currentMember.mother);
    }
  }

  if (currentMember.id > lastMember) lastMember = currentMember.id;
  if (father.id > lastMember) lastMember = father.id;
  if (mother.id > lastMember) lastMember = mother.id;
  treeFromVector->setLastMember(lastMember);

  return treeFromVector;
}

// Delete methods
void Tree::deleteTree() { this->deleteTreeRecursive(this->root); }

void Tree::deleteTreeRecursive(Node *&root) {
  if (root == nullptr) return;

  deleteTreeRecursive(root->left);
  deleteTreeRecursive(root->right);
  // std::cout << "Deleting node: " << root->data << std::endl;
  delete root;
}

// tree.cc
void Tree::deleteSubTree(Node *subTreeRoot) {
  if (!subTreeRoot)
    return;  // Si el subárbol es nulo, no hay nada que eliminar.

  // Llamadas recursivas para eliminar los hijos izquierdo y derecho.
  deleteTreeRecursive(subTreeRoot->left);
  deleteTreeRecursive(subTreeRoot->right);

  // Desvincular del árbol original (si es necesario).
  if (root == subTreeRoot) {
    root = nullptr;  // Si se elimina la raíz, el árbol queda vacío.
  } else {
    Node *parent = findParent(root, subTreeRoot);
    if (parent) {
      if (parent->left == subTreeRoot) {
        parent->left = nullptr;
        parent->data.mother = -1;
      }
      if (parent->right == subTreeRoot) {
        parent->right = nullptr;
        parent->data.father = -1;
      }
    }
  }

  // Eliminar el nodo actual.
  delete subTreeRoot;
}

void Tree::deleteMember(int targetID) {
  // Buscar el subárbol con la raíz que contiene el ID especificado.
  Node *subTreeRoot = findSubTree(targetID);

  if (!subTreeRoot) {
    std::cout << "Member with ID " << targetID << " not found." << std::endl;
    return;
  }

  // Seleccionar el nodo para reemplazar la raíz
  Node *replacement = nullptr;

  // Reglas para seleccionar el reemplazo según el género
  if (subTreeRoot->data.gender == 'm' && subTreeRoot->right &&
      subTreeRoot->right->data.gender == 'm') {
    replacement = subTreeRoot->right;  // Reemplazar con el hijo derecho.
  } else if (subTreeRoot->data.gender == 'f' && subTreeRoot->left &&
             subTreeRoot->left->data.gender == 'f') {
    replacement = subTreeRoot->left;  // Reemplazar con la hija izquierda.
  }

  // Buscar el padre del nodo a eliminar
  Node *parent = findParent(root, subTreeRoot);

  // Ajustar conexiones del padre
  if (parent) {
    if (parent->left == subTreeRoot) {
      parent->left = replacement;
    } else if (parent->right == subTreeRoot) {
      parent->right = replacement;
    }
  } else if (root == subTreeRoot) {
    // Caso especial: la raíz del árbol principal está siendo eliminada.
    root = replacement;
  }

  // Ajustar las conexiones del reemplazo
  if (replacement) {
    if (replacement == subTreeRoot->left) {
      replacement->right = subTreeRoot->right;  // Conectar hijo derecho.
    } else if (replacement == subTreeRoot->right) {
      replacement->left = subTreeRoot->left;  // Conectar hijo izquierdo.
    }
  }

  // Liberar memoria del nodo eliminado
  delete subTreeRoot;

  std::cout << "Member with ID " << targetID << " has been deleted."
            << std::endl;
}

// Encuentra el padre de un nodo dado.
Node *Tree::findParent(Node *current, Node *target) {
  if (!current || current == target) return nullptr;

  if (current->left == target || current->right == target) {
    return current;  // Se encontró el padre.
  }

  // Buscar recursivamente en los hijos.
  Node *leftParent = findParent(current->left, target);
  if (leftParent) return leftParent;

  return findParent(current->right, target);
}
