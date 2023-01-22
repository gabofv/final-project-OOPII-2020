#pragma once

// Libraries
#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include <unordered_map>
#include <utility>
#include <random>
#include <functional>
#include <string>
#include <fstream>
#include <initializer_list>
#include <queue>
#include <algorithm>
#include <fstream>
#include "boost/graph/graphviz.hpp"
#include "boost/graph/adjacency_list.hpp"


#include "types_.h"

// Macros
#define all(x) begin(x), end(x)
#define INF numeric_limits<double>::max()
#define contains(cont, val) cont.find(val) != cont.end()
#define random_choice() (choice())? distr_SS(gen) : distr_CS(gen)

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> DrawnG;

using namespace std;

//-----------------------------------------------

// Random lib declarations - definition in .cpp

extern random_device rd; 
extern mt19937 gen; 

extern uniform_int_distribution<> distr;
extern uniform_real_distribution<> distr_CS;
extern uniform_real_distribution<> distr_SS;

int choice();


//-----------------------------------------------

// node representation
template <typename ID_t, typename weight_t>
struct node {
  weight_t peso;
  ID_t id;
  node (ID_t id) : id(id) {}
  node (ID_t id, weight_t peso) : id(id), peso(peso) {}
  node () = default;
  ~node () = default;
};

// For storing node references in a container
template <typename T, typename T2>
using node_ref = reference_wrapper<node<T, T2>>;

//------------------------------------------------------

// Template class for the graph representation
template<typename ID_t, typename weight_t>
class graph {
  
  // Adjacency list
  unordered_map<ID_t, vector<node_ref<ID_t,weight_t>>> adj;
  
  // Info. for every node
  unordered_map<ID_t, node<ID_t, weight_t>> nodes;

  // Count of #nodes and #edges
  size_t N_nodes{};
  size_t N_edges{};

  // Actual SPT root
  ID_t spt_root = -1;

  
  // Ojo!!!!!!!!!!!!!!!!!!
  template<typename D_id, typename D_w> 
  friend return_t< D_id, D_w> dijkstra (graph<D_id, D_w> &X, const D_id &source); 
  
  public:
  
  // Declaration implies prev. memory reserve
  // in exchange of hash speed (max_load_factor=0.25)
  // See in graph.cpp
  graph() 
  { 
    // Pre definir el tamaño
    // 1<<21
    adj.reserve(1<<20); 
    nodes.reserve(1<<20); 
    adj.max_load_factor(0.25);
    nodes.max_load_factor(0.25);
  };

  // Destructor
  ~graph() = default;
  
  void limpiar_archivo(vector<ID_t>& nodos) {
    fstream entrada;
    fstream salida;
    entrada.open("Dijkstra/GraphToPng.dot", ios::in);
    vector<string> lectura;
    string line;
    
    while (std::getline(entrada, line)){
        lectura.push_back(line);
    }
    auto maxnum=nodos[nodos.size()-1];
    vector<string> escritura;
    for(auto it=lectura.begin()+maxnum+2;it!=lectura.end();it++){
      escritura.push_back(*it);
    }
    entrada.close();
  
    vector<string> numeros;
    for(auto nodo:nodos){
      numeros.push_back(to_string(nodo));
    }

    salida.open("Dijkstra/Graph.dot",ios::out);

    salida<<"graph G {";
    for(auto elem:numeros){
      salida<< elem +";"<<endl;
    }
    for(auto elem:escritura){
      salida<< elem<<endl;
    }
    salida.close();
  }
  
  // Add route - specially implemented for the purpose of our project
  // (random weighted nodes)
  // *Can be easily adapted to a general-purpose graph

  void add_route(ID_t id_1, ID_t id_2) {

    auto find_ID = contains(nodes, id_1);
    auto find_ID_2 = contains(nodes, id_2);

    // Alias
    using node_t = node<ID_t, weight_t>;
    
    // If both nodes exist...
    if(!find_ID && !find_ID_2){
      weight_t random_N = random_choice();
      weight_t random_M = random_choice();
      nodes[id_1] = node_t(id_1, random_M);
      nodes[id_2] = node_t(id_2, random_N);
      adj[id_1].push_back(nodes[id_2]);
      adj[id_2].push_back(nodes[id_1]);
      N_edges++;
      N_nodes += 2;
      return;
    }

    // If one of both nodes doesn´t exist...
    if(!find_ID || !find_ID_2) {
      weight_t random_N = random_choice();
      if(!find_ID) {
        nodes[id_1] = node_t(id_1, random_N);
        adj[id_1].push_back(nodes[id_2]);
        adj[id_2].push_back(nodes[id_1]);
      }
      else{
        nodes[id_2] = node_t(id_2, random_N);
        adj[id_2].push_back(nodes[id_1]);
        adj[id_1].push_back(nodes[id_2]);
      }
      N_edges++;
      N_nodes++;
      return;
    }

    // Checks if an edge exists between to existing nodes
    auto func = [&id_2] (const node<ID_t, weight_t> &A) { return A.id == id_2;};
    auto it = find_if(all(adj[id_1]), func);

    // If an edge already exists...
    if(it != end(adj[id_1])) {
      cout << "Ya existe una ruta entre ambos nodos.\n"; 
      return;
    }

    // If there wasn´t an edge now an edge is created
    adj[id_1].push_back(nodes[id_2]);
    adj[id_2].push_back(nodes[id_1]);

    N_edges++;
  }

