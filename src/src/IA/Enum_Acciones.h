#ifndef SRC_ENUM_ACCIONES_H_
#define SRC_ENUM_ACCIONES_H_

enum Enum_Acciones{
	Nada, 				// Quedarse quieto
	Decidir,			// Accion terminada y debe decidir
	Andar,				// Moverse
	Accion_Correr,
	Accion_pre_atacar,
	Accion_post_atacar,
	Atacar,				// Usar ataque
	Accion_Dash,
	Accion_Interactuar,
	Coger_Arma,			// Recoge un arma
	Usar_Arma,			// Usa el arma equipado
	Saltar,				// Salta
	Accionar,			// Acciona un interruptor
	Recibir_danyo,		// Recibe danyo
	Estar_derribado,	// Cae al suelo
	Huir, 				// Escapa
	n_acciones,			// Nº de acciones
	Error				// Control para la lectura de fichero
};

#endif /* SRC_ENUM_ACCIONES_H_ */
