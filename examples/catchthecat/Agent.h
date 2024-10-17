#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class World;

class Agent {
public:

  struct AStarNode {
    AStarNode(Point2D p) : point(p){};
    AStarNode() = default;
    Point2D point;
    int accDistance;
    int heuristicDistance;
    //Operator < used to compare two nodes
    //We want to know if the node we're comparing has a smaller value
    bool operator<(const AStarNode& rhs) const {
      return (accDistance + heuristicDistance) > (rhs.accDistance + heuristicDistance);
    }
    int calculateClosestSideHeuristic(const Point2D p, int halfSideSize) const {
      //The other way of calculating heuristic based on finding the closest side
      if (p.x - p.y > 0 && p.x + p.y > 0) { //Tests if right side is closest
        return halfSideSize - p.x; //returns distance from right side
      }
      else if (p.x - p.y < 0 && p.x + p.y > 0) { //Tests if top side is closest
        return halfSideSize - p.y; //returns distance from top side
      }
      else if (p.x - p.y < 0 && p.x + p.y < 0) { //Tests if left side is closest
        return p.x - halfSideSize; //returns distance from left side
      }
      else {
        return p.y - halfSideSize; //Otherwise returns distance from bottom side
      }
    }
  };


  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeightbors(World* world, Point2D point, std::unordered_set<Point2D> &queue, std::unordered_map<Point2D, bool> &visited);
};

#endif  // AGENT_H
