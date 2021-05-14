#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"
class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int& width, const int& height) {
    gameScreen.Initialize(width, height);
  }

  void CreateOpponents() {
    std::unique_ptr<Opponent> enemy =
        std::make_unique<Opponent>(gameScreen.GetWidth() / 2, 0);
    opponentVector.push_back(std::move(enemy));
  }

  void Init() {
    player_.SetX(300);
    player_.SetY(400);
    gameScreen.AddMouseEventListener(*this);
    gameScreen.AddAnimationEventListener(*this);
  }

  void Start();

  graphics::Image& GetGameScreen() { return gameScreen; }
  std::vector<std::unique_ptr<Opponent>>& GetOpponents() {
    return opponentVector;
  }
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return o_projectile_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() {
    return p_projectile_;
  }
  Player& GetPlayer() { return player_; }

  void MoveGameElements() {
    for (int i = 0; i < opponentVector.size(); i++) {
      if (opponentVector[i]->GetIsActive()) {
        opponentVector[i]->Move(gameScreen);
      }
    }

    for (int j = 0; j < o_projectile_.size(); j++) {
      if (o_projectile_[j]->GetIsActive()) {
        o_projectile_[j]->Move(gameScreen);
      }
    }

    for (int k = 0; k < p_projectile_.size(); k++) {
      if (p_projectile_[k]->GetIsActive()) {
        p_projectile_[k]->Move(gameScreen);
      }
    }
  }

  void FilterIntersections() {
    for (int i = 0; i < opponentVector.size(); i++) {
      if (opponentVector[i]->IntersectsWith(&player_)) {
        opponentVector[i]->SetIsActive(false);
        player_.SetIsActive(false);
        has_lost_ = true;
      }
    }

    for (int j = 0; j < o_projectile_.size(); j++) {
      if (o_projectile_[j]->IntersectsWith(&player_)) {
        o_projectile_[j]->SetIsActive(false);
        player_.SetIsActive(false);
        has_lost_ = true;
      }
    }

    for (int k = 0; k < p_projectile_.size(); k++) {
      for (int p = 0; p < opponentVector.size(); p++) {
        if (p_projectile_[k]->IntersectsWith(opponentVector[p].get())) {
          p_projectile_[k]->SetIsActive(false);
          opponentVector[p]->SetIsActive(false);
          if (player_.GetIsActive() == true) {
            score_ += 1;
          }
        }
      }
    }
  }

  void UpdateScreen() {
    std::string message = "Score: ";
    message += score_;
    gameScreen.DrawRectangle(0, 0, gameScreen.GetWidth(),
                             gameScreen.GetHeight(), 255, 255, 255);
    gameScreen.DrawText(0, 0, message, 18, 0, 0, 0);
    if (has_lost_ == true) {
      gameScreen.DrawText(gameScreen.GetWidth() / 2, gameScreen.GetHeight() / 2,
                          "Game Over", 18, 0, 0, 0);
    }

    for (int i = 0; i < opponentVector.size(); i++) {
      if (opponentVector[i]->GetIsActive()) {
        opponentVector[i]->Draw(gameScreen);
      }
    }

    for (int j = 0; j < o_projectile_.size(); j++) {
      if (o_projectile_[j]->GetIsActive()) {
        o_projectile_[j]->Draw(gameScreen);
      }
    }

    for (int k = 0; k < p_projectile_.size(); k++) {
      if (p_projectile_[k]->GetIsActive()) {
        p_projectile_[k]->Draw(gameScreen);
      }
    }
    if (player_.GetIsActive()) {
      player_.Draw(gameScreen);
    }
  }

  void OnAnimationStep() override {
    if (opponentVector.size() == 0) {
      CreateOpponents();
    }
    MoveGameElements();
    LaunchProjectiles();
    FilterIntersections();
    RemoveInactive();
    UpdateScreen();
    gameScreen.Flush();
  }

  void OnMouseEvent(const graphics::MouseEvent& event) override {
    if (event.GetX() > 0 && event.GetX() < gameScreen.GetWidth() &&
        event.GetY() > 0 && event.GetY() < gameScreen.GetHeight()) {
      player_.SetX(event.GetX() - (player_.GetWidth() / 2));
      player_.SetY(event.GetY() - (player_.GetHeight() / 2));
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> newPlayProjectile =
          std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY());
      p_projectile_.push_back(std::move(newPlayProjectile));
    }
  }

  int GetScore() const { return score_; }
  bool HasLost() const { return has_lost_; }
  void LaunchProjectiles();
  void RemoveInactive();

 private:
  graphics::Image gameScreen;
  std::vector<std::unique_ptr<Opponent>> opponentVector;
  std::vector<std::unique_ptr<OpponentProjectile>> o_projectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> p_projectile_;
  Player player_;
  int score_ = 0;
  bool has_lost_ = false;
};

#endif
