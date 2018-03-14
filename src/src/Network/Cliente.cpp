#include "Cliente.h"
#include "Mensajes_Conexion.h"
#include "../Personajes/Player.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../../Raknet/RakPeer.h"
#include "../../Raknet/GetTime.h"

Cliente * Cliente::instancia = 0;

Cliente* Cliente::getInstance(){
	if(instancia==0)
		instancia= new Cliente();

	return instancia;
}

Cliente::Cliente() {
	peer = RakNet::RakPeerInterface::GetInstance();
	packet = new RakNet::Packet;
	startgame=false;
	_puede_actualizar = true;
	peer->SetOccasionalPing(true);
}

Cliente::~Cliente() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
	peer = NULL;
}

void Cliente::start_client(char* iptoconnect,unsigned short  port){
	RakNet::SocketDescriptor sd;
	peer->Startup(1, &sd, 1);
	peer->Connect(iptoconnect, port, 0, 0);
	std::cout<< "Conectando a " << iptoconnect << " - Puerto - " << port << std::endl;
}

void Cliente::check_and_send_mesages(){

	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
		switch (packet->data[0]) {
			case  ID_START_GAME:{
				recive_game_start();
				break;
			}
			case ID_PLAYER_JOIN: {
				recive_join_message();
				break;
			}
			case ID_EXISTING_PLAYER: {
				recive_existing_message();
				break;
			}
			case ID_PLAYER_MOVE: {
				recive_move_message();
				break;
			}
			case ID_ENEMY_MOVE: {
				recive_move_message_enemy();
				break;
			}
			case ID_PLAYER_DISCONNECT: {
				recive_player_desconnect();
				break;
			}
			case ID_POSICIONAR:{
				posicionar_player();
				break;
			}
			case ID_CONNECTION_LOST: {
				//window.close();
				break;
			}
			default:
				break;
		}
	}
}

void Cliente::Cerrar_peer(){
	peer->Shutdown(300);
}

// SEND MESSAGES

void Cliente::send_player_move(std::vector<Enum_Inputs> vector_keypresed, short number_of_inputs){
	RakNet::BitStream bitstream;
	Enum_Inputs key_press;

	//std::cout << number_of_inputs << "Envio mensaje de tipo ya he actualizado" << std::endl;
	bitstream.Write((RakNet::MessageID)ID_PLAYER_MOVE);
	bitstream.Write(number_of_inputs);
		for(short a = 0; a < number_of_inputs; a++){
			key_press = vector_keypresed[a];
			bitstream.Write(key_press);
		}
//	_puede_actualizar = false;
	peer->Send(&bitstream, LOW_PRIORITY, UNRELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}

void Cliente::send_game_start(){
	startgame=true;
	RakNet::BitStream bitstream;
	bitstream.Write((RakNet::MessageID)ID_START_GAME);
	peer->Send(&bitstream, LOW_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}

void Cliente::send_desplazamiento(short id, float x, float y){
	RakNet::BitStream bitstream;
	bitstream.Write((RakNet::MessageID)ID_ENEMY_MOVE);
	bitstream.Write(id);
	bitstream.Write(x);
	bitstream.Write(y);

	RakNet::Time time = RakNet::GetTime();
	bitstream.Write(time);

	std::cout << (double)time << "TIEMPO DEL CLIENTE \n";

	peer->Send(&bitstream, LOW_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
	_puede_actualizar = false;
}



// RECIVE MESSAGES

void Cliente::recive_game_start(){
	startgame=true;
}

void Cliente::recive_join_message(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;
	float x,y;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(x);
	bitstream.Read(y);
	std::cout << "han creado a mi hermano ------------------------------ \n";
	players[id] = Game::game_instancia()->game_get_datos()->crear_jugador(x,y);   //-> //anyadir_jugador(); ESTO ES LO QUE PONIA
	_puede_actualizar =true;
	//players[id] =  Game::game_instancia()->game_get_datos()->get_player();
}


void Cliente::asociar_player(Player* _player_asociado){
	//RakNet::RakNetGUID = 
	//std::cout << "zorra"<< << std::endl;
	players[peer->GetMyGUID()] = _player_asociado;
	//RakPeer::GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
}


void Cliente::recive_existing_message(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;
	float x,y;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(x);
	bitstream.Read(y);

	std::cout << id.ToString() << "VALOR DE CUANDO SE CREA \n" ;
	players[id] = Game::game_instancia()->game_get_datos()->crear_jugador(x,y);
	   //-> //anyadir_jugador();  ESTOO ES LO QUE PONIA
	//_puede_actualizar = true;
}

void Cliente::recive_move_message(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;
	//std::vector <Enum_Inputs> keys;
	float number_of_inputs;
	Enum_Inputs key_press;
//	_puede_actualizar = true;


	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(number_of_inputs);

	// std::cout << number_of_inputs << "<- Recibo mensaje del otro jugador \n";
	if(Game::game_instancia()->game_get_datos()->dame_jugadores_online().size()>0)

	for(; number_of_inputs; number_of_inputs--){
		bitstream.Read(key_press);
		//keys.push_back(key_press);<
	//	    std::cout << key_press << "el valor que recibo como mensaje es este \n";

		Game::game_instancia()->game_get_datos()->dame_jugadores_online()[0]->comprobar_input(key_press); //->actualizar_by_id(1, key_press); ESTO ES LO QUE PONIA
	}
}

void Cliente::recive_move_message_enemy(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	float x, y;
	RakNet::RakNetGUID id;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(x);
	bitstream.Read(y);
	
//0	if(Game::game_instancia()->game_get_datos()->dame_jugadores_online().size()>0)
//	Game::game_instancia()->game_get_datos()->dame_jugadores_online()[0]->mover(x, y); //->actualizar_posicion_enemigo(x,y,id); ESTO ES LO QUE PONIA
	std::cout << id.ToString() << "voy a intentar actualizar este valor" << std::endl;
	players[id]->mover(x, y - peer->GetLastPing(packet->guid));
	if(Game::game_instancia()->game_get_datos()->get_player() == players[id])
		_puede_actualizar = true;
	std::cout << id.ToString() << "ACTUALIZADO" << std::endl;


}

void Cliente::posicionar_player(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	float x, y;
	RakNet::RakNetGUID id;
	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(x);
	bitstream.Read(y);
	//if(Game::game_instancia()->game_get_datos()->dame_jugadores_online().size()>0)
	//Game::game_instancia()->game_get_datos()->dame_jugadores_online()[0]->mover(x, y); //->actualizar_posicion_enemigo(x,y,id); ESTO ES LO QUE PONIA
	_puede_actualizar = true;
	std::cout << "llego aqui al menos"<< id.ToString()<< std::endl;
	players[id]->setPositionXZ(x,y);
}


void Cliente::recive_player_desconnect(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);

	//players.erase(id);
	std::cout << "A player has disconnected. \n";
	_puede_actualizar = true;

}

// GETTERS

bool Cliente::get_start(){
	return startgame;
}
