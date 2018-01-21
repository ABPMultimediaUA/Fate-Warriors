
#include <iostream>
#include "FMOD/fmod_studio.hpp"
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"


int main(int argv, char*args[])
{ 
  Interfaz_sonido* sonido = new Interfaz_sonido("txt/bancosonidos.txt");

  
  
  sonido->Play_pasos(3);
  sonido->set_volumen_sfx(0.1);
 char algo;
  std::cin>>algo;
  /*sonido->pause();
  algo;
  std::cin>>algo;*/
  delete sonido;
  return 0;
}
