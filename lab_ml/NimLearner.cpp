/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    startingVertex_ = "p1-"+std::to_string(startingTokens);
    for(unsigned int i=startingTokens;(int)i>=0;i--)
    {
      g_.insertVertex("p1-"+std::to_string(i));
      g_.insertVertex("p2-"+std::to_string(i));
    }
    for(unsigned int i=startingTokens;(int)i>=0;i--)
    {
      if((int)i-2>=0)
      {
        bool temp = g_.insertEdge("p1-"+std::to_string(i),"p2-"+std::to_string(i-2));
        g_.setEdgeWeight("p1-"+std::to_string(i),"p2-"+std::to_string(i-2),0);
        bool temp1 = g_.insertEdge("p2-"+std::to_string(i),"p1-"+std::to_string(i-2));
        g_.setEdgeWeight("p2-"+std::to_string(i),"p1-"+std::to_string(i-2),0);
        if(!temp || !temp1)
          std::cout<<"error"<<std::endl;
      }
      if((int)i-1>=0)
      {
        bool temp2 = g_.insertEdge("p1-"+std::to_string(i),"p2-"+std::to_string(i-1));
        g_.setEdgeWeight("p1-"+std::to_string(i),"p2-"+std::to_string(i-1),0);
        bool temp3 = g_.insertEdge("p2-"+std::to_string(i),"p1-"+std::to_string(i-1));
        g_.setEdgeWeight("p2-"+std::to_string(i),"p1-"+std::to_string(i-1),0);
        if(!temp2 || !temp3)
          std::cout<<"error"<<std::endl;
      }
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  Vertex curr_ = startingVertex_;
 Vertex curr_next = startingVertex_;
 //std::cout<<curr_next<<" here"<<std::endl;
 while(curr_next!="p1-0" && curr_next !="p2-0")
 {
   vector<Vertex> temp = g_.getAdjacent(curr_);
   if(temp.size()==1)
   {
     curr_next = temp.at(0);
   }
   if(temp.size()!=1)
   {
     curr_next = temp.at(rand()%2);
   }
   Edge e = g_.getEdge(curr_,curr_next);
   path.push_back(e);
   curr_ = curr_next;
 }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 if(path.at(path.size()-1).dest=="p1-0")
 {
   for(unsigned int i=0;i<path.size();i++)
   {
     if(i%2==1)
     {
       Vertex temp = path.at(i).source;
       Vertex temp1 = path.at(i).dest;
       int old = g_.getEdgeWeight(temp,temp1);
       g_.setEdgeWeight(temp,temp1,old+1);
     }else
     {
       Vertex temp = path.at(i).source;
       Vertex temp1 = path.at(i).dest;
       int old = g_.getEdgeWeight(temp,temp1);
       g_.setEdgeWeight(temp,temp1,old-1);
     }
     //return;
   }
 }else
 {
   for(unsigned int i=0;i<path.size();i++)
   {
     if(i%2==0)
     {
       Vertex temp = path.at(i).source;
       Vertex temp1 = path.at(i).dest;
       int old = g_.getEdgeWeight(temp,temp1);
       g_.setEdgeWeight(temp,temp1,old+1);
     }else
     {
       Vertex temp = path.at(i).source;
       Vertex temp1 = path.at(i).dest;
       int old = g_.getEdgeWeight(temp,temp1);
       g_.setEdgeWeight(temp,temp1,old-1);
     }

   }
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
