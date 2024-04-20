#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Freeze.hpp"
#include "Freeze_effect.hpp"
#include "Defense.hpp"


//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
Freeze::Freeze(float x, float y) :
    Army("play/Freeze.png", x, y, 20, 5, 82, 15, 3, 0) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Freeze::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();
    if (isPreview) return;

    Defense* tgt = nullptr;
    timeticks += deltaTime;
    
    for (auto& it : scene->DefenseGroup->GetObjects()) {
        tgt = dynamic_cast<Defense*>(it);
        Target = tgt;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius + 80, Target->Position, Target->CollisionRadius))
        {
            if (Target->getcd() != 2.5) {
                Target->setcd(2.5);
            }
            if (timeticks >= 1.9) {
                Target->setcd(Target->tempcd);
            }
        }
        if (timeticks >= 2) {
            Hit(INFINITY);
        }
    }

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            getPlayScene()->EffectGroup->AddNewObject(new Freeze_effect(Position.x + (PlayScene::BlockSize * i), Position.y + (PlayScene::BlockSize * j)));
        }
    }
}

// Since the bomb army cannot shoot, the function doesn't need to do anything.
void Freeze::CreateBullet(Engine::Point pt) {}

// TODO 2 (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void Freeze::Hit(float damage) {
    HP -= damage;
    if (HP <= 0) {
        //OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it : lockedDefenses)
            it->Target = nullptr;
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
        //AudioHelper::PlayAudio("explosion.wav");
    }
}
