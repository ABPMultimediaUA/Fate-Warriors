#ifndef SRC_INODOLUZ_H_
#define SRC_INODOLUZ_H_
#include "../../Utilidades/Vector.h"
#include "iNodo.h"

class iNodoLuz : public iNodo{
    public:

        iNodoLuz(bool activa, float intensidad, Vector3 ambient,
                                                Vector3 specular,
                                                Vector3 diffuse);

        iNodoLuz(bool activa, float intensidad, Vector3 ambient,
                                                Vector3 specular,
                                                Vector3 diffuse,
                                                float x, float y, float z);
        
        ~iNodoLuz();
    private:
};

#endif