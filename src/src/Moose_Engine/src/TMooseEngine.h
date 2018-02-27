#ifndef SRC_TMOOSEENGINE_H_
#define SRC_TMOOSEENGINE_H_

#include <cstdint>
#include <glm/ext.hpp>
class TNodo;
class TGestorRecursos;
class TEntidad;
class TTransform;
class TCamara;
class TLuz;
class TModelado;
class Mapeado;
class Shader;
class GLFWwindow;


class TMooseEngine{

    public:
        TMooseEngine();
        ~TMooseEngine();

        TNodo*      crearNodo(TNodo *padre, TEntidad *ent);
        TNodo*      crearNodoCamara(TNodo *padre, TEntidad *ent);
        TNodo*      crearNodoLuz(TNodo *padre, TEntidad *ent);
        TTransform* crearTransform();
        TCamara*    crearCamara();
        TLuz*       crearLuz();
        TModelado*     crearModelado(char* _i_path);

        void        drawLuces();
        void        drawCamaras();

        inline TNodo* nodoRaiz(){
            return _escena;
        }
        void draw();
        bool ventana_abierta();

    private:
        Mapeado *_mapping_camaras;
        Mapeado *_mapping_luces;
        TNodo* _escena;
        TGestorRecursos* _gestorRecursos;
        uint16_t _contadorIDEntidad;
        uint8_t _n_camaras, _n_c_actual;
        uint8_t _n_luces, _n_l_actual;

        glm::mat4 matriz_luz = glm::mat4(1.0f);
        glm::mat4 matriz_view = glm::mat4(1.0f);
        GLFWwindow* window;
        Shader *_shader;        


        void init_opengl();
        void clear();
        
        //atributos para camaras, luces y demás
};


#endif /* SRC_TMOOSEENGINE_H_ */