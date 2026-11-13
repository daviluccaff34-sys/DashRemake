#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    bool init() override;

    CREATE_FUNC(GameScene);

private:
    cocos2d::DrawNode* cube;
    cocos2d::DrawNode* ground;
    float velocityY = 0;
    bool onGround = true;
    bool gameOver = false;

    void jump();
    void updateGame(float dt);
    void restart();
};

#endif
