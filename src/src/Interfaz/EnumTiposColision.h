
//#define BIT(x) (1<<(x))

enum tipo_colision {
    COL_NADA = 0, //<Colision con nada
    COL_ESCENARIO = (1<<(0)), //<Colision con escenario
    COL_JUGADOR = (1<<(1)), //<Colision con jugador
    COL_NPC = (1<<(2)), //<Colision con NPC
	COL_RAY = (1<<(3)), //rayo del raytracing
	COL_PUERTA = (1<<(4)), //las puertas 
	COL_ATAQUE = (1<<(5)),
	COL_OTRO = (1<<(6)) //<Colision con Otro (trampas, recogibles)
};

//relaciones de colision 
const int escenario_colisiona_con  = 	COL_NADA | COL_JUGADOR | COL_OTRO | COL_NPC | COL_RAY;
const int jugador_colisiona_con    =    COL_JUGADOR | COL_NPC | COL_ESCENARIO | COL_PUERTA | COL_OTRO;
const int npc_colisiona_con        =    COL_JUGADOR | COL_NPC | COL_ESCENARIO | COL_PUERTA | COL_OTRO;
const int ray_colisiona_con        =	COL_ESCENARIO;
const int puerta_colisiona_con     =	COL_ESCENARIO | COL_JUGADOR | COL_NPC;
const int ataque_colisiona_con     =	COL_NPC | COL_JUGADOR;
const int otros_colisiona_con      =    COL_ESCENARIO | COL_JUGADOR | COL_NPC;