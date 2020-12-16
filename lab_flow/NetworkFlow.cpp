/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  vector<Vertex> tempvertex = g_.getVertices();
  vector<Edge> tempedge = g_.getEdges();
    for(auto & v : tempvertex)
    {
      flow_.insertVertex(v);
      residual_.insertVertex(v);
    }
    for(auto & e : tempedge)
    {
      residual_.insertEdge(e.source, e.dest);
      residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
      residual_.insertEdge(e.dest, e.source);
      residual_.setEdgeWeight(e.dest, e.source, 0);
      flow_.insertEdge(e.source, e.dest);
      flow_.setEdgeWeight(e.source, e.dest, 0);
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int min = 1215752191;
  vector<int> tempedge;
  for(size_t i = 0; i < path.size() - 1; i ++)
  {
    tempedge.push_back(residual_.getEdgeWeight(path[i], path[i + 1]));
  }
  for(auto & e : tempedge)
  {
    if(!(e >= min))
    {
      min = e;
    }
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  vector <Vertex> verticies;
  int tempcap = 0;
  int final = 0;

  while(findAugmentingPath(source_, sink_, verticies)){
    vector<Edge> v = residual_.getEdges();
    tempcap = pathCapacity(verticies);
    final += tempcap;
    for(unsigned i = 0; i < verticies.size() - 1; i ++)
    {
      residual_.setEdgeWeight(verticies[i], verticies[i + 1], residual_.getEdgeWeight(verticies[i], verticies[i + 1]) - tempcap);
      residual_.setEdgeWeight(verticies[i + 1], verticies[i], residual_.getEdgeWeight(verticies[i + 1], verticies[i]) + tempcap);
      if(flow_.edgeExists(verticies[i], verticies[i + 1])==true)
      {
        flow_.setEdgeWeight(verticies[i], verticies[i + 1], flow_.getEdgeWeight(verticies[i], verticies[i + 1]) + tempcap);
      }
      else
      {
        flow_.setEdgeWeight(verticies[i + 1], verticies[i], flow_.getEdgeWeight(verticies[i + 1], verticies[i]) - tempcap);
      }
    }

  }
  maxFlow_ = final;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

