#pragma once

#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>
#include <utility>

#include "Graph.h"
#include "types_.h"

using namespace std;

// Function pointer to a comparer (lambda)
template <typename ID_t, typename w_t>
auto order = [] (const node<ID_t, w_t> &A,const node<ID_t, w_t> &B){ 
   return A.peso > B.peso;
 };

// Dijkstra´s Algorithm - Shortest Path Tree (SPT)
template <typename D_id, typename D_w>
return_t<D_id, D_w> dijkstra (graph<D_id, D_w> &X, const D_id &source) {

    using node_t = node<D_id, D_w>;

    // Priority queue that stores nodes and uses
    // "order" comparer to compare weights
    priority_queue<node_t, vector<node_t>, decltype(order<D_id,D_w>)>q(order<D_id,D_w>);

    // Distances between root and target node
    unordered_map<D_id, D_w> distance;
    // Parent of each node
    unordered_map<D_id, D_id> parent;

    // Reserves memory and sets load factor 
    // for increased speed
    distance.reserve(1<<20);
    parent.reserve(1<<20);
    distance.max_load_factor(0.5);
    parent.max_load_factor(0.5);

    // Initialization of distance and parent
    for(auto& [key, n] : X.nodes) 
    {
      distance[key] = INF;
      parent[key] = -1;
    }

    // From root -> source
    q.push(node_t(source, 0));
    distance[source] = 0;

    while(!q.empty()) {

        // Retrieve node with least weight
        D_id x = q.top().id;
        D_w d = q.top().peso;

        q.pop();

        if(d != distance[x]) continue;

        for(const auto neighbor : X.adj[x]) {

            // Neighbor info.
            D_id to = neighbor.get().id;
            D_w w = neighbor.get().peso;

            if(distance[x] + w < distance[to]) {
                // Distance update
                distance[to] = distance[x] + w;
                // Parent update
                parent[to] = x;
                q.push(node_t(to, distance[to]));
            }
        }
    }

    // Root from the last SPT is recorded in graph
    X.spt_root = source;
    
    return_t<D_id, D_w> ans(distance, parent);
    return ans;
};