  // Add node - adds a node to the graph
  void add_node(ID_t id) {
    auto find_id = contains(nodes, id);
    if(!find_id) {
      weight_t random_N = random_choice();
      node<ID_t, weight_t> F(id, random_N);
      nodes[id] = F;
      N_nodes++;
    }
    else cout << "Ya existe ese nodo." << endl;
  }
    
  // Getters
  size_t number_of_nodes() { return N_nodes; };
  size_t number_of_edges() { return N_edges; };

  template <typename ...ids>
  void weight_of(ids... I) { 

    cout << "\n+-------------------------------------\n";
    
    initializer_list<ID_t> aux {forward<ids>(I) ...};
  
    // Iteration over nodes IDs
    for(const auto &node_identity : aux) 
        if(contains(nodes, node_identity))
        {
          cout << "Weight of intersec. #" << node_identity << ": " << nodes[node_identity].peso << "\n";
        }
        else{
          cout << "Node " << node_identity << " doesn´t exist yet.\n";
        }

    cout << "+-------------------------------------\n";
    cout << endl;
  
  };

  void show_spt_root() {
    if (spt_root == -1) {
      cout << "There is no Shortest Path Tree built yet.\n";
      return;
    }
    else
      cout << "Last Shortest Path Tree root: " << spt_root << "\n";
  };

  // Builds vector of nodes' ID in random order
  vector<ID_t> get_nodes_id() {
    vector<ID_t> ans;
    for(auto& [key, val] : nodes)
    {
      ans.push_back(key);
    }
    return ans;
  };

  template <typename ...N>
  void degree_of(N... ids) {

    cout << "\n+-------------------------------------\n";

    initializer_list<ID_t> aux = {forward<N>(ids) ...};

    for(auto ID_ : aux){

      if(contains(nodes, ID_)){
        // Degree of
        cout << "Roads in intersection #" << ID_  << ": ";
        cout << adj[ID_].size() << "\n";
      }
    }
    cout << "+-------------------------------------\n";
  }
  
  // Show methods
  template <typename ...N>
  void show_neighbors(N... ids) {

    cout << "\n+-------------------------------------\n";
    
    // Perfect forwarding of variated node IDs 
    // into an init_list
    initializer_list<ID_t> aux = {forward<N>(ids)...};
    
    for(auto ID_ : aux) {
      if(contains(nodes, ID_)){
        
        // Node ID
        cout << "Intersection ID: " << ID_ << "\n";
        // Neighbors
        cout << "Next intersections: [ ";

        for(auto neigh : adj[ID_])
          cout << neigh.get().id << " ";

        cout << "]\n";

      }
    }
    cout << "+-------------------------------------\n";
  }

  // Print the route between two intersections
  void show_shortest_path(const ID_t &target_node, return_t<ID_t, weight_t> &SPT_info){
    DrawnG g;
    cout << "\n";
    cout << "From intersec. " << spt_root << " to intersec. " << target_node;
    cout << "\n";

    // Backtrack path
    vector<ID_t> path;
    
    auto temp = target_node;
    
    while(temp != spt_root) 
    {
      path.push_back(temp);
      temp = SPT_info.p[temp];
    }

    path.push_back(temp);

    // End -> Start order to Start -> End 
    reverse(all(path));
    
    vector<ID_t> nodos;
    for(const auto intersec : path){
      if(intersec != path[path.size()-1]) {
        nodos.push_back(intersec);
        // Print path
        cout << intersec << " -> ";
        }
      }

    for(int i = 0; i < nodos.size()-1; i++){
      add_edge(nodos[i], nodos[i+1],g);
    }

    //añadimos ultimo nodo al graficador
    add_edge(nodos[nodos.size()-1],path[path.size()-1],g);
    nodos.push_back(path[path.size()-1]);
  
    cout << path[path.size()-1] << "\n";

    // Shortest path length 
    cout << "Time lost: " << SPT_info.d[target_node] << " seconds.\n";

    ofstream outf("Dijkstra/GraphToPng.dot");
    write_graphviz(outf, g);
    
    limpiar_archivo(nodos);
  }

  // Read a text file (edges)
  void read_file(string filename) {

    ifstream f(filename);
    
    int nodo_1, nodo_2; 
    
    while(f >> nodo_1 >> nodo_2)
    
      add_route(nodo_1, nodo_2);
    
    f.close();
  }

};
