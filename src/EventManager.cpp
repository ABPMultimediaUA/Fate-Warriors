/*
 * EventManager.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: manu

*/
#include "EventManager.h"
#include <iostream>
//#include <irrlicht.h>
using namespace irr;
using namespace std;

EventManager::EventManager(){
	//cout<<"W PULSADA"<<std::endl;
	//constructor de clase
	for (u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
	            KeyIsDown[i] = false;
}

EventManager::~EventManager(){
	//destructor de clase
}

bool EventManager::OnEvent(const irr::SEvent& event){
	//cout<<"W PULSADA"<<std::endl;
		// guardamos si cada tecla esta pulsada o no
	        if (event.EventType == irr::EET_KEY_INPUT_EVENT) //si el evento que ha llamado a la funcion es de teclado...
	            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown; //guardamos si esta pulsado
	        return false;
}

bool EventManager::IsKeyDown(irr::EKEY_CODE keyCode) const{
	//cout<<"W PULSADA"<<std::endl;
	return KeyIsDown[keyCode];
}


