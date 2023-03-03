#ifndef CHESS_MANAGER_H
#define CHESS_MANAGER_H

#include "WorldState.h"
#include <Engine.h>
#include <GameObject.h>
#include <iostream>
#include <ColorT.h>
#include <unordered_set>

class Manager: GameObject  {
 private:
  WorldState state;
  vector<WorldState> previousStates;
  Point2D selected={INT32_MIN,INT32_MIN};
  unordered_set<Point2D> validMoves;

 public:
  explicit Manager(Engine* pEngine) : GameObject(pEngine) {
    state.Reset();
    cout << state.toString() << endl;
  }
  void OnGui(ImGuiContext* context) override;
  void OnDraw(SDL_Renderer* renderer) override;

 private:
  Point2D mousePositionToIndex(ImVec2& pos);
  unordered_set<Point2D> getMoves(PieceType t, Point2D point);
  void drawSquare(SDL_Renderer* renderer, Color32& color, SDL_Rect& rect);
};

#endif  // CHESS_MANAGER_H
