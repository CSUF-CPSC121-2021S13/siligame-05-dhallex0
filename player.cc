#include "player.h"

void Player::Draw(graphics::Image& background) {
  std::string player = "playerobject.bmp";
  ImageLoader(background, x_, y_, player);
}

void Player::Move(const graphics::Image& background) {}

void PlayerProjectile::Draw(graphics::Image& background) {
  std::string playerProjectile = "playerprojectile.bmp";
  ImageLoader(background, x_, y_, playerProjectile);
}

void PlayerProjectile::Move(const graphics::Image& background) {
  if (!IsOutOfBounds(background)) {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  } else {
    isActive = false;
  }
}
