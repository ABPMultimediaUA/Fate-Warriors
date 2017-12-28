/*
#ifndef Objeto_Estandar_H_
#define Objeto_Estandar_H_

#include "Objeto.h"

class Matcher;

class Objeto_Estandar : public Objeto{
public:
    Objeto_Estandar(short _id, float _i_x, float _i_y, float _i_z, char* ruta);
    Objeto_Estandar(short _id, float _i_x, float _i_y, float _i_z, char* ruta, char* modelo);

    void render() override;
    void update() override;
    
    ~Objeto_Estandar();        
private:
    Matcher* _matcher;
};

#endif
*/