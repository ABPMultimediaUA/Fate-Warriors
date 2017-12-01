#include "Hero.h"
#include "Input.h"
#include <iostream>

Hero::Hero(){
	player = new sf::RectangleShape({ 40.0f, 40.0f });
	player->setFillColor(sf::Color::Red);
}

Hero::~Hero() {
	delete player;
	player=NULL;
}

std::vector<Input_key> Hero::update(){

	std::vector<Input_key> values_pressed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player->move({ 0.0f, -10.0f });
		values_pressed.push_back(W);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->move({ 0.0f, 10.0f });
		values_pressed.push_back(S);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		player->move({ -10.0f, 0.0f });
		values_pressed.push_back(A);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->move({ 10.0f, 0.0f });
		values_pressed.push_back(D);
	}

	return values_pressed;
}

void Hero::update_extern(Input_key a){

		if (a == Input_key::W) {
			player->move({ 0.0f, -10.0f });
		}
		if (a == Input_key::S){
			player->move({ 0.0f, 10.0f });
		}

		if(a == Input_key::A){
			player->move({ -10.0f, 0.0f });
		}
		if (a == Input_key::D) {
			player->move({ 10.0f, 0.0f });
		}
}

float Hero::position_X(){
	return player->getPosition().x;
}

float Hero::position_Y(){
	return player->getPosition().y;
}

void Hero::setPosition(float x, float y){
	player->setPosition(x,y);
}

sf::RectangleShape* Hero::get_player(){
	return player;
}
