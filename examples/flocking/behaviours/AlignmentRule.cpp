#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {

  Vector2f averageVelocity = Vector2f::zero();
  // iterate over the neighborhood
  for (auto n : neighborhood) {
    //Don't factor the current boid into the vector.
    if(n->transform.position.x == boid->transform.position.x && n->transform.position.y == boid->transform.position.y)
      continue;
    //add the velocity of each neighbor together
    averageVelocity.x += n->velocity.x;
    averageVelocity.y += n->velocity.y;
  }
  if(neighborhood.size() == 0) {
    return averageVelocity;
  }
  //average out the accumulated volocity
  averageVelocity.x /= neighborhood.size();
  averageVelocity.y /= neighborhood.size();

//return the average velocity vector
  return Vector2f::normalized(averageVelocity);
}