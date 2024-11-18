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

  if (node->data == value) {
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
}
  // subtree_root->insert(newMember);



// FUnction Delete 
void Tree::deleteMember(const Person &targetMember) {
  root = Tree::eraseMemberConected(root, targetMember);
}

Node *Tree::eraseMemberConected(Node* node, const Person &targetMember){
if (node == nullptr)
{
    std::cout<<"There is no node to delete"<<std::endl;
    return nullptr;
}

//Looking for the id in order to delete the member inorder
if (targetMember.id < node->data.id){
    node->left = eraseMemberConected(node->left, targetMember);
}
else if (targetMember.id > node->data.id){
    node->right = eraseMemberConected(node->right, targetMember);
}
//Once it founds the Nodo 
else{
if (node->left == nullptr){
    Node *temp = node->right;
    delete node;
    return temp;
}
else if(node->right == nullptr){
 Node *temp = node->left;
 delete node;
 return temp;
}

Node *temp = minNode(node->right);
node->data = temp->data;
node->right = eraseMemberConected(node->right, temp->data);
}
return node;
};
//changing the side of the nodo
Node *Tree::minNode(Node *node){
    Node *current = node;
    while (current && current->left !=nullptr){
        current = current->left;
    }
    return current;
}

//Function fixed relation based on the ID 'Not completed'
void Tree::RelationFixed(Node* node, const Person& memberDelated) {
  if (node != nullptr){ 
    return;
  }
  
  if (node->data.genre == 'm'){
    RelationFixed(node, memberDelated);
  }

  RelationFixed(node->left, memberDelated);
  RelationFixed(node->right, memberDelated);
}

void Tree::RelationSiblings(Node* node, const Person& memberDelated) {
  if (memberDelated.genre == 'm' && node->data.genre == 'm') {
    node->data.mother -= 1;
  } else if (memberDelated.genre == 'f' && node->data.genre == 'f') {
    node->data.father -= 1; 
  }
}