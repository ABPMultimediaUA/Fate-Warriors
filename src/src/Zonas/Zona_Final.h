#ifndef ZONA_FINAL_H_
#define ZONA_FINAL_H_

#include "Zona.h"

class Zona_Final : public Zona{
public:
	Zona_Final(float _i_x, float _i_y, float _i_z, int long_x, int long_y, uint16_t num_enemigos, int rondas, uint8_t crec_enem, uint8_t music_ini);
    ~Zona_Final();
    void actualizar_zona() override; 

private:
    void iniciar_zona_final();
    void update_zona_fina();
    bool _zona_fina_iniciado;
    uint16_t _num_enemigos;
    int _rondas;

    uint8_t _crecimiento_enemigos;
    
    uint8_t _musica_inicio;
};

#endif /* ZONA_FINAL_H_ */