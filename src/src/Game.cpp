#include "Game.h"
#include "PruebaLOD1/Nivel.h"
#include "Cliente.h"
#include "Servidor.h"
#include <stack>
#include <iostream>

Game* Game::instancia = 0;

Game* Game::game_instancia(){
	if(instancia == 0)
		instancia= new Game();

	return instancia;
}
Game::Game(){
	_datos = nullptr;
	_action_manager = nullptr;
  enemigo1 = NULL;
	yoplayer = new Hero*[2];
	yoplayer[0] = NULL;
	yoplayer[1] = NULL;
}
Game::~Game(){
}
void Game::anyadir_jugador(){
	yoplayer[1] = new Hero();
}

void Game::actualizar_jugador_coop(float x, float y){
	yoplayer[1]->setPosition(x,y);
}

void Game::actualizar_posicion_enemigo(float x, float y, short id){
	enemigo1->setPosition(x,y);
}

void Game::main_loop_servidor(){
	char portstring[30];
	unsigned short port;
	Servidor* servidor = Servidor::getInstance();

	std::cout << "Type port to listen " << std::endl;
	std::cin >> portstring;
	port = (unsigned short) strtoul(portstring, NULL, 0);

	enemigo1 = new Enemy(1);
	yoplayer[0] = new Hero();
	yoplayer[1] = new Hero();


	servidor->start_server(port, 3);

	sf::RenderWindow window(sf::VideoMode(900, 600), "Networking Test");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()){
		servidor->check_and_send_mesages();
		enemigo1->update(); // IA

		window.clear();
		window.display();
	}
	delete(servidor);
}

void Game::main_loop_cliente(){
	Cliente* cliente = Cliente::getInstance();
	char portstring [30];
	unsigned short port;
	char iptoconnect [30];

	std::cout << "Type port to connect " << std::endl;
	std::cin >> portstring;
	port = (unsigned short) strtoul(portstring, NULL, 0);

	std::cout << "Type ip to connect to" << std::endl;
	std::cin >> iptoconnect;

	enemigo1 = new Enemy(1);
	cliente->start_client(iptoconnect, port);
	yoplayer[0] = new Hero();

	sf::RenderWindow window(sf::VideoMode(900, 600), "Networking Test");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()){
		//Bucle prepartida
		while(!cliente->get_start()){
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				cliente->send_game_start();
		}

		//Bucle partida
		sf::Event e;
		while(window.pollEvent(e)){
			if(e.type == sf::Event::Closed){
				cliente->Cerrar_peer();
				window.close();
			}
		}

		if(window.hasFocus()){
			std::vector<Input_key> inputs = yoplayer[0]->update();

			if(inputs.size()>0){
				cliente->send_player_move (inputs, inputs.size());
			}
		}
		cliente->check_and_send_mesages();

		window.clear();

		window.draw(*(enemigo1->get_player()));
		window.draw(*(yoplayer[0]->get_player()));

		if(yoplayer[1]!= NULL)
			window.draw(*(yoplayer[1]->get_player()));

		window.display();
	}
	delete(cliente);
	delete(enemigo1);
}

void Game::game_update(){

}
void Game::actualizar_by_id(short id, Input_key actionkey){
	yoplayer[id]->update_extern(actionkey);
}
void Game::game_crea_partida() {
	_datos = new Datos_Partida();
	_action_manager = new Action_Manager();
//  Nivel* _nivel1=new Nivel("Nivel.txt");
}
void Game::game_fin_partida() {
	delete _datos;
	delete _action_manager;
}
void Game::game_run(){
		
	for(int cont=0; cont<10; cont++) {
		_action_manager->toma_decisiones();
		_action_manager->realiza_acciones();
	}
}
  
