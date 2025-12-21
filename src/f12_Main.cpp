#include "GUIEngine.h"
#include <memory>
#include "Label.h"
#include "Button.h"
#include <iostream>

using namespace gui;
using namespace std;

LabelPtr label;
int value = 0;
void funk(string txt){
    if (txt == "Öka")
        value++;
    else
        value--;
    label->setText(to_string(value));
}

int main(){
    CompPtr c1 = Button::make(100,100,100,75,"Öka",funk);
    CompPtr c2 = Button::make(400,100,100,75,"Minska",funk);
    label = Label::make(260,100,80,75,"0");
    eng.add(c1);
    eng.add(c2);
    eng.add(label);
    eng.run();
}