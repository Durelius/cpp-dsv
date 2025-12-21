#include "Component.h"
#include "GUIEngine.h"
#include <memory>
#include "Label.h"
#include "Button.h"
#include "Player.h"
#include "Sprite.h"
#include <iostream>

using namespace gui;
using namespace std;

LabelPtr label;

int main(){
    CompPtr p1 = Player::make(100, 100, 50, 50, "resources/images/ship.png");
    eng.add(p1);
    eng.run();
}
