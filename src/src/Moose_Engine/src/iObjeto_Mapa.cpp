#include "iNodo.h"
#include "iObjeto_Mapa.h"
#include "Image_Map.h"
#include "TMooseEngine.h"

iObjeto_Mapa::iObjeto_Mapa(float x, float y, float ancho, float alto, Texture_ID_Map tipo){
    //_imagen_mapa = ASIGNAR EL OBJETO
    _imagen_mapa = TMooseEngine::get_instancia()->anyadir_elemento_al_mapa(x, y, ancho, alto, tipo);
}

iObjeto_Mapa::~iObjeto_Mapa(){
    TMooseEngine::get_instancia()->eliminar_elemento_del_mapa(_imagen_mapa);
}

void iObjeto_Mapa::setTextureposition(float x, float y){ 
    _imagen_mapa->setTextureposition(x,y);
}
