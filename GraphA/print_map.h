#pragma once

#include "set_map.h"

void print_mapa () {
  int x = 0, y = 0;
  int size = 0;
  pointA p1, e;
  Astar as;

  cout << endl;
  cout << "************/\\WARNING/\\************" << endl;
  cout << "**                               **" << endl;
  cout << "**  Tamaño maximo de mapa = 25   **" << endl;
  cout << "**                               **" << endl;
  cout << "***********************************" << endl;
  cout << endl;

  cout << "Ingresa el tamaño de tu Mapa: ";cin>>size;
  while(size > 25){
    cout << "Ingresa el tamaño de tu Mapa: ";cin>>size;
  }

  mapa m1(size,size);

  set_map(size,x,y,p1,e,m1);

  while(p1 == e){
    cout<<"LOS PUNTOS SON IGUALES, ESOCGER OTROS PUNTOS:"<<endl;
    set_map(size,x,y,p1,e,m1);
  }

  system("clear");
  cout<<"***** MAPA CON RUTA COMPLETADA *****"<<endl;
  
  if(as.buscar(p1, e, m1)){
    list<pointA> path_;
    int g = as.path(path_);
    for(int x = -1; x < size+1; x++){
      for(int y = -1; y < size+1; y++){
        if(x < 0 || y < 0 || x > size-1 || y > size-1 || m1(x,y) == 1){
          cout<< "|";
        }
        else{
          if (find(path_.begin(), path_.end(), pointA(x, y)) != path_.end()) {
            cout << "x"; //coloca casilla recorrida
          }
          else{
            cout << "."; //casilla revisada pero no optm
          }
        }
      }
      cout<<endl;
    }
    cout << "\nCosto: " << g << ": " << endl;
    for(auto i = path_.begin(); i != path_.end(); i++){
      cout<< "(" << (*i).x << ", " << (*i).y << ") ";
    }
  }
  else{
    cout<<"NO EXISTE UN CAMINO OPTIMO DEBIDO A LAS RESTRICCIONES DEL MAPA";
  }
  cout<<"\n\n";
}
