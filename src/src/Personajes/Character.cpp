#include "Character.h"

#include "Inventario.h"
#include "NPC.h"
#include "NPC_Manager.h"
#include "Player.h"
#include "../Tiempo/Time.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Interactuables/Llave.h"
#include "../Interactuables/Puerta.h"
#include "../Interactuables/Interactuable_Manager.h"
#include "../Interactuables/Interruptor.h"
#include "../Consumibles/Consumible_Action.h"
#include "../Interfaz/Motor.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Zonas/Respawn.h"

#include "../Motor_sonido/Interfaz_sonido.h"
#include "../Moose_Engine/src/iObjeto_Mapa.h"


#include <iostream>

Character::Character(short _id, float _i_x, float _i_y, float _i_z, int16_t _i_vida, float _i_velocidad,
    int16_t _i_danyo_ataque_normal, int16_t _i_danyo_ataque_fuerte, Enum_Equipo _i_equipo) 
    :Objeto(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _vida_maxima(_i_vida), _velocidad(_i_velocidad),
    _danyo_ataque_normal(_i_danyo_ataque_normal), _danyo_ataque_fuerte(_i_danyo_ataque_fuerte){

    _zona_en_la_que_se_encuentra = nullptr;
    _inmortal = false;
    _inventario = new Inventario();
    _tiempo = Time::Instance();
    _accion = Nada;
    _tipo_ataque = Ataque_Ninguno;
    _tiempo_inicio_accion = 0;
    _duracion_accion_actual = 0;
    _velocidadAndar = _i_velocidad;
    _velocidadCorrer = _i_velocidad * 2;
    _rb_ataque = Motor::Motor_GetInstance()->crear_rb_ataque();
    _equipo = _i_equipo;
    _bloqueado = false;
    _npcs_persiguiendome = 0;
       

    _sonido= Interfaz_sonido::GetInstancia();
}

Character::~Character() {
    delete _inventario;
    Motor::Motor_GetInstance()->borrar_rb(_rb_ataque);
}


void Character::eliminar_npc_mapa(){
    delete _yo;
    _yo = nullptr;
}

void Character::dibujar_npc(){
    if (_yo==nullptr){
        _yo = new iObjeto_Mapa(getX(), getZ(), 12,12, Enum_Enemigo);
    }
    else{
        _yo->setTextureposition(getX(), getZ());
    }
}

int16_t Character::get_vida(){
	return _vida;
}

Enum_Equipo Character::get_equipo(){
    return _equipo;
}

void Character::activar_inmunidad_a_danyos(){
    _inmortal = true;
}

void Character::desactivar_inmunidad_a_danyos(){
    _inmortal = false;
}

void Character::modificar_vida_en(int16_t _i_vida){

	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida <= 0){
        morir();
    }
    else{
        _vida+=_i_vida;
    }
}

void Character::danyar_comun(int16_t _danyo){

    if(!_inmortal){
        _vida = _vida - _danyo;

        if(_accion == Accion_pre_atacar){
            //std::cout << "Ataque cortado" << std::endl;
        }

        set_accion(Recibir_danyo);
        play_animaciones_recibir_danyo();

        if(_vida <= 0){
            morir();
        }
    }
}

void Character::set_vida(int16_t _i_vida){
	_vida=_i_vida;
}

Inventario* Character::get_inventario(){
    return _inventario;
}

bool Character::isDead(){
    if(_vida>0){
        return false;
    }
    return true;
}

bool Character::puede_subir_vida_(int16_t _i_vida){
    if(_vida==_vida_maxima){
        return false;
    }
    return true;
}

int16_t Character::get_danyo_ataque_normal(){
	return _danyo_ataque_normal;
}

int16_t Character::get_danyo_ataque_fuerte(){
	return _danyo_ataque_fuerte;
}

