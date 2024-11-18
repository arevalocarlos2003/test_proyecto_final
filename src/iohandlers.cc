#include "iohandlers.h"

int intInputHandler() {
  std::string wrongInput;
  int input = 0;
  while (true) {
    std::cin >> input;
    if (!std::cin.good()) {
      std::cin.clear();
      std::cin >> wrongInput;
      std::cout << "Debes ingresar un numero ingresaste: [" << wrongInput << "]"
                << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else
      break;
  }
  return input;
}

char genderInputHandler() {
  char gender = '0';
  while (true) {
    std::cin >> gender;
    if (gender == 'm') break;
    if (gender == 'f') break;
    std::cout << "Debes ingresar un caracter ya sea m o f ingresaste: "
              << gender << std::endl;
  }
  return gender;
}

// File management
bool ListCurrentPathFiles() {
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::cout << "Files in this directory: " << currentPath << std::endl;
  int numberOfFiles = 0;

  for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
    std::string fileName = entry.path().filename().string();
    if (entry.is_regular_file() &&
        fileName.rfind(".csv") == fileName.size() - 4) {
      std::cout << "|-- \x1b[32m" << fileName << "\x1b[0m" << std::endl;
      numberOfFiles++;
    }
  }

  return numberOfFiles == 0;
}

void GetInorderPeopleFromFile(const std::string& fileName,
                              std::vector<Person>& personCollection) {
  std::fstream peopleFile;
  peopleFile.open(fileName, std::ios::in);

  if (!peopleFile.is_open()) {
    std::cout << std::endl
              << "\x1b[31mError trying opening this file: \x1b[0m" << fileName
              << std::endl;
  }

  std::string currentLine;
  Person currentPerson;
  std::string auxConvertion;
  while (std::getline(peopleFile, currentLine)) {
    std::stringstream currentLineStream(currentLine);
    std::getline(currentLineStream, auxConvertion, ',');
    currentPerson.id = std::stoi(auxConvertion);
    auxConvertion.clear();
    std::getline(currentLineStream, currentPerson.first_name, ',');
    std::getline(currentLineStream, currentPerson.last_name, ',');
    std::getline(currentLineStream, auxConvertion, ',');
    currentPerson.genre = auxConvertion[0];
    auxConvertion.clear();
    std::getline(currentLineStream, auxConvertion, ',');
    currentPerson.father = std::stoi(auxConvertion);
    auxConvertion.clear();
    std::getline(currentLineStream, auxConvertion, ',');
    currentPerson.mother = std::stoi(auxConvertion);
    std::cout << currentPerson << std::endl;
    personCollection.push_back(currentPerson);
  }

  peopleFile.close();
}