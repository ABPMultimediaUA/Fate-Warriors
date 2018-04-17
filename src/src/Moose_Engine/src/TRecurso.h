#ifndef SRC_TRECURSO_H_
#define SRC_TRECURSO_H_
#include <glm/ext.hpp>

class TRecurso {

public:
    TRecurso() = default;
    virtual ~TRecurso() = default;
	virtual std::string GetNombre() = 0;
    virtual void  SetNombre(std::string) = 0;
protected:
	std::string _nombre;
};

#endif /* SRC_TRECURSO_H_ */