void Character::atacar(Enum_Tipo_Ataque _i_tipo_ataque){
    // Ataque de player y aliados, sobrescrbir en Enemigo
    // Se ataca a enemigos
    if(_accion == Saltar && (_i_tipo_ataque == Ataque_Normal || _i_tipo_ataque == Ataque_Fuerte)){
        _i_tipo_ataque = Ataque_Salto;
        std::cout << "ATAQUE CON SALTO"<< std::endl;
    }

    if(
        this->get_tipo_ataque() == Ataque_Ninguno && esta_bloqueado() == false && 
        (
            _accion != Saltar ||
            _accion == Saltar && _i_tipo_ataque == Ataque_Salto
        )
        ){

        set_tipo_ataque(_i_tipo_ataque);
        set_accion(Accion_pre_atacar);
        play_animaciones_ataque();
    }
    else if(
            _accion == Accion_post_atacar && _tipo_ataque != Ataque_Salto && _tipo_ataque != Ataque_Especial && _tipo_ataque != Ataque_Normal_Normal 
            && _tipo_ataque != Ataque_Normal_Fuerte && _tipo_ataque != Ataque_Fuerte_Normal && _tipo_ataque != Ataque_Fuerte_Fuerte  
            ) {
                
        Enum_Tipo_Ataque _ataque_combo;
        _ataque_combo = get_tipo_ataque_combo(_i_tipo_ataque);

        set_tipo_ataque(_ataque_combo);
        set_accion(Accion_pre_atacar);
        
        play_animaciones_ataque();      // Sirve para los combos
        
    }
}

void Character::esquivar(uint16_t _direccion){
    if(esta_bloqueado() == false){
        set_accion(Accion_Dash);
        _sonido->Stop_pasos();
        _sonido->Play_personaje(0);
        _objeto_motor->cambiar_modelado("Anim_dash_jugador", 17);
    }
    
}

void Character::saltar(){
    if(esta_bloqueado() == false && _accion != Saltar){
        set_accion(Saltar);
        _objeto_motor->saltar();
    }
}

void Character::mover(uint16_t _i_direccion){
    mover_direccion(_i_direccion, _i_direccion);
}

void Character::mover_direccion(uint16_t _i_direccion, uint16_t _i_direccion_mover){
    if(esta_bloqueado() == false){ 

        _direccion_actual = _i_direccion;
            
        if(get_accion() == Nada){
            set_accion(Andar);
            _velocidad = _velocidadAndar;
            animacion_andar();
        }
        else if(get_accion() == Andar){
            //std::cout << "Andando" << std::endl;
            if(_velocidad<_velocidadAndar){
                _velocidad += 0.05;
                animacion_andar();
            }
            if(accion_en_curso() == false){
                set_accion(Accion_Correr);
                animacion_correr();
            }
        }
        else if(_accion == Accion_Correr){
            //std::cout << "CORRIENDO" << std::endl;
            animacion_correr();
            if(_velocidad<_velocidadCorrer){
                _velocidad += 0.1;
            }
        }
        _objeto_motor->VelocidadDireccion(_i_direccion,_velocidad,_tiempo->get_tiempo_desde_ultimo_update(), _i_direccion_mover);
    }
}

bool Character::interactuar_con_objeto(){
    //Busca el objeto interactuable mas cercano e interactua con el (recogerlo, abrirlo, etc.)
    Interactuable_Manager * _int_man  = Game::game_instancia()->game_get_datos()->get_interactuable_manager();
    
    Llave** _llaves = _int_man->get_llaves();
    Puerta** _puertas = _int_man->get_puertas();

    std::vector<Interruptor*> _interruptores = _int_man->get_interruptores();
    unsigned short n_interruptores = _interruptores.size();


    unsigned short _cont;
    bool objeto_encontrado = false;

    //Busca palancas y la usa 

    for(_cont = 0; _cont < n_interruptores && objeto_encontrado == false; _cont++) {
		if( comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _interruptores[_cont]->get_vector(), 3) == true){
            // Encuentra palanca e intenta accionarla
            
            _interruptores[_cont]->iniciar_interruptor();
            objeto_encontrado = true;
       //     std::cout << "Usa palanca"<< std::endl;
        }
	}




    // Busca llave y la coge

    for(_cont = 0; _cont < _int_man->get_n_llaves() && objeto_encontrado == false; _cont++) {
		if( _llaves[_cont]->get_visible() == true && 
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _llaves[_cont]->get_vector(), 3) == true)
        {
            // Recoge llave y la anyade al inventario
            recoge_llave(_llaves[_cont]);
            objeto_encontrado = true;
        }
	}
	
    // Busca puerta y la abre

	for(_cont = 0; _cont < _int_man->get_n_puertas() && objeto_encontrado == false; _cont++) {
		if( _puertas[_cont]->get_visible() == true && 
            _puertas[_cont]->get_abierta() == false && 
            comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _puertas[_cont]->get_vector(), 3) == true)
        {
            std::vector<Llave*> _llaves_character = this->get_inventario()->get_llaves();
            
            for (short i = 0; i < _llaves_character.size(); ++i) {
                if(_llaves_character[i]->get_id_puerta() == _puertas[_cont]->get_id()){ // Abre la puerta y elimina la llave del inventario
                    abrir_puerta(_puertas[_cont], _llaves_character[i]);
                    objeto_encontrado = true;
                }
            }
        }
	}

    return objeto_encontrado;
}

