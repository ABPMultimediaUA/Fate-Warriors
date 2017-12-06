#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <iostream>
#include "stdlib.h"
#include <map>

namespace RakNet{
	class RakPeerInterface;
	class Packet;
	class RakNetGUID;
};

struct Position{
	float x;
	float y;
};


class Servidor {
public:

	void send_enemy_move(float x, float y, short id);

	static Servidor* getInstance();
	void start_server(unsigned short port, unsigned short max_clients);
	void check_and_send_mesages();
	~Servidor();

private:
	static  Servidor* instancia;
	Servidor();
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	short numplayers;
	std::map<RakNet::RakNetGUID, short> identifyplayers;
	std::map<RakNet::RakNetGUID, Position> players;
};

#endif /* SERVIDOR_H_ */
