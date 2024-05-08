#pragma once
#include <iostream>
#include <vector>
#include "SortingAlgorithm.hpp"

using namespace std;

template <typename T>
void RandomVector(vector<T>& v,
                  unsigned int& size,
                  unsigned int& mode);

template <typename T>
void SortCompare(vector<T> v);