void Character::morir(){ // SE SOBRESCRIBE EN NPC!!
    _zona_en_la_que_se_encuentra = nullptr;
    Respawn::posiciones_instancia()->anyadir_character_y_tiempo_para_reaparecer(this, _tiempo->get_current()+9000);
    //setY(99999999999);
}

void Character::revivir(Vector2 pos){ 
    set_vida(_vida_maxima);
    setY(2);
    pos_x_azar_en_zona = pos._x;
    pos_y_azar_en_zona = pos._y;

    setPositionXZ(pos._x, pos._y);
    
    _npcs_persiguiendome = 0;
}


Enum_Acciones Character::get_accion(){
    return _accion;
}

Enum_Tipo_Ataque Character::get_tipo_ataque(){
    return _tipo_ataque;
}

bool Character::esta_bloqueado(){
    if((_tiempo->get_current() - _tiempo_inicio_accion < _duracion_accion_actual) && _bloqueado == true){
        return true;
    }
    else{
        return false;
    }
}

bool Character::accion_en_curso(){
    if((_tiempo->get_current() - _tiempo_inicio_accion < _duracion_accion_actual)){
        return true;
    }
    else{
        return false;
    }
}

///////////////////////////////////////////////////////// INICIO GESTION ACCIONES /////////////////////////////////////////////////////////

void Character::set_tipo_ataque(Enum_Tipo_Ataque _i_tipo_ataque){
    _tipo_ataque = _i_tipo_ataque;
}

void Character::impulso_danyar(Character * atacante, Character * atacado, int impulso){

    float x = atacado->getX() - atacante->getX();
    float z = atacado->getZ() - atacante->getZ();

    Vector2 direccion_impulso(x,z);
    direccion_impulso.Normalize();

    float valor = lib_math_distancia_2_puntos(atacado->getX(), atacado->getZ(), atacante->getX(), atacante->getZ());

    Vector3 a(direccion_impulso._x*(impulso/valor),0,direccion_impulso._y*(impulso/valor));
    atacado->get_objeto_motor()->Impulso_explosion(a);

}

int Character::getTiempoAccion(Enum_Acciones _accion){

    if(_accion == Accion_pre_atacar){

        if(_tipo_ataque == Ataque_Normal){
            return 600;
        }
        else if(_tipo_ataque == Ataque_Fuerte){
            return 400;
        }
        else if(_tipo_ataque == Ataque_Normal_Normal){
            return 100;
        }
        else if(_tipo_ataque == Ataque_Normal_Fuerte){
            return 200;
        }
        else if(_tipo_ataque == Ataque_Fuerte_Normal){
            return 200;
        }
        else if(_tipo_ataque == Ataque_Fuerte_Fuerte){
            return 200;
        }
        else{
            std::cout<< "No debe entrar 2 \n";
            return 200;
        }
            
    }
    
    else if(_accion == Atacar){
        return 1;
    }

    else if(_accion == Accion_post_atacar){

        if(_tipo_ataque == Ataque_Normal){
            return 400;
        }
        else if(_tipo_ataque == Ataque_Fuerte){
            return 400;
        }
        else if(_tipo_ataque == Ataque_Normal_Normal){
            return 400;
        }
        else if(_tipo_ataque == Ataque_Normal_Fuerte){
            return 200;
        }
        else if(_tipo_ataque == Ataque_Fuerte_Normal){
            return 200;
        }
        else if(_tipo_ataque == Ataque_Fuerte_Fuerte){
            return 200;
        }
        else{
            std::cout<< "No debe entrar \n";
            return 200;
        }
    }
    else if(_accion == Accion_Dash){
        return 300;
    }
    else if(_accion == Accion_Interactuar){
        return 25;
    }
    else if(_accion == Saltar){
        return 600;
    }
    else if(_accion == Accion_pre_Coger_Llave){
        return 700;
    }
    else if(_accion == Accion_post_Coger_Llave){
        return 600;
    }
    else if(_accion == Accion_pre_Usar_Llave){
        return 800;
    }
    else if(_accion == Accion_post_Usar_Llave){
        return 400;
    }
    else{
        return 500;
    }
}

