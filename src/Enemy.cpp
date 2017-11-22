#include "Enemy.h"
#include <iostream>
#include "Cliente.h"
#include "Servidor.h"

Enemy::Enemy(short _i_enemy){
	malote = new sf::RectangleShape({ 40.0f, 40.0f });
	malote->setFillColor(sf::Color::Red);
	malote->setPosition(25,25);
	derecha = false;
	id_enemy = _i_enemy;
}

Enemy::~Enemy() {
	delete malote;
	malote=NULL;
}

void Enemy::update(){
	Servidor *sevidor  = Servidor::getInstance();

	if(derecha)
		malote->move({ 10.0f, 0.0f });
	else
		malote->move({ -10.0f, 0.0f });

	if(malote->getPosition().x>250.0)
		derecha = false;

	if(malote->getPosition().x<0)
		derecha=true;

	sevidor->send_enemy_move(malote->getPosition().x, malote->getPosition().y, id_enemy);
}

float Enemy::position_X(){
	return malote->getPosition().x;
}

float Enemy::position_Y(){
	return malote->getPosition().y;
}

void Enemy::setPosition(float x, float y){
	malote->setPosition(x,y);
}

sf::RectangleShape* Enemy::get_player(){
	return malote;
}
