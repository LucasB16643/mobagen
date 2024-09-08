#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  for (auto n : neighborhood) {
    if(n->transform.position.x == boid->transform.position.x && n->transform.position.y == boid->transform.position.y)
      continue;
    averageVelocity.x += n->velocity.x;
    averageVelocity.y += n->velocity.y;
  }
  if(neighborhood.size() == 0) {
    return averageVelocity;
  }
  averageVelocity.x /= neighborhood.size();
  averageVelocity.y /= neighborhood.size();
  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  return Vector2f::normalized(averageVelocity);
}