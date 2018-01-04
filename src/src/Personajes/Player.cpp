#include "Player.h"
#include <iostream>
#include "../Entrada/Input.h"
#include "../Entrada/Controles.h"
//#include "../Interfaz/Interfaz.h"
//#include "../Interfaz/Interfaz_Fisica.h"
#include "../Camara/Camara.h"
#include "../Tiempo/Time.h"
#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"

#include "../Nivel/Nivel.h"

#include "../Interfaz_Libs/Lib_Math.h"

#include "../Game.h"
#include "../Action_Manager.h"
//  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z) : Character(_id,_i_x, _i_y, _i_z, 15, 10000,10,15)
                                                                {   
    //_matcher = new Matcher(LLAVE_R, LLAVE_M, _i_x, _i_y,  _i_z,  1,true);                                                                
    //_matcher = new Matcher(PERSONAJE_R, PERSONAJE_M, _i_x, _i_y,  _i_z,  1,true); s

    //_tiempo = Time::Instance();
    //std::cout<<"eso: "<<_interface<<std::endl;
    //crear nodo de personaje del motor
    _otro_tiempo = _tiempo->get_start();
    _tiempo_anterior = _tiempo->get_start();
  // _nodoId = _interface->Interfaz_crearProtaZip("models/Personaje.zip", "Personaje.obj",false,
  //                      _i_x,_i_y,_i_z);
  // _interface_fisica->CargaRigidBodyProta(200,_i_x,_i_y,_i_z);
    std::string str = "models/Personaje.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    _id_motor = _motor->crearObjeto(cstr, _i_x,0,_i_z);
    _motor->poner_camara_a_entidad(_id);
    std::cout<<"X player: "<<_motor->getX(_id_motor);
    std::cout<<"Z player: "<<_motor->getZ(_id_motor)<<std::endl;
}

Player::~Player(){

}

