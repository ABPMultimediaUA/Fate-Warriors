#ifndef SRC_ENUM_OBJETIVOS_H_
#define SRC_ENUM_OBJETIVOS_H_

enum Enum_Objetivos{
	Objetivo_Ninguno,			// No hay objetivo
	Objetivo_Jugador,			// El objetivo de la decision actual es el jugador
	Objetivo_Enemigo,			// El objetivo de la decision actual es el enemigo más cercano
	Objetivo_Aliado,			// El objetivo de la decision actual es el aliado más cercano	
	n_objetivos
};

#endif /* SRC_ENUM_OBJETIVOS_H_ */