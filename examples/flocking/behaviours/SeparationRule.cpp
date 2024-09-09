#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  // iterate over the neighborhood
  for (auto n : neighborhood) {
    //Don't factor the current boid into the vector.
    if (n->getPosition().x == boid->getPosition().x && n->getPosition().y == boid->getPosition().y) {
      continue;
    }
// calculate the distance and direction components of the neighbor and current boid.
    Vector2f dir = {boid->transform.position.x - n->transform.position.x, boid->transform.position.y - n->transform.position.y};

    float dist = sqrt(dir.x * dir.x + dir.y * dir.y);


    if (dist <= desiredDistance) {
      continue;
    }
//calculate normalized vector and strength .
    Vector2f hat = {dir.x/dist, dir.y/dist};
    float strength = 1/dist;
    //add the x and y components to the separating force vector.
    separatingForce.x += hat.x * strength;
    separatingForce.y += hat.y * strength;
  }



  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2f position = boid->transform.position;
         int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
   }

  separatingForce = Vector2f::normalized(separatingForce);
 //return vector.
  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
