#include "game_element.h"

#include "cpputils/graphics/image.h"

void GameElement::ImageLoader(graphics::Image& background, int& x_, int& y_,
                              std::string& character) {
  const graphics::Color black = graphics::Color(0, 0, 0);

  graphics::Image image;
  image.Load(character);
  for (int i = 0; i < image.GetWidth(); i++) {
    for (int j = 0; j < image.GetHeight(); j++) {
      if (image.GetColor(i, j) != black) {
        background.SetColor(i + x_, j + y_, image.GetColor(i, j));
      } else {
        continue;
      }
    }
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image& background) {
  if (x_ < 0 || y_ < 0 || x_ > background.GetWidth() ||
      y_ > background.GetHeight()) {
    return true;
  } else {
    return false;
  }
}
