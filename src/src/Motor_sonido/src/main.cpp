
#include <iostream>
#include "FMOD/fmod_studio.hpp"
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"


int main(int argv, char*args[])
{ 
  Interfaz_sonido* sonido = new Interfaz_sonido("txt/bancosonidos.txt");

  
  
  //sonido->Play_pasos(0);
  //sonido->set_volumen_sfx(0.1);
  char algo;
  //std::cin>>algo;
  do{
    std::cin>>algo;
    switch(algo){
      case '2':sonido->Play_pasos(0);
      break;
      case '3':sonido->Stop_pasos(0);
      break;
    }

  }while(algo!='1');
  //sonido->Stop_pasos(0);
  //algo;
  //std::cin>>algo;
  delete sonido;
  return 0;
}
