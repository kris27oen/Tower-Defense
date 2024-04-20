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
#include "Rage.hpp"
#include "Rage_effect.hpp"
#include "Defense.hpp"


//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
Rage::Rage(float x, float y) :
    Army("play/rage.png", x, y, 20, 5, 82, 15, 4, 0) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Rage::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();
    if (isPreview) return;

    Army* tgt = nullptr;
    timeticks += deltaTime;

    for (auto& it : scene->ArmyGroup->GetObjects()) {
        tgt = dynamic_cast<Army*>(it);
        

        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius + 80, tgt->Position, tgt->CollisionRadius))
        {
            if (tgt->getspeed() != 75) {
                tgt->setrage(75, 0.5);
            }
            if (timeticks >= 4.4) {
                tgt->setrage(tgt->tempspeed, tgt->tempcd);
            }
        }
    }
    if (timeticks >= 4.5) {
        Hit(INFINITY);
    }

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            getPlayScene()->EffectGroup->AddNewObject(new Rage_effect(Position.x + (PlayScene::BlockSize * i), Position.y + (PlayScene::BlockSize * j)));
        }
    }
}

// Since the bomb army cannot shoot, the function doesn't need to do anything.
void Rage::CreateBullet(Engine::Point pt) {}

// TODO 2 (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void Rage::Hit(float damage) {
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
