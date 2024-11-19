#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "iohandlers.h"
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
  Tree(Person value) {
    this->root = new Node(value);
    this->lastMember = 0;
    this->currentLevel = 0;
  }
  Tree() {
    this->lastMember = 0;
    this->currentLevel = 0;
  }
  ~Tree() {}

  void insert(const Person &value);
  void deleteTree();
  void updateRelations() const;
  void inorderVector(std::vector<Node *> &nodes) const;
  void inorderPersonVector(std::vector<Person> &nodes) const;
  void print2D() const;

  void setLastMember(int lastMember) { this->lastMember = lastMember; }
  int getLastMember() { return this->lastMember; }
  void setCurrentLevel(int level) { this->currentLevel = level; }
  int getCurrentLevel() { return this->currentLevel; }

  Node *findSubTree(const int &value) const;
  int findLevel(const Person &value) const;

 private:
  int lastMember;
  int currentLevel;

  void insertRecursive(Node *&node, Person value);
  void deleteTreeRecursive(Node *&node);
  void updateRelationsRecursive(Node *node) const;
  void inorderRecursiveVector(Node *node, std::vector<Node *> &nodes) const;
  void inorderPersonRecursiveVector(Node *node,
                                    std::vector<Person> &nodes) const;
  void print2DRecursive(Node *root, int space) const;
  Node *findSubTreeRecursive(Node *node, const int &value) const;
  int findLevelRecursive(Node *root, const Person &value, int level) const;
};

void InsertFamilyMember(Tree *&root, int targetPosition, Person newMember);
void InsertFamilyMemberFromVector(Tree *&root, int targetPosition,
                                  Person newMember, int id);

// Search Functions
int GetTargetIDFromKeyBoard();
struct Node *SearchByID(std::vector<Node *> &inorderVector, int targetID);
struct Person SearchPersonByID(std::vector<Person> &inorderVector,
                               int targetID);
std::vector<Node *> SearchByName(std::vector<Node *> &inorderVector,
                                 struct Person targetMember);
std::vector<Node *> SearchByLastName(std::vector<Node *> &inorderVector,
                                     struct Person targetMember);

// Create From KeyBoard Functions
struct Person CreateMemberFromKeyBoard(Tree *root);
struct Person GetMemberNamesFromKeyBoard();

void PrintInorderNodes(std::vector<Node *> inorderNodesCollection);

Tree *BuildTreeFromVector(std::vector<Person> &personCollection);

#endif  // TREE_H