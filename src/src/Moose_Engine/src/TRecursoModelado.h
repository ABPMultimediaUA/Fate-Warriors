#ifndef SRC_TRECURSOMODELADO_H_
#define SRC_TRECURSOMODELADO_H_
#include "TRecurso.h"
#include <vector>
class TRecursoMalla;
class Shader;
class TRecursoModelado : public TRecurso{

public:
    TRecursoModelado(std::vector<TRecursoMalla*> _i_mallas, const char* _i_nombre);
    ~TRecursoModelado();
    void draw(Shader* _i_shader);
    std::string GetNombre() override;
    void  SetNombre(std::string nombre) override;
    void set_BB(glm::vec3 _i_BB);
    glm::vec3 get_BB();
private:
    std::vector<TRecursoMalla*> _mallas;
    glm::vec3 _BB;
    
};

#endif /* SRC_TRECURSOModelado_H_ */