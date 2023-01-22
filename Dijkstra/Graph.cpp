#include "Graph.h"

using namespace std;

//---------------------------------

// Random weight given to a node
// where each node represents an intersection
// of the California road network

// Intersection...
// With traffic lights (WL)
// With no traffic lights (NL)
// Ratio of weight distribution:
// WL:NL -> 1:2.2 -> 5:11
// Unit of weight -> seconds

random_device rd; 
mt19937 gen(rd()); 

// ¿With or without traffic lights?
uniform_int_distribution<> distr(0, 16);
// WL
uniform_real_distribution<> distr_CS(30, 90);
// NL
uniform_real_distribution<> distr_SS(4, 5);


int weights[] = {5, 11};

int choice () {
  int rnd = distr(gen);
  int ans;
  for(int i=0; i<2; i++) {
    if(rnd < weights[i]) return i;
    rnd -= weights[i];
  }
  // *
  return true;
}