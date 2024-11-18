#ifndef IOHANDLERS_H
#define IOHANDLERS_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "person.h"
/* This user-defined library provides tools for managing files related to a
 * genealogical tree. It offers functions for importing and exporting tree data,
 * enabling the reading and writing of its structure in various formats.
 * Additionally, it includes handlers to manage specific input operations
 * efficiently.
 *
 * Copyright  (c) 2024 Carlos Arevalo
 * */
int intInputHandler();
char genderInputHandler();

// File management
bool ListCurrentPathFiles();
void GetInorderPeopleFromFile(const std::string& fileName,
                              std::vector<Person>& personCollection);

#endif  // IOHANDLERS_H