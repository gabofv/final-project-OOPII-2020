#pragma once

#include <list>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "AStar.h"

using namespace std;

void print_map_default(int& size, mapa& m1){
  for(int x = -1; x < size+1; x++){
      for(int y = -1; y < size+1; y++){
        if(x < 0 || y < 0 || x > size-1 || y > size-1 || m1(x,y) == 1){
          cout<< "|";
        }
        else{
          cout<<".";
        }
      }
    cout<<endl;
  }
}


void pedir_coordenadas_inicial(int& size, mapa& m1, int& x, int& y, pointA& p1){

  cout << "Ingresa una coordenada x para tu punto inicial: "; cin >> x;
  while(x > size-1){
    system("clear");
    print_map_default(size, m1);
    cout << "Ingresa una coordenada x para tu punto inicial: "; cin >> x;
  }

  cout << "Ingresa una coordenada y para tu punto inicial: "; cin >> y;
  while(y > size-1){
    system("clear");
    print_map_default(size, m1);
    cout << "Ingresa una coordenada y para tu punto inicialnicial: "; cin >> y;
  }

  p1.set_x(x);
  p1.set_y(y); 
}



void pedir_coordenadas_final(int& size, mapa& m1, int& x, int& y, pointA& e){
  cout << "Ingresa una coordenada x para tu punto final: "; cin >> x;
  while(x > size-1){
    system("clear");
    print_map_default(size, m1);
    cout << "Ingresa una coordenada x para tu punto final: "; cin >> x;
  }

  cout << "Ingresa una coordenada y para tu punto final: "; cin >> y;
  while(y > size-1){
      system("clear");
      print_map_default(size, m1);
      cout << "Ingresa una coordenada y para tu punto final: "; cin >> y;
  }

  e.set_x(x);
  e.set_y(y);
}

void set_map(int& size, int& x, int& y, pointA& p1, pointA& e, mapa& m1){
  system("clear");
  
  cout<<"****** MAPA REFERENCIAL *****" << endl;
  cout << endl;
  print_map_default(size,m1);
  cout << endl;

  pedir_coordenadas_inicial(size,m1,x,y,p1);

  while(m1(x,y) == 1){
    cout<<"No puedes escoger este punto ya que es un obstaculo"<<endl;
    pedir_coordenadas_inicial(size,m1,x,y,p1);
  }

  pedir_coordenadas_final(size,m1,x,y,e);
  
  while(m1(x,y) == 1){
    cout<<"No puedes escoger este punto ya que es un obstaculo"<<endl;
    pedir_coordenadas_final(size,m1,x,y,e);
  }

}