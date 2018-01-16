#include "Enemy.h"
#include <iostream>

Enemy::Enemy(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte, Enum_Tipo_Enemigo _i_tipo_npc) 
    : NPC(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte, _i_tipo_npc) {
}

Enemy::~Enemy() {
}