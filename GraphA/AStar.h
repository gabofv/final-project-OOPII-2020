#pragma once

#include <iostream>
#include <list>
#include "nodeA.h"
#include "mapA.h"
#include <algorithm>
#include <iterator>

using namespace std;

class Astar { 
public:
  mapa m; //matriz que simula rutas
  pointA p_fin; // punto final
  pointA p_ini; //punto inicial
  pointA neigh[8]; //puntos cardinales o vecinos
  list<nodeA> open; //lista de casillas o nodos que pueden seguir abriendo caminos
  list<nodeA> close; //lista de nodos que ya hemos revisado

//------------------------------------------------------------------

//Se encarga de ponerle puntos cardinales para que verifique si hay una pared o algun objeto que evita que pueda seguir su camino
  Astar(){ 
    neigh[0] = pointA(-1,-1);
    neigh[1] = pointA(1,-1);
    neigh[2] = pointA(-1,1);
    neigh[3] = pointA(1,1);
    neigh[4] = pointA(0,-1);
    neigh[5] = pointA(-1,0);
    neigh[6] = pointA(0,1);
    neigh[7] = pointA(1,0);
  }

  int calcularDistancia(pointA& p);
  bool validar_p(pointA& p);
  bool existe_punto (pointA& p, int costo);
  bool rellenar_lista_Open (nodeA& nd);
  bool buscar(pointA& z, pointA& e, mapa& matrix);
  int path(list<pointA>& camino);
};