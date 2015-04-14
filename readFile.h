#pragma once

#include <string>
#include <vector>

std::vector<std::pair<std::vector<double>, std::vector<double>>> examples32;
std::vector<std::pair<std::vector<double>, std::vector<double>>> examples8;

std::vector<std::pair<std::vector<double>, std::vector<double>>>* readData32(std::string fp);
std::vector<std::pair<std::vector<double>, std::vector<double>>>* readData8(std::string fp);
void printData(std::vector<std::pair<std::vector<double>, std::vector<double>>> examples, int width, int numExamples);