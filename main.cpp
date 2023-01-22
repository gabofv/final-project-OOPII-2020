/*
Objetivo: 
Estimación de ruta más corta en términos de tiempo
respecto al tiempo perdido por reducción de velocidad
en cada intersección. 

Integrantes:
- Gabriel Vásquez 100%
- Juan Sara 100%
- Juan Torres 100%
- Alonso Rios 100%

Data set: https://snap.stanford.edu/data/roadNet-CA.html

*/

#include <iostream>

#include "Dijkstra/Graph.h"
#include "Dijkstra/dijkstra.h"
#include "art.h"

using namespace std;

#define all(x) begin(x), end(x)

int main() {
  
  // Código de prueba
  /*
  graph<int, double> G;
  G.read_file("Dijkstra/CA_routes.txt");
  auto res = dijkstra(G, 793);
  // 37039
  int tget = 41991;
  G.show_neighbors(tget, 1051, 1044, 1050, 1047, 2249, 41991, 1087, 2248, 2249);
  G.show_shortest_path(tget, res);
  */

  main_menu();

  return 0;
} 