#ifndef Matcher_H_
#define Matcher_H_

class Interfaz;
class Interfaz_Fisica;
class Vector; 

class Matcher{

public:
    Matcher(char* ruta, float x, float y, float z, int masa, bool isProta);
    Matcher(char* ruta, char* nombreModelado, float x, float y, float z, int masa, bool isProta);
    void Mover(float x, float y, float z);
    ~Matcher();

private:
    unsigned short _identificador_fisico;   //identificador del objeto en el motor bullet
    unsigned short _identificador_grafico;  //identificador del objeto en el motor grafico
    Interfaz*        _interfaz_graficos;
    Interfaz_Fisica* _interfaz_fisicas;
    bool           _isProta; //controla si se trata del objeto especial del protagonista
};

#endif