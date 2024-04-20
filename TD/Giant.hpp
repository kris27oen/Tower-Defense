#ifndef Giant_hpp
#define Giant_hpp

#include "Army.hpp"

class Giant : public Army {
public:
    Giant(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

#endif /* BombArmy_hpp */
