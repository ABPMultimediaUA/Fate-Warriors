#include "Matcher.h"
#include "Interfaz.h"
#include "Interfaz_Fisica.h"
#include "../Utilidades/Vector.h"


//constructor para modelado sin comprimir (una sola ruta de archivo)
Matcher::Matcher(char* ruta, float x, float y, float z, int masa, bool isProta):_interfaz_graficos(Interfaz::Interfaz_getInstance())
                                                        ,_interfaz_fisicas(Interfaz_Fisica::Interfaz_Fisica_GetInstance())
                                                        {
    _isProta = isProta;
    
    if(!isProta){
        _identificador_fisico  = _interfaz_fisicas->CargaRigidBody(masa, x, y, z);
        _identificador_grafico = _interfaz_graficos->Interfaz_cargaModelo(ruta, false, x, y, z);     
    }
    else{
        _identificador_fisico  = _interfaz_fisicas->CargaRigidBody(masa, x, y, z);
        _identificador_grafico = _interfaz_graficos->Interfaz_crearProta(ruta, false, x, y, z);     
    }
}

//constructor para modelado comrpimido (ruta del .zip + nombre del archivo de modelado dentro)
Matcher::Matcher(char* ruta, char* nombreModelado, float x, float y, float z, int masa, bool isProta):
                                                        _interfaz_graficos(Interfaz::Interfaz_getInstance())
                                                        ,_interfaz_fisicas(Interfaz_Fisica::Interfaz_Fisica_GetInstance())
                                                        {
    _isProta = isProta;

    if(!isProta){
        _identificador_fisico = _interfaz_fisicas->CargaRigidBody(masa, x, y, z);
        _identificador_grafico = _interfaz_graficos->Interfaz_cargaModeloZip(ruta, nombreModelado, false, x, y, z);      
    }
    else{  
        _identificador_fisico = _interfaz_fisicas->CargaRigidBody(masa, x, y, z);        
        _identificador_grafico = _interfaz_graficos->Interfaz_crearProtaZip(ruta, nombreModelado, false, x, y, z);
    }

}

/*
void Matcher::Mover(float x, float y, float z){
    std::cout<<"matcher mover"<<std::endl;
    Vector3 vectorsito(x,y,z);
    Vector3 mov(0,0,0); 
    std::cout<<"identificador fisico: "<<_identificador_fisico<<std::endl;
    mov = _interfaz_fisicas->moverObjeto(vectorsito, _identificador_fisico);
    _interfaz_graficos->Interfaz_moverProta(mov._x,mov._z);
}

*/

//version especifica para el objeto personaje
void Matcher::Mover(float x, float y, float z){
    //std::cout<<"matcher mover"<<std::endl;
    Vector3 vectorsito(x,y,z);
    Vector3 mov(0,0,0); 
    
    if(!_isProta){
        mov = _interfaz_fisicas->moverObjeto(vectorsito, _identificador_fisico);
        _interfaz_graficos->Interfaz_moverModelo(_identificador_grafico, mov._x, mov._y, mov._z);
    }
    else{
        mov = _interfaz_fisicas->moverObjeto(vectorsito, _identificador_fisico);
        _interfaz_graficos->Interfaz_moverProta(mov._x,mov._z);
    }

}


Matcher::~Matcher(){

}