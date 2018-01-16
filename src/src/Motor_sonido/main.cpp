
#include <iostream>
#include "FMOD/fmod_studio.hpp"
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"


int main(int argv, char*args[])
{ 
  Interfaz_sonido* sonido = new Interfaz_sonido();

  sonido->CreateSound();

  sonido->Disparar();

  char algo;
  std::cin>>algo;
  if(algo=='1'){
  delete sonido;
  }
  return 0;
}
