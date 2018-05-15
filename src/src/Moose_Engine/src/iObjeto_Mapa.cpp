#include "iNodo.h"
#include "iObjeto_Mapa.h"
#include "Image_Map.h"
#include "TMooseEngine.h"



iObjeto_Mapa::iObjeto_Mapa(){
    //_imagen_mapa = ASIGNAR EL OBJETO
}

iObjeto_Mapa::~iObjeto_Mapa(){
    
}

void iObjeto_Mapa::setTextureposition(float x, float y){
    _imagen_mapa->setTextureposition(x,y);
}
