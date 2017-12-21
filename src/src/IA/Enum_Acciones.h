#ifndef SRC_ENUM_ACCIONES_H_
#define SRC_ENUM_ACCIONES_H_

enum Enum_Acciones{
	Nada, 			// Quedarse quieto
	Decidir,		// Accion terminada y debe decidir
	Andar,			// Moverse
	Atacar,			// Usar ataque
	Coger_objeto,	// Recoge un objeto
	Usar_objeto,	// Usa el objeto equipado
	Saltar,			// Salta
	Protegerse,		// Se cubre
	Accionar,		// Acciona un interruptor
	Dar_orden,		// Da una órden a los otros enemigos de la zona
	Recibir_danyo,	// Recibe danyo
	Estar_derribado,// Cae al suelo
	n_acciones,		// Nº de acciones
	Error			// Control para la lectura de fichero
};

#endif /* SRC_ENUM_ACCIONES_H_ */
