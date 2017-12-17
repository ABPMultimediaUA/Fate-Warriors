#ifndef Matcher_H_
#define Matcher_H_

#include "../Utilidades/Vector.h"
#include <iostream>

class Interfaz;
class Interfaz_Fisica; 
struct Vector3;
class Matcher{

public:
    Matcher(char* ruta, float x, float y, float z, int masa, bool isProta);
    Matcher(char* ruta, char* nombreModelado, float x, float y, float z, int masa, bool isProta);
    void Mover(float x, float y, float z);
    void Saltar(); 
    Vector3 getPosition();
    ~Matcher();

private:
    unsigned short _identificador_fisico;   //identificador del objeto en el motor bullet
    unsigned short _identificador_grafico;  //identificador del objeto en el motor grafico
    Interfaz*        _interfaz_graficos;
    Interfaz_Fisica* _interfaz_fisicas;
    Vector3        _posicion;
    bool           _jumping;
    bool           _isProta; //controla si se trata del objeto especial del protagonista
    
};

#endif