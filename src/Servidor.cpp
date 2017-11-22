#include "Servidor.h"
#include "Mensajes_Conexion.h"
#include "Game.h"

Servidor * Servidor::instancia = 0;

Servidor* Servidor::getInstance(){
	if(instancia==0)
		instancia= new Servidor();

	return instancia;
}

Servidor::Servidor() {
	peer = RakNet::RakPeerInterface::GetInstance();
	packet = new RakNet::Packet;
	numplayers = 0;
}

void Servidor::start_server(unsigned short port, unsigned short max_clients){

	RakNet::SocketDescriptor sd(port, 0);
	peer->Startup(max_clients, &sd, 1);
	peer->SetMaximumIncomingConnections(max_clients);

}

Servidor::~Servidor() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

void Servidor::send_enemy_move(float x, float y, short id){
	RakNet::BitStream bitstream;
	bitstream.Write((RakNet::MessageID)ID_ENEMY_MOVE);
	bitstream.Write(id);
	bitstream.Write(x);
	bitstream.Write(y);
	peer->Send(&bitstream, LOW_PRIORITY, UNRELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}


void Servidor::check_and_send_mesages(){

	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		switch (packet->data[0]) {
//START CONNECTION
			case ID_NEW_INCOMING_CONNECTION: {
				players[packet->guid] = {0,0};
				identifyplayers[packet->guid] = numplayers;
				numplayers++;
				RakNet::BitStream stream; //Send the new player's GUID to other clients due to client~server model
				stream.Write((RakNet::MessageID)ID_PLAYER_JOIN);
				stream.Write(packet->guid);
				peer->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, true);

				for (auto &row : players) { //Update new player with all pre-existing characters and positions
					if (row.first == packet->guid) continue; //Check if guid is the new player's
					RakNet::BitStream update_plr;
					update_plr.Write((RakNet::MessageID)ID_EXISTING_PLAYER);
					update_plr.Write(row.first);
					update_plr.Write(row.second.x);
					update_plr.Write(row.second.y);

					peer->Send(&update_plr, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
				}
				break;

			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Player methods
			case ID_START_GAME: {

				RakNet::BitStream stream(packet->data, packet->length, false);
				stream.IgnoreBytes(sizeof(RakNet::MessageID));

				RakNet::BitStream posUpdate;
				posUpdate.Write((RakNet::MessageID)ID_START_GAME); //Client getting "ID_PLAYER_MOVE", know's it's a different player

				peer->Send(&posUpdate, LOW_PRIORITY, UNRELIABLE, 0, packet->guid, true); //Send to all clients except the one that moved

				break;
			}

			case ID_PLAYER_MOVE: {
				Input_key key_press;
				std::vector<Input_key> keys;
				short number_of_inputs;
				RakNet::BitStream stream(packet->data, packet->length, false);
				stream.IgnoreBytes(sizeof(RakNet::MessageID));


				for(stream.Read(number_of_inputs); number_of_inputs; number_of_inputs--){
					stream.Read(key_press);
					keys.push_back(key_press);
					Game::game_instancia()->actualizar_by_id(identifyplayers[packet->guid], key_press);
				}

				float numberallkeys = keys.size();
				RakNet::BitStream posUpdate;
				posUpdate.Write((RakNet::MessageID)ID_PLAYER_MOVE); //Client getting "ID_PLAYER_MOVE", know's it's a different player
				posUpdate.Write(packet->guid);
				posUpdate.Write(numberallkeys);
				for(unsigned short a=0; a<keys.size(); a++){
					posUpdate.Write(keys[a]);
				}

				peer->Send(&posUpdate, LOW_PRIORITY, UNRELIABLE, 0, packet->guid, true); //Send to all clients except the one that moved

				break;
			}

			case ID_ENEMY_MOVE: {
				Position position;
				short id;

				RakNet::BitStream stream(packet->data, packet->length, false);
				stream.IgnoreBytes(sizeof(RakNet::MessageID));
				stream.Read(id);
				stream.Read(position.x);
				stream.Read(position.y);

				RakNet::BitStream posUpdate;
				posUpdate.Write((RakNet::MessageID)ID_ENEMY_MOVE); //Client getting "ID_PLAYER_MOVE", know's it's a different player
				posUpdate.Write(id); //Send Raknet ID of the enemy
				posUpdate.Write(position.x);
				posUpdate.Write(position.y);

				peer->Send(&posUpdate, LOW_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, true); //Send to all clients except the one that moved

				break;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Conection methods
			case ID_CONNECTION_LOST:
			case ID_DISCONNECTION_NOTIFICATION: {

				RakNet::BitStream bitstream;
				bitstream.Write((RakNet::MessageID)ID_PLAYER_DISCONNECT);
				bitstream.Write(packet->guid);

				players.erase(packet->guid);

				peer->Send(&bitstream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
				break;
			}
			default:
				break;
		}
}
