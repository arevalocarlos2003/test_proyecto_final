#include "person.h"

std::ostream &operator<<(std::ostream &os, const Person &person) {
  os << "[" << person.id << "| " << person.first_name << "| "
     << person.last_name << "| " << person.gender << "]";
  return os;
}

void printPerson(const Person &person) {
  std::cout << std::endl
            << "\x1b[33mFamily Member Data\x1b[0m" << std::endl
            << std::endl;
  const int kMaxSpace = 15;
  std::string father =
      (person.father == -1) ? "-- none --" : std::to_string(person.father);
  std::string mother =
      (person.mother == -1) ? "-- none --" : std::to_string(person.mother);
  std::cout << std::left << std::setw(kMaxSpace) << "ID" << std::left
            << std::setw(kMaxSpace) << "First Name" << std::left
            << std::setw(kMaxSpace) << "Last Name" << std::left
            << std::setw(kMaxSpace) << "Gender" << std::left
            << std::setw(kMaxSpace) << "Father ID" << std::left
            << std::setw(kMaxSpace) << "Mother ID" << std::endl;
  std::cout << std::left << std::setw(kMaxSpace) << person.id << std::left
            << std::setw(kMaxSpace) << person.first_name << std::left
            << std::setw(kMaxSpace) << person.last_name << std::left
            << std::setw(kMaxSpace) << person.gender << std::left
            << std::setw(kMaxSpace) << father << std::left
            << std::setw(kMaxSpace) << mother << std::endl
            << std::endl;
}