#include "Cliente.h"
#include "Mensajes_Conexion.h"
#include "Hero.h"
#include "Game.h"

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
}

Cliente::~Cliente() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
	peer = NULL;
}

void Cliente::start_client(char* iptoconnect,unsigned short  port){
	RakNet::SocketDescriptor sd;
	peer->Startup(1, &sd, 1);
	peer->Connect(iptoconnect, port, 0, 0);
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

void Cliente::send_player_move(std::vector<Input_key> vector_keypresed, short number_of_inputs){
	RakNet::BitStream bitstream;
	Input_key key_press;

	bitstream.Write((RakNet::MessageID)ID_PLAYER_MOVE);
	bitstream.Write(number_of_inputs);
		for(short a = 0; a < number_of_inputs; a++){
			key_press = vector_keypresed[a];
			bitstream.Write(key_press);
		}

	peer->Send(&bitstream, LOW_PRIORITY, UNRELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}

void Cliente::send_game_start(){
	startgame=true;
	RakNet::BitStream bitstream;
	bitstream.Write((RakNet::MessageID)ID_START_GAME);
	peer->Send(&bitstream, LOW_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}

// RECIVE MESSAGES

void Cliente::recive_game_start(){
	startgame=true;
}

void Cliente::recive_join_message(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);

	Game::game_instancia()->anyadir_jugador();
}

void Cliente::recive_existing_message(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;
	float x,y;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(x);
	bitstream.Read(y);

	Game::game_instancia()->anyadir_jugador();
}

void Cliente::recive_move_message(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;
	//std::vector <Input_key> keys;
	float number_of_inputs;
	Input_key key_press;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(number_of_inputs);

	for(; number_of_inputs; number_of_inputs--){
		bitstream.Read(key_press);
		//keys.push_back(key_press);
		Game::game_instancia()->actualizar_by_id(1, key_press);
	}
}

void Cliente::recive_move_message_enemy(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	float x, y;
	short id;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);
	bitstream.Read(x);
	bitstream.Read(y);
	Game::game_instancia()->actualizar_posicion_enemigo(x,y,id);
}

void Cliente::recive_player_desconnect(){
	RakNet::BitStream bitstream(packet->data, packet->length, false);
	RakNet::RakNetGUID id;

	bitstream.IgnoreBytes(sizeof(RakNet::MessageID));
	bitstream.Read(id);

	//players.erase(id);
	std::cout << "A player has disconnected. \n";
}

// GETTERS

bool Cliente::get_start(){
	return startgame;
}
