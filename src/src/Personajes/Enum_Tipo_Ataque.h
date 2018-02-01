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
	Ataque_Fuerte_Normal
};

enum Tipo_Arma{
	Tipo_Arma_cuerpo_a_cuerpo = 1,
	Tipo_Arma_distancia = 2,
	Tipo_Arma_cerca = 3
};

#endif /* SRC_ENUM_TIPO_ATAQUE_H_ */