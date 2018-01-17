
#include <iostream>
#include "FMOD/fmod_studio.hpp"
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"


int main(int argv, char*args[])
{ 
  Interfaz_sonido* sonido = new Interfaz_sonido();

  sonido->CreateSound();

  

  char algo;
  do{
    std::cin>>algo;
    switch(algo){
      case '1': sonido->PasosCadena();
      break;
      case '2': sonido->PasosArena();
      break;
      case '3': sonido->PasosAsfalto();
      break;
    }
  }while(algo!='0');
  delete sonido;
  return 0;
}