Datos_Partida* Game::game_get_datos() {
	return _datos;


}
int Game::prueba_grafo()
{
    Nivel *G = new Nivel("Nivel.txt");
    int opc;
/*
    G->nivel_inserta_vertice(1); //NodoA
    G->nivel_inserta_vertice(2); //PasilloB
    G->nivel_inserta_vertice(3); //NodoC
    G->nivel_inserta_vertice(4); //PasilloD
    G->nivel_inserta_vertice(5); //NodoG
    G->nivel_inserta_vertice(6); //PasilloJ
    G->nivel_inserta_vertice(7); //NodoN
    G->nivel_inserta_vertice(8); //PasilloE
    G->nivel_inserta_vertice(9); //NodoH
    G->nivel_inserta_vertice(10); //PasilloK
    G->nivel_inserta_vertice(11); //NodoO
    G->nivel_inserta_vertice(12); //PasilloL
    G->nivel_inserta_vertice(13); //NodoP
    G->nivel_inserta_vertice(14); //PasilloR
    G->nivel_inserta_vertice(15); //NodoS
    G->nivel_inserta_vertice(16); //PasilloT
    G->nivel_inserta_vertice(17); //NodoU
    G->nivel_inserta_vertice(18); //PasilloF
    G->nivel_inserta_vertice(19); //NodoI
    G->nivel_inserta_vertice(20); //PasilloM
    G->nivel_inserta_vertice(21); //NodoQ
    G->nivel_inserta_vertice(22); //PasilloAux1
    G->nivel_inserta_vertice(23); //PasilloAux2

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(1), G->nivel_get_vertice(2), 1);
    //G->nivel_inserta_arista_bi(G->nivel_get_vertice(2), G->nivel_get_vertice(1), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(2), G->nivel_get_vertice(3), 1);
    //G->nivel_inserta_arista_bi(G->nivel_get_vertice(3), G->nivel_get_vertice(2), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(3), G->nivel_get_vertice(4), 1);
    //G->nivel_inserta_arista_bi(G->nivel_get_vertice(4), G->nivel_get_vertice(3), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(4), G->nivel_get_vertice(5), 1);
   // G->nivel_inserta_arista_bi(G->nivel_get_vertice(5), G->nivel_get_vertice(4), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(5), G->nivel_get_vertice(6), 1);
   // G->nivel_inserta_arista_bi(G->nivel_get_vertice(6), G->nivel_get_vertice(5), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(6), G->nivel_get_vertice(7), 3);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(7), G->nivel_get_vertice(6), 3);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(3), G->nivel_get_vertice(8), 1);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(8), G->nivel_get_vertice(3), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(8), G->nivel_get_vertice(9), 1);
   // G->nivel_inserta_arista_bi(G->nivel_get_vertice(9), G->nivel_get_vertice(8), 1);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(9), G->nivel_get_vertice(10), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(10), G->nivel_get_vertice(9), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(11), G->nivel_get_vertice(10), 10);
 //   G->nivel_inserta_arista_bi(G->nivel_get_vertice(10), G->nivel_get_vertice(11), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(9), G->nivel_get_vertice(12), 10);
 //   G->nivel_inserta_arista_bi(G->nivel_get_vertice(12), G->nivel_get_vertice(9), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(12), G->nivel_get_vertice(13), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(13), G->nivel_get_vertice(12), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(13), G->nivel_get_vertice(14), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(14), G->nivel_get_vertice(13), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(14), G->nivel_get_vertice(15), 10);
   // G->nivel_inserta_arista_bi(G->nivel_get_vertice(15), G->nivel_get_vertice(14), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(15), G->nivel_get_vertice(16), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(16), G->nivel_get_vertice(15), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(16), G->nivel_get_vertice(17), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(17), G->nivel_get_vertice(16), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(3), G->nivel_get_vertice(18), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(18), G->nivel_get_vertice(3), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(18), G->nivel_get_vertice(19), 10);
 //   G->nivel_inserta_arista_bi(G->nivel_get_vertice(19), G->nivel_get_vertice(18), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(19), G->nivel_get_vertice(20), 10);
 //   G->nivel_inserta_arista_bi(G->nivel_get_vertice(20), G->nivel_get_vertice(19), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(20), G->nivel_get_vertice(21), 10);
 //   G->nivel_inserta_arista_bi(G->nivel_get_vertice(21), G->nivel_get_vertice(20), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(5), G->nivel_get_vertice(22), 10);
    G->nivel_inserta_arista_bi(G->nivel_get_vertice(22), G->nivel_get_vertice(11), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(11), G->nivel_get_vertice(22), 10);
  //  G->nivel_inserta_arista_bi(G->nivel_get_vertice(22), G->nivel_get_vertice(5), 10);

    G->nivel_inserta_arista_bi(G->nivel_get_vertice(7), G->nivel_get_vertice(23), 10);
    G->nivel_inserta_arista_bi(G->nivel_get_vertice(23), G->nivel_get_vertice(17), 10);
  // G->nivel_inserta_arista_bi(G->nivel_get_vertice(17), G->nivel_get_vertice(23), 20);
   // G->nivel_inserta_arista_bi(G->nivel_get_vertice(23), G->nivel_get_vertice(7), 20);*/

    do
    {
        //std::cout<<"1. Ingresar Vertice"<<std::endl;
        std::cout<<"2. Ingresar arista"<<std::endl;
        std::cout<<"3. Lista de adyacencia"<<std::endl;
        std::cout<<"4. Tamaño"<<std::endl;
        std::cout<<"5. nivel_camino_corto_l2"<<std::endl;
        std::cout<<"6. conexion entre dos vertices?"<<std::endl;
        std::cout<<"7. Vacio?"<<std::endl;
        std::cout<<"8. Salir"<<std::endl;
        std::cout<<std::endl<<"Elija una opcion: ";
        std::cin>>opc;
        switch(opc)
        {
        /*case 1:
        {
            int nombre;
            std::cout<<"Ingrese la id nombre del vertice: ";
            std::cin.ignore();
            std::cin>>nombre;
            G->nivel_inserta_vertice();
            break;
        }*/
        case 2:
        {
            int origen, destino;
            int peso;
            if(G->nivel_vacio())
            {
                std::cout<<"El nivel esta nivel_vacio"<<std::endl;
            }
            else
            {
                std::cout<<"Ingrese id del nombre del vertice origen: ";
                std::cin.ignore();
                std::cin>>origen;
                std::cout<<"Ingrese id del nombre del vertice destino: ";
                std::cin>>destino;
                std::cout<<"Ingrese el peso: ";
                std::cin>>peso;

                if(G->nivel_get_vertice(origen) == NULL || G->nivel_get_vertice(destino) == NULL)
                {
                    std::cout<<"Uno de los vertices no es valido"<<std::endl;
                }
                else
                {
                    G->nivel_inserta_arista_bi(G->nivel_get_vertice(origen), G->nivel_get_vertice(destino), peso);
                }
            }
            break;
        }
        case 3:
        {
            if(G->nivel_vacio())
            {
                std::cout<<"El nivel esta nivel_vacio"<<std::endl;
            }
            else
            {
                G->nivel_lista_adyacencia();
            }
            break;
        }
        case 4:
        {
            if(G->nivel_vacio())
            {
                std::cout<<"El nivel esta nivel_vacio"<<std::endl;
            }
            else
            {
                std::cout<<"Tamano: "<<G->nivel_tamano()<<std::endl;
            }
            break;
        }
        case 5:
        {
            int origen, destino;
            if(G->nivel_vacio())
            {
                std::cout<<"El nivel esta nivel_vacio"<<std::endl;
            }
            else
            {
                std::cout<<"Ingrese el id nombre del vertice origen: ";
                std::cin.ignore();
                std::cin>>origen;
                std::cout<<"Ingrese id del nombre del vertice destino: ";
                std::cin>>destino;
                if(G->nivel_get_vertice(origen) == NULL || G->nivel_get_vertice(destino) == NULL)
                {
                    std::cout<<"Vertices invalidos"<<std::endl;
                }
                else
                {
                    Vertice *pv;
                    std::stack<Vertice*> algo=G->nivel_camino_corto_l2(G->nivel_get_vertice(origen), G->nivel_get_vertice(destino));
                    while(!algo.empty()){
                        pv=algo.top();
                        std::cout << pv->_id <<" -> ";
                        algo.pop();
                    }
                    std::cout<<std::endl;

                }
            }
            break;
        }
        case 6:
        {
            int origen, destino;
            if(G->nivel_vacio())
            {
                std::cout<<"El nivel esta nivel_vacio"<<std::endl;
            }
            else
            {
                std::cout<<"Ingrese id del nombre del vertice origen: ";
                std::cin.ignore();
                std::cin>>origen;
                std::cout<<"Ingrese id del nombre del vertice destino: ";
                std::cin>>destino;
                if(G->nivel_get_vertice(origen) == NULL || G->nivel_get_vertice(destino) == NULL)
                {
                    std::cout<<"Vertices no validos"<<std::endl;
                }
                else
                {
                    G->nivel_eliminar_arista(G->nivel_get_vertice(origen), G->nivel_get_vertice(destino));
                }
            }
            break;
        }
        case 7:
        {
            if(G->nivel_vacio())
            {
                std::cout<<"El nivel esta nivel_vacio"<<std::endl;
            }
            else
            {
               G->nivel_anular();
            }
            break;
        }   
        case 8:
        {

            break;
        }
        default:
        {
            std::cout<<"Elija una opcion valida"<<std::endl;
        }
        }
    }
    while(opc != 8);
    delete G;
    return 0;
}