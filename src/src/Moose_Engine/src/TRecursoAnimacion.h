#ifndef SRC_TRECURSOANIMACION_H_
#define SRC_TRECURSOANIMACION_H_
#include "TRecurso.h"
#include <vector>
#include <cstdint>
class Shader;
class TRecursoModelado;
class TRecursoAnimacion : public TRecurso{

public:
    TRecursoAnimacion(std::vector<TRecursoModelado*> _i_modelos, const char* _i_nombre);
    ~TRecursoAnimacion();

    char* GetNombre() override;
    void  SetNombre(char* nombre) override;
    void  draw(Shader* shader, uint8_t num);
private:
    std::vector<TRecursoModelado*> _modelos;

};
#endif