#ifndef SRC_TRECURSOMODELADO_H_
#define SRC_TRECURSOMODELADO_H_
#include "TRecurso.h"

class TRecursoModelado : public TRecurso{

public:
    TRecursoModelado();
    ~TRecursoModelado();

    char* GetNombre() override;
    void  SetNombre(char* nombre) override;
    void cargarFichero(char* nombre);
private:
};

#endif /* SRC_TRECURSOModelado_H_ */