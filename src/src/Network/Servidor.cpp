#include "Servidor.h"
#include "Mensajes_Conexion.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Personajes/Player.h"
#include "../Tiempo/Time.h"
#include "../../Raknet/GetTime.h"


Servidor * Servidor::instancia = 0;

Servidor* Servidor::getInstance(){
	if(instancia==0)
		instancia= new Servidor();

	return instancia;
}

Servidor::Servidor() {
	peer = RakNet::RakPeerInterface::GetInstance();
	peer->SetOccasionalPing(true);
	packet = new RakNet::Packet;
	numplayers = 0;
	_siguiente_actualizacion = 30000;
	_reloj = Time::Instance();
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


void Servidor::Posicionar_jugadores(){
	int a =0;
	for (auto &row : players) { //Update new player with all pre-existing characters and positions
		RakNet::BitStream bitstream;
		bitstream.Write((RakNet::MessageID)ID_POSICIONAR);
		bitstream.Write(row.first);
		bitstream.Write(row.second->getX());
		bitstream.Write(row.second->getZ());
		peer->Send(&bitstream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
		//std::cout <<++a <<row.first.ToString()<< " "<< row.second->getX()<< " " << row.second->getZ()<< "ESTO ESTA ENVIANDO A \n";
	}
}

void Servidor::check_and_send_mesages(){

	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		switch (packet->data[0]) {
//START CONNECTION
			case ID_NEW_INCOMING_CONNECTION: {
				float x = rand() % 50 + 25;
				float z = rand() % 50 + 25;
				players[packet->guid] = Game::game_instancia()->game_get_datos()->crear_jugador(x,z);
				identifyplayers[packet->guid] = numplayers;
				numplayers++;
				RakNet::BitStream stream; //Send the new player's GUID to other clients due to client~server model
				stream.Write((RakNet::MessageID)ID_PLAYER_JOIN);
				stream.Write(packet->guid);
				stream.Write(x);
				stream.Write(z);				
				peer->Send(&stream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, true);

				for (auto &row : players) { //Update new player with all pre-existing characters and positions
					if (row.first == packet->guid) continue; //Check if guid is the new player's
					RakNet::BitStream update_plr;
					update_plr.Write((RakNet::MessageID)ID_EXISTING_PLAYER);
					update_plr.Write(row.first);
					update_plr.Write(row.second->getX());
					update_plr.Write(row.second->getZ());
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
				Enum_Inputs key_press;
				std::vector<Enum_Inputs> keys;
				short number_of_inputs;
				RakNet::BitStream stream(packet->data, packet->length, false);
				stream.IgnoreBytes(sizeof(RakNet::MessageID));


				for(stream.Read(number_of_inputs); number_of_inputs; number_of_inputs--){
					stream.Read(key_press);
					keys.push_back(key_press);
					Game::game_instancia(); //->actualizar_by_id(identifyplayers[packet->guid], key_press); ESTO ES LO QUE PONIA
				}

				float numberallkeys = keys.size();
				RakNet::BitStream posUpdate;
				posUpdate.Write((RakNet::MessageID)ID_PLAYER_MOVE); //Client getting "ID_PLAYER_MOVE", know's it's a different player
				posUpdate.Write(packet->guid);
				posUpdate.Write(numberallkeys);
				for(unsigned short a=0; a<keys.size(); a++){
					posUpdate.Write(keys[a]);
				}

				peer->Send(&posUpdate, LOW_PRIORITY, RELIABLE_ORDERED , 0, packet->guid, true); //Send to all clients except the one that moved

				break;
			}

			case ID_ENEMY_MOVE: {
				Position position;
				short id;
				RakNet::Time tiempo_recibido;

				RakNet::BitStream stream(packet->data, packet->length, false);
				stream.IgnoreBytes(sizeof(RakNet::MessageID));
				stream.Read(id);
				stream.Read(position.x);
				stream.Read(position.y);
				stream.Read(tiempo_recibido);

				Game::game_instancia()->game_get_datos()->dame_jugadores_online()[identifyplayers[packet->guid]]->mover(position.x,_reloj->get_tiempo_desde_ultimo_update()-peer->GetLastPing(packet->guid));
				Game::game_instancia()->game_get_datos()->dame_jugadores_online()[identifyplayers[packet->guid]]->set_direccion_actual(position.x);
			
			
			
				RakNet::Time tiempo = peer->GetClockDifferential(packet->guid);
				RakNet::Time serverTime = RakNet::GetTime() + tiempo;


				std::cout << "TIEMPO DEL SERVIDOR " << (double) serverTime << tiempo_recibido  << std::endl;
				
			//	printf("Time difference is %" PRINTF_64_BIT_MODIFIER "u\n",  tiempo_recibido);

			//	std::cout <<  (int) (time - tiempo_recibido)<< " <- mira aqui" << std::endl;



position.y =_reloj->get_tiempo_desde_ultimo_update()-peer->GetLastPing(packet->guid);

				RakNet::BitStream posUpdate;
				posUpdate.Write((RakNet::MessageID)ID_ENEMY_MOVE); //Client getting "ID_PLAYER_MOVE", know's it's a different player
				posUpdate.Write(packet->guid); //Send Raknet ID of the enemy
				posUpdate.Write(position.x);
				posUpdate.Write(position.y);

				float  mult = 4.9212625;


			//	Game::game_instancia()->game_get_datos()->dame_jugadores_online()[identifyplayers[packet->guid]]->setPositionXZ(mult*6, mult*52);
				//Game::game_instancia()->game_get_datos()->dame_jugadores_online()[identifyplayers[packet->guid]]->setPositionXZ(mult*6, mult*52);
				std::cout << identifyplayers[packet->guid] << "valor \n";
				peer->Send(&posUpdate, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true); //Send to all clients except the one that moved
			
			
			
				std::cout << peer->GetAveragePing(packet->guid)<< "vlor del pings" << _reloj->get_tiempo_desde_ultimo_update()-peer->GetLastPing(packet->guid);
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

		if(_reloj->get_current()>_siguiente_actualizacion){
			Posicionar_jugadores();
			_siguiente_actualizacion = _reloj->get_current()+5000;
		}

}
