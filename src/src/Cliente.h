#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <iostream>
#include "Raknet/RakPeerInterface.h"
#include "Raknet/BitStream.h"
#include "Raknet/RakNetTypes.h"
#include "stdlib.h"
#include <map>
#include <vector>
#include "Hero.h"

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

	//Send data
	void send_player_move(std::vector<Input_key> vector_keypresed, short number_of_inputs);
	void send_enemy_move(float x, float y, short id_enemigo);
	void send_game_start();

	std::vector<Hero*> all_clients();

	virtual ~Cliente();

private:

	static  Cliente* instancia;
	Cliente();
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	std::map<RakNet::RakNetGUID, Hero*> players;
	bool startgame;
};

#endif /* CLIENTE_H_ */
