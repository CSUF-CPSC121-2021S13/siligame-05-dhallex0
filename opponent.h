#ifndef OPPONENT_H
#define OPPONENT_H

#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : GameElement(0, 0, 10, 10) {}
  OpponentProjectile(const int x, const int y) : GameElement(x, y, 10, 10) {}

  void Draw(graphics::Image& background) override;
  void Move(const graphics::Image& background) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : GameElement(0, 0, 50, 50) {}
  Opponent(const int x, const int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image& background) override;
  void Move(const graphics::Image& background) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int tracker_ = 0;
};

#endif
