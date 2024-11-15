#ifndef PERSON_H
#define PERSON_H

#include <iostream>

struct Person {
  int id;
  std::string name;
  char genre;
  int relation;

  bool operator==(const Person &other) const {
    return (id == other.id) && (name == other.name) && (genre == other.genre);
  }
};

std::ostream &operator<<(std::ostream &os, const Person &person);

#endif  // PERSON_H