static bool getSiAccionBloqueaInput(Enum_Acciones _accion){
    switch(_accion)
    {
        case Accion_pre_atacar:
            return true;
        case Atacar:
            return true;
        case Accion_post_atacar:
            return true;
        case Accion_Dash:
            return true;
        case Accion_Interactuar:
            return true;
        case Saltar:
            return false;
        case Recibir_danyo:
            return true;
        case Accion_pre_Coger_Llave:
            return true;
        case Accion_post_Coger_Llave:
            return true;
        case Accion_pre_Usar_Llave:
            return true;
        case Accion_post_Usar_Llave:
            return true;
        default:
            return false;
    }
}

Enum_Tipo_Ataque Character::get_tipo_ataque_combo(Enum_Tipo_Ataque new_tipo_ataque){
    switch(_tipo_ataque) // ataque actual
    {
        case Ataque_Normal:
            if(new_tipo_ataque == Ataque_Normal)
                return Ataque_Normal_Normal;
            else if(new_tipo_ataque == Ataque_Fuerte)
                return Ataque_Normal_Fuerte;
            else
                std::cout<< "No debe entrar 4.0 \n";
            
        case Ataque_Fuerte:
            if(new_tipo_ataque == Ataque_Normal)
                return Ataque_Fuerte_Normal;
            else if(new_tipo_ataque == Ataque_Fuerte)
                return Ataque_Fuerte_Fuerte;
            else
                std::cout<< "No debe entrar 4.1 \n";
        default:
            std::cout<< "No debe entrar 4.2 \n";
            return Ataque_Fuerte_Fuerte;
    }
}

uint8_t Character::get_danyo_ataque(Enum_Tipo_Ataque tipo_ataque){
    switch(tipo_ataque) // ataque actual
    {
        case Ataque_Normal:
            return _danyo_ataque_normal;
        case Ataque_Fuerte:
            return _danyo_ataque_fuerte;
        default:
            return _danyo_ataque_normal;
    }
}

int Character::get_impulso_danyar(Enum_Tipo_Ataque tipo_ataque){
    switch(tipo_ataque) // ataque actual
    {
        case Ataque_Normal:
            return 15000;
        case Ataque_Fuerte:
            return 30000;
        default:
            return 25000;
    }
}

btVector3 Character::getPosicionRbAtaque(Enum_Tipo_Ataque _ataque){

    float x_atacante = this->getX();
    float y_atacante = this->getY();
    float z_atacante = this->getZ();
    float _cos, _sen;
    _cos = cos(_direccion_actual*std::acos(-1)/180);
    _sen = sin(_direccion_actual*std::acos(-1)/180);
  
    switch(_ataque)
    {
        case Ataque_Ninguno:
            return btVector3(x_atacante + _sen * 9, y_atacante, z_atacante + _cos * 9);

        default:
            return btVector3(x_atacante + _sen * 3, y_atacante, z_atacante + _cos * 3);
    }
}

btVector3 Character::getEscalaRbAtaque(Enum_Tipo_Ataque _ataque){
    // ancho, alto, largo

    if(_tipo_ataque == Ataque_Normal){
        //std::cout<< "cuerpo a cuerpo normal" <<std::endl;
        return btVector3(4,1,4);
    }
    else if(_tipo_ataque == Ataque_Fuerte){
        //std::cout<< "cuerpo a cuerpo  fuerte" <<std::endl;
        return btVector3(4,1,4.5);
    }
    else if(_tipo_ataque == Ataque_Salto){
        //std::cout<< "cuerpo a cuerpo salto" <<std::endl;
        return btVector3(2,1,2);
    }
    else if(_tipo_ataque == Ataque_Especial){
        //std::cout<< "cuerpo a cuerpo Especial" <<std::endl;
        return btVector3(2,1,2);
    }
    else
        return btVector3(2,1,2);
}

