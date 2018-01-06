#include "GUI.h"
#include "SFML/Graphics.hpp"
#include <cmath>

GUI::GUI(IrrlichtDevice *_i_device){
	_guienv = _i_device->getGUIEnvironment();
	_text = _guienv->addStaticText(L"", rect<s32>(35, 35, 200, 70), true, false, 0);
}

GUI::~GUI(){
	delete _text;
	_guienv->drop();
}


void GUI::set_text_vida(int _i_vida){
	int vida = 12;
	core::stringw str = L"Salud: ";     
    str += _i_vida;     

    _text->setText(str.c_str());
}

void GUI::draw(){
	_guienv->drawAll();
}