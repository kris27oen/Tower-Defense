#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Trap_damage.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Defense;

//Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* defenseParent);
Trap_damage::Trap_damage(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent) :
    Bullet("play/Trap.png", 500, INFINITY, position, forwardDirection, rotation, parent) {
}
