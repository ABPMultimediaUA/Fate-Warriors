#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <iostream>
#include "../../Raknet/RakPeerInterface.h"
#include "../../Raknet/BitStream.h"
#include "../../Raknet/RakNetTypes.h"
#include "stdlib.h"
#include <map>

struct Position{
	float x;
	float y;
};

class Time;
class Player;

class Servidor {
public:

	void send_enemy_move(float x, float y, short id);

	static Servidor* getInstance();
	void start_server(unsigned short port, unsigned short max_clients);
	void check_and_send_mesages();
	void Posicionar_jugadores();
	~Servidor();

private:
	static  Servidor* instancia;
	Servidor();
	Time* _reloj;
	double _siguiente_actualizacion;
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	short numplayers;
	std::map<RakNet::RakNetGUID, short> identifyplayers;
	std::map<RakNet::RakNetGUID, Player*> players;


};

#endif /* SERVIDOR_H_ */
