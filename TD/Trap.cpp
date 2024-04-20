#include <allegro5/base.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <iostream>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Collider.hpp"
#include "Defense.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "Trap.hpp"

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3


//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
Trap::Trap(float x, float y) : Defense("play/Trap.png", x, y, 30, 0, 10, 4, 30) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Trap::Update(float deltaTime) {
    PlayScene* scene = getPlayScene();
    if (!Enabled) return;

    Army* tgt = nullptr;
    timeticks += deltaTime;

    for (auto& it : scene->ArmyGroup->GetObjects()) {
        tgt = dynamic_cast<Army*>(it);
        Target = tgt;
        if (Target->isPreview) {
            return;
        }
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, Target->Position, Target->CollisionRadius))
        {
            if (Target->id == 3) {
                Target = nullptr;
                continue;
            }
            else if (Target->id == 4) {
                Target = nullptr;
                continue;
            }
            else {
                Sprite::Draw();
                if (flag == 0) timeticks = 0;
                Target->Hit(INFINITY);
                flag = 1;
            }
        }
    }
    if (flag == 1 && timeticks >= 0.25) Hit(INFINITY);
}

void Trap::CreateBullet(Engine::Point pt) {}

void Trap::Hit(float damage) {
    HP -= damage;
    if (HP <= 0) {
        OnExplode();
        // Remove all armies' reference to target
        for (auto& it : lockedArmies)
            it->Target = nullptr;
        int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
        int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
        getPlayScene()->ClearMapState(x, y);
        getPlayScene()->TrapGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}

void Trap::Draw() const {
    if(flag == 1) Sprite::Draw();
    if (PlayScene::DebugMode) {
        // Draw collision radius.
        Sprite::Draw();
        al_draw_circle(Position.x, Position.y, shootRadius, al_map_rgb(255, 0, 0), 2);
    }
}