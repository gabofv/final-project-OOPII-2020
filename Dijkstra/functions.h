#pragma once
#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

template <typename T>
T t_abs(T a) {
  return a<0? -1*a : a;
}