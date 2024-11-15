#include "person.h"

std::ostream &operator<<(std::ostream &os, const Person &person) {
  os << "[" << person.id << "| " << person.name << "| " << person.genre << "]";
  return os;
}