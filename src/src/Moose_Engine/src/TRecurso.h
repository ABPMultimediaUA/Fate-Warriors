#ifndef SRC_TRECURSO_H_
#define SRC_TRECURSO_H_
#include <glm/ext.hpp>

class TRecurso {

public:
    TRecurso() = default;
    virtual ~TRecurso() = default;
	virtual char* GetNombre() = 0;
    virtual void  SetNombre(char*) = 0;
protected:
	char* _nombre;
};

#endif /* SRC_TRECURSO_H_ */