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

    std::string GetNombre() override;
    void  SetNombre(std::string nombre) override;
    void  draw(Shader* shader, uint8_t num);
    inline uint8_t get_anim_cont(){
        return _modelos.size();
    }
private:
    std::vector<TRecursoModelado*> _modelos;

};
#endif