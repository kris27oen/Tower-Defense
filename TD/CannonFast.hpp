#ifndef CannonFast_hpp
#define CannonFast_hpp

#include "Defense.hpp"

class CannonFast : public Defense {
public:
    CannonFast(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

#endif /* CannonFast_hpp */

