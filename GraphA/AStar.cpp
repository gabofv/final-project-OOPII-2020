#include "AStar.h"
using namespace std;

int Astar::calcularDistancia(pointA& p){
  //Aplicamos la heuristica (caso de suposicion)
    int x1 = p_fin.x - p.x; //coordenada x del punto final - punto inicial 
    int y1 = p_fin.y - p.y; //coordenada y del punto final - punto inicial
    return (x1 * x1 + y1 * y1);//retornamos la suma al cuadrado para su distancia
}

//----------------------------------------------------------------------------

//Validar si el punto ingresado es valido para el mapa construido comparando sus coodenadas con los puntos maximos y minimos de la matriz para ver si no sobrepasa el limite del mapa
bool Astar::validar_p(pointA &p){
  return (p.x > -1 && p.y > -1 && p.x < m.w && p.y < m.h);
}

//------------------------------------------------------------------------------

//Se encarga de determinar si existe un punto por el se pueda pasar
bool Astar::existe_punto(pointA& p, int costo){
  //parametro, punto a encontrar y su peso
  list<nodeA>::iterator it; 
  it = find(close.begin(), close.end(), p); //busca el punto ingresado en la lista de puntos que ya han sido revisados

  if (it != close.end()) { //Si el punto es encontrado 
    if( (*it).costo + (*it).distancia < costo) return true; // Si el peso de punto + su distancia es menor al peso ideal para llegar a dicho punto, entonces retorna verdadero y existe el punto
    else {
      close.erase(it); //elimina el punto encontrado
      return false;
    }
  }

  it = find(open.begin(),open.end(),p);
  if(it != open.end()){
    if((*it).costo + (*it).distancia < costo) return true;
    else {open.erase(it); return false;}
  }

  return false;
}

//---------------------------------------------------------------------------

bool Astar::rellenar_lista_Open(nodeA& nd){
  //Rellena la lista Open de nodos por revisar
  int t_cost; // Costo por cada paso que da
  int nc; // nuevo costo
  int dist;  
  pointA neigh_x; // Punto cercano al nodo 

  for (int i=0; i<8; i++) { // Recorre el array de vecinos o puntos cardinales
    t_cost = i < 4 ? 1:1; // Determina si el paso o recorrido es recto o diagonal, se puede hacer que la diagonal tenga un costo diferente
    neigh_x = nd.pos + neigh[i]; // Suma la posicion del nodo con cada uno de sus puntos cercanos o cardinales
    if (neigh_x == p_fin) return true; // Si el punto cercano es igual al punto final de la matriz entonces encontramos el camino corto

    //Si el punto nuevo es valido y sus coordenadas son diferentes de 1 osea no es una pared o vereda
    if (validar_p(neigh_x) && m(neigh_x.x, neigh_x.y) != 1) {
      nc = t_cost + nd.costo; //suma del costo por paso mas el costo que tenemos hasta ahorita, nos da un nuevo costo
      dist = calcularDistancia(neigh_x); //calcular distancia entre el nuevo punto y el punto final
      if (!existe_punto(neigh_x, nc + dist)) { //si no existe el punto
        nodeA nd1; //se crea un nuevo nodo 
        nd1.costo = nc; //se le da el nuevo costo al nuevo nodo
        nd1.distancia = dist;
        nd1.pos = neigh_x;
        nd1.parent = nd.pos; //al padre le asignamos como referencia la posicion de nuestro nodo (parametro)
        open.push_back(nd1); //Se agrega el nodo padre, se utilizara al momento de reconstruir el camino
      }
    }
  }
  return false; 
  // retorna false si no es posible llegar al punto teniendo los nodos de la lista
}

// -------------------------------------------------------------------------

//Busca desde nuestro  punto inicial hasta nuestro punto final a traves de la matriz
bool Astar::buscar(pointA& z, pointA& e, mapa& matrix){
  nodeA n; //crea un nuevo nodo
  p_fin = e; //el punto e define el punto final
  p_ini = z; //el punto z define el punto inicial
  m = matrix; // m es la matriz

  n.costo = 0; n.pos = z; n.parent = 0; n.distancia = calcularDistancia(z); //Los atributos del nodeA "n" son seteados para la busqueda

  open.push_back(n); //Se añada a la lista inicial "open" el primer nodo inicial

  while(!open.empty()){ //mientras la lista no este vacia
    nodeA n = open.front(); // el primer elemento es el primer nodo 
    open.pop_front(); //lo eliminamos
    close.push_back(n); //lo ponemos dentro de la lista de nodos ya revisados
    if(rellenar_lista_Open(n)) {return true;} //Se estaria rellenando con las casillas que faltan revisar, es decir, se estaria tomando en cuenta sus vecinos y una vez que se concrete el rellenado, se devuelve true
  }
  return false; //sino falso
}

//----------------------------------------------------------------------------

//determina el costo o la cantidad de puntos que tuvo que recorrer para llegar a su destino
int Astar::path(list<pointA>& camino){
  camino.push_front(p_fin); //se agrega a la lista camino, el punto final

  int cost = 1 + close.back().costo; //El coste de los pasos que hemos dado + 1 pasito extra dara el nuevo costo

  camino.push_front(close.back().pos); //se añade a camino la posicion del ultimo nodo de la lista de nodos ya revisados, en este caso es el primer nodo que se reviso.
  
  pointA parent = close.back().parent; //el padre toma el valor del parent del ultimo nodo de la lista de nodos ya revisados, en este del primer nodo que ser evaluo.

  for(auto i = close.rbegin(); i != close.rend(); i++){ //recorremos desde el final al inicio del close
    if((*i).pos == parent && !((*i).pos == p_ini )){ //si la posicion del elemento es igual a su padre y su posicion es diferente a la igualdad entre su posicion inicial
      camino.push_front((*i).pos); //metemos las posiciones del elemento en la lista de caminos o puntos
      parent = (*i).parent; //El "parent" tomara el padre de nuestro elemento para reconstruir nuestro camino
    }
  }
  camino.push_front(p_ini); //se agrega a la lista de puntos "camino" el punto inicial
  return cost; //se retorna el costo total del camino
}