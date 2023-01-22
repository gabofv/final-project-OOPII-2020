#pragma once

#include <iostream>
#include "Dijkstra/Graph.h"
#include "GraphA/print_map.h" 
using namespace std;

void menu() {
  cout << "***************************" << endl;
  cout << "*                         *" << endl;
  cout << "*" << "  1. Dijkstra algorithm" << "  *" << endl;
  cout << "*" << "  2. A-Star algorithm" << "    *" << endl;
  cout << "*" << "  0. Close project" << "       *" << endl;
  cout << "*                         *" << endl;
  cout << "***************************" << endl;
}

void tittle () {
    cout << " ____                      _     _               ____       _   _     " << endl;
    cout << "/ ___|  ___  __ _ _ __ ___| |__ (_)_ __   __ _  |  _ \\ __ _| |_| |__  " << endl;
    cout << "\\___ \\ / _ \\/ _` | '__/ __| '_ \\| | '_ \\ / _` | | |_) / _` | __| '_ \\ " << endl;
    cout << " ___) |  __/ (_| | | | (__| | | | | | | | (_| | |  __/ (_| | |_| | | |" << endl;
    cout << "|____/ \\___|\\__,_|_|  \\___|_| |_|_|_| |_|\\__, | |_|   \\__,_|\\__|_| |_|" << endl;
    cout << "                                         |___/                        " << endl;
}

void print_dijkstra () {
    cout << " ____  _  _ _        _              " << endl;
    cout << "|  _ \\(_)(_) | _____| |_ _ __ __ _ " << endl;
    cout << "| | | | || | |/ / __| __| '__/ _` | " << endl;
    cout << "| |_| | || |   <\\__ \\ |_| | | (_| |" << endl;
    cout << "|____/|_|/ |_|\\_\\___/\\__|_|  \\__,_|" << endl;
    cout << "       |__/                         " << endl;
}

void print_a () {
    cout << "    _         " << endl;
    cout << "   / \\  __/\\__" << endl;
    cout << "  / _ \\ \\    /" << endl;
    cout << " / ___ \\/_  _\\" << endl;
    cout << "/_/   \\_\\ \\/  " << endl;
}

void see_u() {
  cout << " ____              _   _         " << endl;
  cout << "/ ___|  ___  ___  | | | |        " << endl;
  cout << "\\___ \\ / _ \\/ _ \\ | | | |        " << endl;
  cout << " ___) |  __/  __/ | |_| |  _ _ _ " << endl; 
  cout << "|____/ \\___|\\___|  \\___/  (_|_|_)" << endl;
}

void print_gracias() {
    cout << "  ____                _                  ____  " << endl;
    cout << " / ___|_ __ __ _  ___(_) __ _ ___    _  |  _ \\ " << endl;
    cout << "| |  _| '__/ _` |/ __| |/ _` / __|  (_) | | | |" << endl;
    cout << "| |_| | | | (_| | (__| | (_| \\__ \\   _  | |_| |" << endl;
    cout << " \\____|_|  \\__,_|\\___|_|\\__,_|___/  (_) |____/ " << endl;
}

void print_for_dijkstra () {
  cout << endl;
  cout << "The file is ready! " << endl;
  cout << "Please choose and option for Dijkstra algorithm: " << endl << endl;
  cout << "*****************************************************" << endl;
  cout << "*                                                   *" << endl;
  cout << "*  1. Calculate degree of some roads intersections  *" << endl;
  cout << "*  2. Show the shortest path and time               *" << endl;
  cout << "*  3. Show neighbors                                *" << endl;
  cout << "*  4. Show most recent Shortest Path Tree root      *" << endl;
  cout << "*  5. Show weights of nodes                         *" << endl;
  cout << "*                                                   *" << endl;
  cout << "*****************************************************" << endl;
  cout << endl;
  //show id
  //
}

bool want_to_continue () {
  string rpt; bool band=true;
  cout << "Do you want to choose another option? (y/n): ";
  while (band) {
    cin >> rpt;
    if (rpt == "y" || rpt == "yes") {
      band = false;
      return true;
    }
    else if (rpt == "n" || rpt == "no") {
      band = false;
      return false; 
    }
    else {
      cout << "Write a valid option... ";
    }
  }
  return false;
}

//***********************************************************************

bool ask_continue() {
  string ans; bool accept=true;
  cout << "Do you want to return to our menu? (y/n) -> ";
  while (accept) {
    cin >> ans;
    if (ans == "y" || ans == "yes") {
      accept = false;
      system("clear");
      return true;
    }
    else if (ans == "n" || ans == "no") {
      accept = false;
      system("clear");
      see_u(); cout << endl;
      //system("clear");
      return false; 
    }
    else {
      cout << "Please try again with a valid answer -> ";
    }
  }
  return false;
}

void main_menu() {
  int opt; bool band=true;
  tittle();
  cout << "Welcome to our project" << endl; cout << endl;

  while (band) {
    cout << "Go ahead and select an option from our menu!" << endl; cout << endl;
    menu(); cout << endl; 
    cout << "---> "; cin >> opt;
    system("clear");
    
    switch(opt) {
      case 1: {
        bool band_1=true; int opt_1;
        cout << "This is our implementation of: " << endl;
        print_dijkstra(); cout << endl;
        //Dijkstra algorithm
        print_for_dijkstra();

        graph<int, double> G;
        G.read_file("Dijkstra/CA_routes.txt");

        //**********************************************************************
        while (band_1) {
          cout << "----> "; cin >> opt_1;
          switch(opt_1) {
            case 1: {
              //_______________________________
              G.degree_of(1, 41991, 3, 1050);
              //_______________________________
              cout << endl;
              band_1 = want_to_continue();
              break;
            }
            case 2: {
              //_______________________________
              auto res = dijkstra(G, 793);
              int tget = 41991;
              G.show_shortest_path(tget, res);
              //_______________________________
              cout << endl;
              band_1 = want_to_continue();
              break;
            }
            // Shows neighbors of a variated # of nodes
            case 3: {
              //_______________________________
              G.show_neighbors(1, 1051, 3, 41991);
              //_______________________________
              cout << endl;
              band_1 = want_to_continue();
              break;
            }
            // Shows root of Shortest Path Tree (SPT) if there is a SPT
            case 4: {
              //_______________________________
              G.show_spt_root();
              //_______________________________
              band_1 = want_to_continue();
              break;
            }
            case 5: {
              //_______________________________
              G.weight_of(1, 4, 41991, 1051, 8, 201255);
              //_______________________________
              band_1 = want_to_continue();
              break;
            }
            case 0: {
              print_gracias(); cout << endl;
              exit(-1);
            }
            default: {
              system("clear");
              cout << "Please choose a correct option for our dijkstra implementation..." << endl;
              print_for_dijkstra();
              band_1 = true;
              break;
            }
          }
        }
        //**********************************************************************

        cout << "***********************************************" << endl;
        band = ask_continue();
        break;
      }
      case 2: {
        cout << "This is our implementation of: " << endl;
        print_a(); cout << endl;
        //A* algorithm
        print_mapa();
        band = ask_continue();
        break;
      }
      case 0: {
        print_gracias(); cout << endl;
        exit(-1);
      }
      default: {
        system("clear");
        cout << "Please choose a correct item..." << endl;
        break;
      }
    }
  }
}