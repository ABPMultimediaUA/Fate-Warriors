#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <iostream>
#include "../../Raknet/RakPeerInterface.h"
#include "../../Raknet/BitStream.h"
#include "../../Raknet/RakNetTypes.h"
#include "../Input.h"
#include "stdlib.h"
#include <map>
#include <vector>
class Player;

class Cliente {
public:

	static Cliente* getInstance();
	void start_client(char* iptoconnect,unsigned short  port);
	void check_and_send_mesages();

	void Cerrar_peer();
	bool get_start();

	//Recibe data
	void recive_game_start();
	void recive_join_message();
	void recive_existing_message();
	void recive_move_message();
	void recive_move_message_enemy();
	void recive_player_desconnect();
	void send_desplazamiento(short id, uint16_t id_mensaje, float x, float y);
	void posicionar_player();

	//Send data
	void send_player_move(std::vector<Enum_Inputs> vector_keypresed, uint16_t id_mensaje, short number_of_inputs);
	void send_game_start();

	std::vector<Player*> all_clients();

	void asociar_player(Player* _player_asociado);

	virtual ~Cliente();
	bool _puede_actualizar;

private:

	static  Cliente* instancia;
	Cliente();
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	std::map<RakNet::RakNetGUID, Player*> players;
	bool startgame;
};

#endif /* CLIENTE_H_ */