void Character::set_accion(Enum_Acciones _i_accion){
    _accion = _i_accion;

    _tiempo_inicio_accion = _tiempo->get_current();
    _duracion_accion_actual = getTiempoAccion(_i_accion);

    _bloqueado = getSiAccionBloqueaInput(_i_accion);
    
    if(_bloqueado == false){ // No se bloquean inputs
        _objeto_motor->colorear_nodo(255,255,255);
    }
  
    if(_i_accion != Accion_pre_atacar && _i_accion != Accion_post_atacar && _i_accion != Atacar){
        set_tipo_ataque(Ataque_Ninguno);
    }
}

void Character::gestion_acciones(){
    gestion_ataque();
    gestion_dash();
    gestion_interactuar();
    gestion_saltar();
    gestion_recibir_danyado();
    gestion_coger_llave();
    gestion_usar_llave();
    //gestion_mover();
}

void Character::gestion_recibir_danyado(){
    if(get_accion() == Recibir_danyo && !_inmortal){
        //std::cout << "SIENDO DANYADO" << std::endl;
        _objeto_motor->colorear_nodo(255,0,0);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
            //_objeto_motor->colorear_nodo(255,255,255);
        }
    }
}

void Character::gestion_dash(){
    if(get_accion() == Accion_Dash){
        //std::cout << "ESQUIVANDO" << std::endl;
        _objeto_motor->Dash(_direccion_actual);
        //_objeto_objeto_motor->colorear_nodo(0,255,0);
        //_objeto_motor->colorear_nodo(0,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Accion_Correr);
            //_objeto_motor->colorear_nodo(255,255,255);
        }
    }
}

void Character::gestion_saltar(){
    if(get_accion() == Saltar){
        std::cout << "SALTANDO" << std::endl;

        if(accion_en_curso() == false){
            std::cout << "FIN SALTO" << std::endl;
            this->set_accion(Accion_Correr);
        }
    }
}

