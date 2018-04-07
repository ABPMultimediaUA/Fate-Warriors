#ifndef SRC_ENUM_TIPO_ATAQUE_H_
#define SRC_ENUM_TIPO_ATAQUE_H_

enum Enum_Tipo_Ataque{
	Ataque_Ninguno,		// Ningun ataque
	Ataque_Normal,		// Ataque normal
	Ataque_Fuerte,		// Ataque fuerte
	Ataque_Especial,	// Ataque especial solo para el personaje
	Ataque_Desconocido,	// Eliminar, se gestiona con tipo accion
	Ataque_Normal_Normal,
	Ataque_Normal_Fuerte,
	Ataque_Fuerte_Fuerte,
	Ataque_Fuerte_Normal,
	Ataque_Salto
};

enum Tipo_Arma{
	Tipo_Arma_cuerpo_a_cuerpo = 1,
	Tipo_Arma_distancia = 2,
	Tipo_Arma_cerca = 3
};

enum Enum_Nombre_Arma{
	Nombre_Arma_Katana,		
	Nombre_Arma_Ametralladora,		
	Nombre_Arma_Pistola,
	Nombre_Arma_Nada
};

enum Enum_Equipo{
	Enum_Equipo_A,
	Enum_Equipo_B,
	Enum_Equipo_Ninguno
};


#endif /* SRC_ENUM_TIPO_ATAQUE_H_ */
