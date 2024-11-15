#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>

#include "person.h"

struct Person;

class Node {
 public:
  Person data;
  Node *left;
  Node *right;

  Node(Person value) {
    this->data = value;
    this->left = nullptr;
    this->right = nullptr;
  }

  Node() {
    this->left = nullptr;
    this->right = nullptr;
  }
};

class Tree {
 public:
  Node *root;
  Tree() {
    this->lastMember = 0;
    this->currentLevel = 0;
  }
  ~Tree() {}

  void insert(const Person &value);
  void inorder() const;
  void inorderVector(std::vector<Node *> &nodes) const;
  void print2D() const;

  void setLastMember(int lastMember) { this->lastMember = lastMember; }
  int getLastMember() { return this->lastMember; }
  void setCurrentLevel(int level) { this->currentLevel = level; }
  int getCurrentLevel() { return this->currentLevel; }

  Node *find(const Person &value) const;

 private:
  int lastMember;
  int currentLevel;

  void insertRecursive(Node *&node, Person value);
  void inorderRecursive(Node *node) const;
  void inorderRecursiveVector(Node *node, std::vector<Node *> &nodes) const;
  void print2DRecursive(Node *root, int space) const;
  Node *findRecursive(Node *node, const Person &value) const;
};

// Encuentra el nivel de un nodo en el árbol.


void InsertFamilyMember(Tree *&root, Person targetPosition, Person newMember);

#endif  // TREE_H