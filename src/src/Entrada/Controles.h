#ifndef SRC_CONTROLES_H_
#define SRC_CONTROLES_H_

#include "Input.h"

class Controles{
public:
	virtual ~Controles();
	bool estaPulsada(Input_key key);
	static Controles* Instance();
private:
	static Controles* instancia;
	Controles();
};

#endif /* SRC_CONTROLES_H_ */
