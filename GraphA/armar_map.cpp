#include "armar_map.h"
#include <iostream>


char** armar_mapa(string& archivo){
  archivo="GraphA/"+ archivo +".txt";
  ifstream file(archivo,ios::in);

  char** mapita = new char*[25];
  for(int i = 0; i < 25; i++){
    mapita[i] = new char[25];
  }

  if(!file.is_open()){
    cout<<"No se puede abrir el archivo"<<endl;
    return mapita;
  }

  int a;
  int row = 0,column = 0;
  while(file >> a){
    mapita[row][column] = a;
    column++;
    if(column == 25){
      row++;
      if(row == 25){
        break;
      }
      column = 0;
    }
  }
  return mapita;
}