#include "Matcher.h"
#include "Interfaz.h"
#include "Interfaz_Fisica.h"
#include "../Utilidades/Vector.h"


//constructor para modelado sin comprimir (una sola ruta de archivo)
Matcher::Matcher(char* ruta, float x, float y, float z, int masa, bool isProta):_interfaz_graficos(Interfaz::Interfaz_getInstance())
                                                        ,_interfaz_fisicas(Interfaz_Fisica::Interfaz_Fisica_GetInstance())
                                                        ,_posicion(x,y,z)
                                                        {
    _jumping = false;
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
                                                        ,_posicion(x,y,z)
                                                        {
    _jumping = false;
    _isProta = isProta;
    _posicion = Vector3(x,y,z);
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
mov = _interfaz_fisicas->Saltar(_identificador_fisico, 30);
        _interfaz_graficos->Interfaz_moverModeloProta(_identificador_grafico, mov._x, mov._y, mov._z);
        
*/

Vector3 Matcher::getPosition(){
    return _posicion;
}

//version especifica para el objeto personaje
void Matcher::Mover(float x, float y, float z){
    //std::cout<<"matcher mover"<<std::endl;
    Vector3 vectorsito(x,y,z);
    if(!_isProta){
        _posicion = _interfaz_fisicas->moverObjeto(vectorsito, _identificador_fisico);
        _interfaz_graficos->Interfaz_moverModelo(_identificador_grafico, _posicion._x, _posicion._y, _posicion._z);
    }
    else{
        _posicion = _interfaz_fisicas->moverObjeto(vectorsito, _identificador_fisico);
        _interfaz_graficos->Interfaz_moverProta(_posicion._x,_posicion._z);
    }

    if(this->getPosition()._y>20){
        _jumping = false;
    }
    else{
        _jumping = true;
    }
    //std::cout<<"YEEEEEEEEEEEE: "<<_posicion._y<<std::endl;

}

void Matcher::Saltar(){
    std::cout<<"SALTO"<<std::endl;
    //Vector3 vectorsito(x,y,z);
    Vector3 mov(0,0,0); 
        if(_jumping){
            mov = _interfaz_fisicas->Saltar(_identificador_fisico, 20);
            _interfaz_graficos->Interfaz_moverModelo(_identificador_grafico, mov._x, mov._y, mov._z);
            mov = _interfaz_fisicas->Saltar(_identificador_fisico, 30);
            _interfaz_graficos->Interfaz_moverModelo(_identificador_grafico, mov._x, mov._y, mov._z);
            mov = _interfaz_fisicas->Saltar(_identificador_fisico, 35);
            _interfaz_graficos->Interfaz_moverModelo(_identificador_grafico, mov._x, mov._y, mov._z);
            mov = _interfaz_fisicas->Saltar(_identificador_fisico, 37);
            _interfaz_graficos->Interfaz_moverModelo(_identificador_grafico, mov._x, mov._y, mov._z);
        }
}

Matcher::~Matcher(){

}