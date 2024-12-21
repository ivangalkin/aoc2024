// Modified with
// https://stackoverflow.com/questions/28998597/how-to-save-shortest-path-in-dijkstra-algorithm

#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

#define INF 0x3f3f3f3f
// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// To add an edge (assumes the same weight u->v and v->u, therefore not usable
// in our task)
void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
  adj[u].push_back(make_pair(v, wt));
  adj[v].push_back(make_pair(u, wt));
}

// Prints shortest paths from src to all other vertices
std::tuple<int, std::vector<int>>
shortestPath(const vector<pair<int, int>> adj[], int V, int src, int target) {
  // Create a priority queue to store vertices that
  // are being preprocessed. This is weird syntax in C++.
  // Refer below link for details of this syntax
  // http://geeksquiz.com/implement-min-heap-using-stl/
  priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

  // Create a vector for distances and initialize all
  // distances as infinite (INF)
  vector<int> dist(V, INF);

  vector<bool> visited(V, false);
  vector<int> prev(V, -1);

  // Insert source itself in priority queue and initialize
  // its distance as 0.
  pq.push(make_pair(0, src));
  dist[src] = 0;

  /* Looping till priority queue becomes empty (or all
  distances are not finalized) */
  while (!pq.empty() && !visited[target]) {
    // The first vertex in pair is the minimum distance
    // vertex, extract it from priority queue.
    // vertex label is stored in second of pair (it
    // has to be done this way to keep the vertices
    // sorted distance (distance must be first item
    // in pair)
    int u = pq.top().second;
    pq.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    // Get all adjacent of u.
    for (const auto &[v, weight] : adj[u]) {
      // If there is shorted path to v through u.
      if (dist[v] > dist[u] + weight) {
        // Updating distance of v
        dist[v] = dist[u] + weight;
        pq.push(make_pair(dist[v], v));

        prev[v] = u;
      }
    }
  }

  vector<int> res;
  res.push_back(target);
  int temp = target;
  do {
    temp = prev[temp];
    res.push_back(temp);
  } while (temp != src);

  // Print shortest distances stored in dist[]
  //        printf("Vertex Distance from Source\n");
  //        for (int i = 0; i < V; ++i)
  //            printf("%d \t\t %d\n", i, dist[i]);

  return {dist[target], res};
}
