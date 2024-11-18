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
  std::vector<Person> inorderNodes;
  Tree() { this->lastMember = 0; }
  ~Tree() {}

  void insert(const Person &value);
  void inorder() const;
  void print2D() const;

  void setLastMember(int lastMember) { this->lastMember = lastMember; }
  int getLastMember() { return this->lastMember; }
  Node *find(const Person &value) const;
  //eraseMember
  Node *minNode(Node *node);
  void deleteMember(const Person &target);
  Node *eraseMemberConected(Node* node, const Person &targetMember);
  void RelationFixed(Node* node, const Person &memberDelated);
  void RelationSiblings(Node* node, const Person &memberDelated);
  void ShowDELETESearchOptions();

  //Erase only the data not the node (leaving the id)
  Node *deleteData(Node* node, const Person &targetMember);
  Node *update_same_nodo(Node* node, const Person &targetMember);


 private:
  int lastMember;

  void insertRecursive(Node *&node, Person value);
  void inorderRecursive(Node *node) const;
  void print2DRecursive(Node *root, int space) const;
  Node *findRecursive(Node *node, const Person &value) const;
  };

void InsertFamilyMember(Tree *&root, Person targetPosition, Person newMember);

#endif  // TREE_H