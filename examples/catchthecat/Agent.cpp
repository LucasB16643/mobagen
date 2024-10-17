#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<AStarNode> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state

  AStarNode start = AStarNode(w->getCat());

  start.heuristicDistance = start.calculateClosestSideHeuristic(start.point, w->getWorldSideSize() / 2);

  frontier.push(start);
  frontierSet.insert(start.point);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    AStarNode const current = frontier.top(); // get the current from frontier
    frontier.pop();
    frontierSet.erase(current.point); // remove the current from frontierset

    int const gridHalfSize = w->getWorldSideSize() / 2; //Gets the half grid size
    if (current.point.y == gridHalfSize || current.point.y == -gridHalfSize || current.point.x == gridHalfSize || current.point.x == -gridHalfSize) { //Checks if the point is a goal point
      borderExit = current.point;
      break;
    }

    visited[current.point] = true;// mark current as visited
     std::vector<Point2D> neighbors = getVisitableNeightbors(w, current.point, frontierSet, visited); //returns a vector of neighbors that are not visited, not cat, not block, not in the queue

    for (Point2D const neighbor : neighbors) {
      cameFrom[neighbor] = current.point;
      AStarNode newNeighborNode = AStarNode(neighbor); //Converts neighbor point into AStar node
      start.heuristicDistance = start.calculateClosestSideHeuristic(start.point, w->getWorldSideSize() / 2);
      frontier.push(newNeighborNode);
      frontierSet.insert(neighbor);
    }
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  vector<Point2D> path; //Path from the goal to the start
  if (borderExit != Point2D::INFINITE) { //Builds path only if a goal was found
    Point2D current = borderExit;
    while (current != start.point) { //Runs backwards through cameFrom map to build path from the goal to the start
      path.push_back(current);
      current = cameFrom[current];
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}

std::vector<Point2D> Agent::getVisitableNeightbors(World* world, Point2D point, std::unordered_set<Point2D> &queue, std::unordered_map<Point2D, bool> &visited) {
  int start = point.x - static_cast<int>(point.y % 2 == 0);
  std::vector<Point2D> visitables;


  for(int i = start; i < start + 2; i++) {
    Point2D checkPoint = {i, point.y - 1};
    if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
      visitables.push_back(checkPoint);
    }
  }


  for (int i = start; i < start + 2; i++) {
    Point2D checkPoint = {i, point.y + 1};
    if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
      visitables.push_back(checkPoint);
    }
  }


  start = point.x - 1;
  for (int i = start; i < start + 3; i++) {
    if (i != point.x) {
      Point2D checkPoint = {i, point.y};
      if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
        visitables.push_back(checkPoint);
      }
    }
  }

  return visitables;
}



