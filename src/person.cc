#include "person.h"

std::ostream &operator<<(std::ostream &os, const Person &person) {
  os << "[" << person.id << "| " << person.first_name << "| "
     << person.last_name << "| " << person.genre << "]";
  return os;
}

void printPerson(const Person &person) {
  std::cout << std::endl << "\x1b[35mFamily Member Data\x1b[0m" << std::endl;
  std::cout << "id: " << person.id << std::endl;
  std::cout << "first name: " << person.first_name << std::endl;
  std::cout << "last name: " << person.last_name << std::endl;
  std::cout << "genre: " << person.genre << std::endl;
  std::cout << "father id: " << person.father << std::endl;
  std::cout << "mother id: " << person.mother << std::endl;
  std::cout << std::endl << std::endl;
}