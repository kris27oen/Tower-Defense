#ifndef Freeze_hpp
#define Freeze_hpp

#include "Army.hpp"

class Freeze : public Army {
public:
    float timeticks;
    Freeze(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

#endif /* BombArmy_hpp */