void Player::update(){

    bucle_ataque();

    Controles* controles = Controles::Instance();

    bool _w = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    bool _a = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool _s = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    bool _d = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    
    if(_w){
        if(_a){
            _motor->moverDireccion(_id_motor,315);
        }
        else if(_d){
            _motor->moverDireccion(_id_motor,45);
        }
        else {
            _motor->moverDireccion(_id_motor,0);
        }
    }
    else if(_s){
        if(_a){
            _motor->moverDireccion(_id_motor,225);
        }
        else if(_d){
            _motor->moverDireccion(_id_motor,135);
        }
        else {
            _motor->moverDireccion(_id_motor,180);
        }
    }
    else if(_a){
        _motor->moverDireccion(_id_motor,270);
    }
    else if(_d){
        _motor->moverDireccion(_id_motor,90);
    }

    if(controles->estaPulsada(Input_key::E)){
            std::cout<< "Pulsa E"<< std::endl;

            if(esta_bloqueado() == false){
                this->interactuar_con_objeto();
                this->bloquear_input(1000);
                std::cout<< "SÍ INTERACTUA ----------------------------------"<< std::endl;
            }
            else{
                std::cout<< "No puede INTERACTUAR "<< std::endl;
            }
            
            //std::cout<< "Tiempo actual: "<< this->_tiempo->get_current() << std::endl;
            //std::cout<< "Tiempo almacenado: "<< this->get_tiempo_inicio_bloqueado() << std::endl;
        }


        if(controles->estaPulsada(Input_key::Escape)){
          
            //interface->Interfaz_Apagar();
        }

        if(controles->estaPulsada(Input_key::MouseLeft)){
            this->atacar(Ataque_Normal);
        }

        if(controles->estaPulsada(Input_key::MouseRight)){
            //std::cout<< "MOUSER" <<std::endl;
            //this->atacar(Ataque_Fuerte);
            danyar(0);
        }

    /*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        _motor->moverDireccion(0);
        std::cout << "Entra a W \n";
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        _motor->moverDireccion(180);
        std::cout << "Entra a S \n";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        _motor->moverDireccion(270);
        std::cout << "Entra a A \n";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        _motor->moverDireccion(90);
        std::cout << "Entra a D \n";
    }
    */
  

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        _motor->saltar();
        //exit(0);
	}

    // Deteccion del movimiento con mando
    sf::Joystick::update();
    if(sf::Joystick::isConnected(0)){
        //std::cout << "En X" << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
        //std::cout << "En Y" << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
        float _x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float _y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

        // Minimo de movimiento de Joystick
        if(std::abs(_x) > 20 || std::abs(_y) > 20) {
            unsigned short _direccion = lib_math_angulo_2_puntos(_y, -_x, 0, 0);
            _motor->moverDireccion(_id_motor,_direccion);
        }
    }

    /*

    Controles* controles = Controles::Instance();
    Interfaz* interface = Interfaz::Interfaz_getInstance();
    bool moving = false;
    if(interface!=nullptr){    
        float angulo = interface->Interfaz_GetCamaraAngleRad();
   
        float miX;
        float miY;
        float miZ;

        Vector3  mov = _matcher->getPosition();

        miX = mov._x;
        miY = mov._y;
        miZ = mov._z;
//        float movX,movY,movZ;

        _otro_tiempo = _tiempo->get_current();

        double _time = _tiempo->get_tiempo_desde_ultimo_update_segundos();

        float desp_x, desp_z;

        desp_x = desp_z = 0;


        if(controles->estaPulsada(Input_key::W)){
            miZ += cos(angulo) * _velocidad * _time;
            miX += sin(angulo) * _velocidad * _time;
            desp_z += cos(angulo) * _velocidad * _time;
            desp_x += sin(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(0);
            moving = true;
        }
        
        if(controles->estaPulsada(Input_key::S)){
            miZ -= cos(angulo) * _velocidad * _time;
            miX -= sin(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(180);    
            desp_z -= cos(angulo) * _velocidad * _time;
            desp_x -= sin(angulo) * _velocidad * _time;
            moving = true;
        }

        if(controles->estaPulsada(Input_key::A)){
            miZ += sin(angulo) * _velocidad * _time;
            miX -= cos(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(-90);
            desp_z += sin(angulo) * _velocidad * _time;
            desp_x -= cos(angulo) * _velocidad * _time;
            moving = true;
        }

        if(controles->estaPulsada(Input_key::D)){
            miZ -= sin(angulo) * _velocidad * _time;
            miX += cos(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(90);
            desp_z -= sin(angulo) * _velocidad * _time;
            desp_x += cos(angulo) * _velocidad * _time;
            moving = true;
        }
        
        if(controles->estaPulsada(Input_key::E)){
            Game::game_instancia()->game_get_action_manager()->comprobar_objetos_interactuables_cercanos(this);  
        }

        if(controles->estaPulsada(Input_key::Space)){
            _matcher->Saltar();
            moving = true;
        }

        if(controles->estaPulsada(Input_key::Escape)){
          
            interface->Interfaz_Apagar();
        }

        if(controles->estaPulsada(Input_key::MouseLeft)){
            Game::game_instancia()->game_get_action_manager()->atacar(this);
        }

        if(controles->estaPulsada(Input_key::MouseRight)){
            std::cout<< "MOUSER" <<std::endl;
        }

        
        setX(miX);
        setZ(miZ);

        //interface->Interfaz_moverProta(miX, miZ);
        if(moving){
            _matcher->Mover(desp_x,miY,desp_z);
        }
        else{
            //std::cout<<"-------BBBBBBBBBBBBBBBBBBBBBB-------------------------"<<std::endl;
            _matcher->Mover(0,0,0);
        }

        _tiempo_anterior = _otro_tiempo;

        //set level of detail del nivel
        Nivel* nivel=Nivel::nivel_instancia();
        nivel->nivel_set_lod(nivel->nivel_get_id_vertice(miX,miZ));
        
  }
  */
}
			
void Player::render(){
  
}
