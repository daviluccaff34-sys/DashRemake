#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    bool init() override;
    void update(float dt) override;

    CREATE_FUNC(GameScene);

private:
    cocos2d::DrawNode* cube = nullptr;
    cocos2d::DrawNode* ground = nullptr;
    float velocityY = 0.0f;
    bool onGround = true;
    bool gameOver = false;

    void jump();
    void updateGame(float dt);
    void restart();
};

#endif
