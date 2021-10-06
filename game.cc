#include "game.h"

void Game::Start() { gameScreen.ShowUntilClosed(); }

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponentVector.size(); i++) {
    if (opponentVector[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> newProjectile =
          std::make_unique<OpponentProjectile>(opponentVector[i]->GetX(),
                                               opponentVector[i]->GetY());
      o_projectile_.push_back(std::move(newProjectile));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = 0; i < opponentVector.size(); i++) {
    if (opponentVector[i]->GetIsActive() != true) {
      opponentVector.erase(opponentVector.begin());
      i -= 1;
    }
  }

  for (int j = 0; j < o_projectile_.size(); j++) {
    if (o_projectile_[j]->GetIsActive() != true) {
      o_projectile_.erase(o_projectile_.begin());
      j -= 1;
    }
  }

  for (int k = 0; k < p_projectile_.size(); k++) {
    if (p_projectile_[k]->GetIsActive() != true) {
      p_projectile_.erase(p_projectile_.begin());
      k -= 1;
    }
  }
}
