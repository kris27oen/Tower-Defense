#ifndef CannonFastBullet_hpp
#define CannonFastBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
    struct Point;
}  // namespace Engine

class Trap_damage : public Bullet {
public:
    explicit Trap_damage(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
};

#endif /* CannonBullet_hpp */
