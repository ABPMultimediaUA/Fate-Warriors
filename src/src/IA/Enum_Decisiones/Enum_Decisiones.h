#ifndef SRC_ENUM_DECISIONES_H_
#define SRC_ENUM_DECISIONES_H_

enum Enum_Decisiones{
	Decision_Quieto,				// Se queda quieto
	Decision_Atacar,				// Ataca 							(a objetivo)
	Decision_Mover,					// Decide moverse 					(a objetivo)
	Decision_Ir_Atacar,				// Decide acercarse para atacar 	(a objetivo)
	Decision_Coger_Objeto,			// Decide coger el objeto mas cercano
	Decision_Activar_Interruptor,	// Decide activar el interruptor mas cercano
	Decision_Huir,					// Decide huir a la sala enemiga mas cercana
	Decision_Alertar,				// Decidr ir a la zona enemiga mas acercana para alertar
	n_decisiones
};

#endif /* SRC_ENUM_DECISIONES_H_ */
