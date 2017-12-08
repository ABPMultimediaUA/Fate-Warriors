#include "Game.h"
#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Tiempo/Time.h"
#include <iostream>
#include <btBulletDynamicsCommon.h>

const float t_min_IA=(1000/15);

void pruebasNuevas(){
        btBroadphaseInterface* broadphase = new btDbvtBroadphase();

        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

        btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

        dynamicsWorld->setGravity(btVector3(0, -10, 0));


        btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

        btCollisionShape* fallShape = new btSphereShape(1);


        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
        btRigidBody::btRigidBodyConstructionInfo
                groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
        btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
        dynamicsWorld->addRigidBody(groundRigidBody);


        btDefaultMotionState* fallMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
        btScalar mass = 1;
        btVector3 fallInertia(0, 0, 0);
        fallShape->calculateLocalInertia(mass, fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
        btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
        dynamicsWorld->addRigidBody(fallRigidBody);


        for (int i = 0; i < 300; i++) {
                dynamicsWorld->stepSimulation(1 / 60.f, 10);

                btTransform trans;
                fallRigidBody->getMotionState()->getWorldTransform(trans);

                std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
        }

        dynamicsWorld->removeRigidBody(fallRigidBody);
        delete fallRigidBody->getMotionState();
        delete fallRigidBody;

        dynamicsWorld->removeRigidBody(groundRigidBody);
        delete groundRigidBody->getMotionState();
        delete groundRigidBody;


        delete fallShape;

        delete groundShape;


        delete dynamicsWorld;
        delete solver;
        delete collisionConfiguration;
        delete dispatcher;
        delete broadphase;
}


int main(){

	//pruebasNuevas();

	Game* _juego = Game::game_instancia();

	Time* time=Time::Instance();
	//double _tiempo_desde_ultimo_update=time->get_current();
	double _h_ultimo_update=time->get_current();
	double _interpolacion;

	_juego->crea_partida();

	Time* _time = Time::Instance();

	Interfaz* _interface = Interfaz::Interfaz_getInstance(); //moose ninja || 1280 width || 720 height


	//_time->updateAntes();
	while(_interface->Interfaz_getDevice()->run()){
		//evento para cerrar la ventana


		time->set_tiempo_desde_ultimo_update(time->get_current() - _h_ultimo_update);//actualizacion del reloj
		//std::cout << "Tiempo desde update " << time->get_tiempo_desde_ultimo_update() << std::endl;
		//update
		if(time->get_tiempo_desde_ultimo_update()>t_min_IA){
			_h_ultimo_update=time->get_current();
			_juego->update(time->get_tiempo_desde_ultimo_update());
		}


		//render
		_interpolacion=fmin(1.f,(double)time->get_tiempo_desde_ultimo_update()/t_min_IA);
		_juego->render(_interpolacion);
		//std::cout << "Interpolaicon " << _interpolacion	 << std::endl;
		//_time->cambiar_antes_a_ahora();
	}

	_juego->fin_partida();

	delete _time;

	delete _juego;
	
	return 0;

}
