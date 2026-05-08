#include "engine.h"
class Foo : public sgr::Engine {

  void init() override {};
  void update(uint64_t deltaTime) override {};
  void handleEvents(sf::RenderWindow &window) override {
    while (const std::optional event = window.pollEvent())
      if (event->is<sf::Event::Closed>())
        close();
  };

public:
  ~Foo() {}
};
int main(int argc, char *argv[]) {
  Foo testUnit{};
  testUnit.run();
  return 0;
}
