#include "Enemy.h"
#include <iostream>

Enemy::Enemy(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short vida) : Character(_id,_i_x, _i_y, _i_z,  _i_ancho, _i_alto,vida){
}

Enemy::~Enemy(){
}

bool Enemy::usar(){
	return true;
}

void Enemy::update(){

}
			
void Enemy::render(){
}