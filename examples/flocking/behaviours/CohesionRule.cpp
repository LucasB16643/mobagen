#include "CohesionRule.h"

#include "../../../cmake-build-debug/_deps/glm-src/glm/ext/quaternion_geometric.hpp"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  Vector2 centerMass =  Vector2f::zero();
  for (auto n : neighborhood) {
    if (n->getPosition().x == boid->getPosition().x && n->getPosition().y == boid->getPosition().y) {
      continue;
    }
    centerMass += {n->transform.position/neighborhood.size()};
    Vector2f dir = {centerMass.x - boid->transform.position.x, centerMass.y - boid->transform.position.y};
    float dist = sqrt(dir.x * dir.x + dir.y * dir.y);

    cohesionForce = dir/boid->getDetectionRadius();
  }

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  return cohesionForce;
}