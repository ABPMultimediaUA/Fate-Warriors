#ifndef SRC_TRECURSOMATERIAL_H_
#define SRC_TRECURSOMATERIAL_H_
#include "TRecurso.h"

class aiMaterial;
class TRecursoMaterial : public TRecurso{
//la carga de assimp esta basada en learnopengl
public:
    TRecursoMaterial(std::string nombre);
    ~TRecursoMaterial();

    std::string GetNombre() override;
    void  SetNombre(std::string nombre) override;
    inline unsigned int Get_id(){return _id;}
    inline std::string Get_type(){return _type;}
private:
    unsigned int _id;
    std::string _type;
    std::string _path;
    void cargarFichero(const char* path);
};

#endif /* SRC_TRECURSOMATERIAL_H_ */