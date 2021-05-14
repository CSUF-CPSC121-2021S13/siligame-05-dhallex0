#include "opponent.h"

void Opponent::Draw(graphics::Image& background) {
  std::string opponent = "opponent.bmp";
  ImageLoader(background, x_, y_, opponent);
}

void Opponent::Move(const graphics::Image& background) {
  if (!IsOutOfBounds(background)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    isActive = false;
  }
}

void OpponentProjectile::Draw(graphics::Image& background) {
  std::string opponentProjectile = "projectile.bmp";
  ImageLoader(background, x_, y_, opponentProjectile);
}

void OpponentProjectile::Move(const graphics::Image& background) {
  if (!IsOutOfBounds(background)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    isActive = false;
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  tracker_ = tracker_ + 1;
  if (tracker_ % 10 == 0) {
    std::unique_ptr<OpponentProjectile> oProjectile =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(oProjectile);
  } else {
    return nullptr;
  }
}
