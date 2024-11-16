#ifndef PERSON_H
#define PERSON_H

#include <iostream>

struct Person {
  int id;
  std::string first_name;
  std::string last_name;
  char genre;
  int father;
  int mother;

  bool operator==(const Person &other) const {
    return (id == other.id) && (first_name == other.first_name) &&
           (last_name == other.last_name) && (genre == other.genre);
  }

  bool operator<(const Person &other) const { return id < other.id; }
};

std::ostream &operator<<(std::ostream &os, const Person &person);
void printPerson(const Person &person);
#endif  // PERSON_H