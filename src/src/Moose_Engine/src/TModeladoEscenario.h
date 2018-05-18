#ifndef SRC_TMODELADOESCENARIO_H_
#define SRC_TMODELADOESCENARIO_H_
#include "TModelado.h"
class TRecursoMalla;
class TRecursoModelado;
class TFichero;

class Shader;
//clase hecha para evitar su dibujado en el dibujado de sombras
class TModeladoEscenario : public TModelado{
    public:
        TModeladoEscenario(const char* path);
        ~TModeladoEscenario()=default;
        
        void draw(Shader* _i_shader) override;
    private:

};

#endif /* SRC_TMODELADO_H_ */