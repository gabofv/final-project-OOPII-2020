#pragma once

#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

struct pointA {
  int x, y;

  pointA(int x=0, int y=0) {
    this->x=x; 
    this->y=y;
  }

  bool operator == (const pointA& p) {return p.x == x && p.y == y;}
  pointA operator + (const pointA& p) {return pointA(p.x + x, p.y + y);}

  void set_x(int value){x = value;}
  void set_y(int value){y = value;}
};


