#pragma once

#include <unordered_map>

using namespace std;

// Implemented for returning two containers through 
// dijkstra function
template <typename id, typename w>
struct return_t {
  unordered_map<id, w> d;
  unordered_map<id, id> p;
  return_t(unordered_map<id, w> &d, unordered_map<id, id> &p) : d(d), p(p) {}
  ~return_t() = default;
};