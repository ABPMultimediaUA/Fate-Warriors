#ifndef SRC_HEADER_EVENTMANAGER_H_
#define SRC_HEADER_EVENTMANAGER_H_
#include "irrlicht/irrlicht.h"

using namespace irr;

//using namespace irr;

class EventManager : public irr::IEventReceiver
{
public:
    // Implementacion del metodo OnEvent, que se llama cada vez que se detecta cualquier
	// evento de teclado, raton, etc.
    virtual bool OnEvent(const irr::SEvent& event);

    // This is used to check whether a key is being held down
    //esta funcion se llama para comprobar el estado de una tecla
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

    EventManager(); //constructor que inicia toda la matriz de booleanas del teclado a false
    ~EventManager();
private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif /* SRC_HEADER_EVENTMANAGER_H_ */
