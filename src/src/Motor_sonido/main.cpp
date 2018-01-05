
#include <iostream>
#include "FMOD/fmod_studio.hpp"
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"


int main8(int argv, char*args[])
{
  Interfaz_sonido* sonido = new Interfaz_sonido();

  sonido->CreateSound();

  
  sonido->Disparar();
  sonido->Disparar();
  sonido->Disparar();
  sonido->Disparar();
  sonido->Disparar();
  sonido->Disparar();
  sonido->Disparar();
  

  delete sonido;

  return 0;
}