void Character::gestion_interactuar(){
    if(get_accion() == Accion_Interactuar){
        std::cout << "Interactuando..." << std::endl;

        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

void Character::gestion_coger_llave(){
    if(get_accion() == Accion_pre_Coger_Llave){

        if(esta_bloqueado() == false){
            set_accion(Accion_post_Coger_Llave);

            get_inventario()->anadir_llave(_llave_aux_animacion);
            _llave_aux_animacion->set_visible(false);
            _sonido->Play_escenario(1);
            Game::game_instancia()->set_llave_hud(true);
            _llave_aux_animacion->eliminar_del_minimapa();
        }
    }
    else if(get_accion() == Accion_post_Coger_Llave){

        if(esta_bloqueado() == false){
            set_accion(Nada);
        }
    }
}

void Character::gestion_usar_llave(){
    if(get_accion() == Accion_pre_Usar_Llave){

        if(esta_bloqueado() == false){
            set_accion(Accion_post_Usar_Llave);

            get_inventario()->eliminar_llave(_llave_aux_animacion);
            _puerta_aux_animacion->set_abierta();
            Game::game_instancia()->set_llave_hud(false);
            _puerta_aux_animacion->eliminar_del_minimapa(); 
        }
    }
    else if(get_accion() == Accion_post_Usar_Llave){

        if(esta_bloqueado() == false){
            set_accion(Nada);
        }
    }
}

void Character::set_zona_en_la_que_se_encuentra(Zona* _zona){
   _zona_en_la_que_se_encuentra = _zona;
}


void Character::gestion_ataque(){ // CONTROLAR GESTION DE ENEMIGO, que esta OVERRIDE

    if(this->get_accion() == Accion_pre_atacar){
        //std::cout << "PRE-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Atacar);
            Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb_ataque, getPosicionRbAtaque(_tipo_ataque), getEscalaRbAtaque(_tipo_ataque), _direccion_actual);
        }
    }
    else if(this->get_accion() == Atacar){

        play_voces_ataque();

        Datos_Partida * _datos_partida = Game::game_instancia()->game_get_datos();
        Character ** _characters = _datos_partida->get_characters();
        uint16_t _cont, _num_characters;
        _num_characters = _datos_partida->get_num_characters();

        bool golpea = false;

        for(_cont = 0; _cont < _num_characters; _cont++) {
            if( _characters[_cont]->get_vida_actual()>0 && _characters[_cont]->get_equipo() != _equipo &&
                Motor::Motor_GetInstance()->comprobar_colision(_rb_ataque, _characters[_cont]->get_objeto_motor()->getRigidBody()) == true)
            {

                _characters[_cont]->danyar(get_danyo_ataque(this->get_tipo_ataque()));
                Motor::Motor_GetInstance()->_interfaz->Crear_particulas( _characters[_cont]->getX(),9,  _characters[_cont]->getZ(), get_direccion_actual()); 
                //std::cout << "----- " << _characters[_cont]->get_vida() << "------" << std::endl;

                // Impulsa al atacado
                impulso_danyar(this, _characters[_cont], get_impulso_danyar(_tipo_ataque));

                golpea = true;
            }
        }

        if(golpea == true){
           
        }
        _objeto_motor->Impulso(_direccion_actual, 3000);
    

        //std::cout << "ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(0,0,255);
        if(esta_bloqueado() == false){
            this->set_accion(Accion_post_atacar);
        }
    }
    else if(this->get_accion() == Accion_post_atacar){
        //std::cout << "POST-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,20,147);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}

///////////////////////////////////////////////////////// FIN GESTION ACCIONES /////////////////////////////////////////////////////////

void Character::aumentar_danyo_ataque_fuerte(uint8_t _i_valor){
    _danyo_ataque_fuerte+=_i_valor;
}

void Character::aumentar_danyo_ataque_normal(uint8_t _i_valor){
    _danyo_ataque_normal+=_i_valor;
}

void Character::disminuir_danyo_ataque_fuerte(uint8_t _i_valor){
    _danyo_ataque_fuerte-=_i_valor;
}
void Character::disminuir_danyo_ataque_normal(uint8_t _i_valor){
    _danyo_ataque_normal-=_i_valor;
}

uint16_t Character::get_direccion_actual(){
    return _direccion_actual;
}

void Character::set_direccion_actual(uint16_t nueva_direccion){
    _direccion_actual = nueva_direccion;
}


void Character::rotar_cuerpo(uint16_t _i_valor){
    _objeto_motor->rotar_nodo(_i_valor);
}

void Character::rotar_cuerpo_sin_interpolacion(uint16_t _i_valor){
    _objeto_motor->rotar_nodo_sin_interpolacion(_i_valor);
}


Zona* Character::get_zona() {
    return _zona_en_la_que_se_encuentra;
}

void Character::animacion_andar() {
}

void Character::animacion_correr() {
}

void Character::recoge_llave(Llave* _llave) {
    set_accion(Accion_pre_Coger_Llave);
    auto _pos_llave = _llave->get_posicion();
    float _distancia = 3.5;
    uint16_t _angulo = lib_math_angulo_2_puntos(_objeto_motor->getZ(), _objeto_motor->getX(), std::get<1>(_pos_llave), std::get<0>(_pos_llave));
    float _new_x = std::get<0>(_pos_llave) - sin(_angulo * PIs / 180) * _distancia;
    float _new_z = std::get<1>(_pos_llave) - cos(_angulo * PIs / 180) * _distancia;
    _objeto_motor->setPositionXZ(_new_x, _new_z);
    _objeto_motor->rotar_nodo(_angulo);
    _objeto_motor->cambiar_modelado("Anim_coger_objeto_jugador", 19);

    _llave_aux_animacion = _llave;

    //std::cout << "Llave recogida"<< std::endl;
    //std::cout << "Llaves: "<< get_inventario()->get_llaves().size() << std::endl;
}

void Character::abrir_puerta(Puerta* _puerta, Llave* _llave) {
    set_accion(Accion_pre_Usar_Llave);

    auto _pos_cerrojo = _puerta->get_posicion_cerrojo();
    _objeto_motor->setPositionXZ(std::get<0>(_pos_cerrojo), std::get<1>(_pos_cerrojo));
    _objeto_motor->rotar_nodo(_puerta->get_rotacion_cerrojo());
    _objeto_motor->cambiar_modelado("Anim_abrir_puerta_ok_jugador", 18);

    _puerta_aux_animacion = _puerta;
    _llave_aux_animacion = _llave;

    //std::cout << "Puerta abierta"<< std::endl;
    //std::cout << "Llaves: "<< get_inventario()->get_llaves().size() << std::endl;
}