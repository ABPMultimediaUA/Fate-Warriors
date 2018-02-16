#ifndef INTERACTUABLE_ACTION_H_
#define INTERACTUABLE_ACTION_H_

class Interactuable_Manager;


class Interactuable_Action{
public:
	Interactuable_Action();
	virtual ~Interactuable_Action();
	void update();

private:
	Interactuable_Manager* _interactuable_manager;

};

#endif /* INTERACTUABLE_ACTION_H_ */
