#ifndef Rage_hpp
#define Rage_hpp

#include "Army.hpp"

class Rage : public Army {
public:
    float timeticks;
    Rage(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

#endif /* BombArmy_hpp */
