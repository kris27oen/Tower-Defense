#ifndef TRAP_hpp
#define TRAP_hpp

#include "Defense.hpp"

class Trap : public Defense {
public:
    int flag = 0;
    float timeticks = 0;
    Trap(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
    void Draw() const override;
};

#endif /* WallDefense_hpp */
