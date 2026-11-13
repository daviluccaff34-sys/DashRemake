#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
#include <vector>

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
    cocos2d::Label* scoreLabel = nullptr;
    cocos2d::Label* gameOverLabel = nullptr;
    std::vector<cocos2d::DrawNode*> obstacles;

    float velocityY = 0.0f;
    float obstacleTimer = 0.0f;
    float obstacleSpeed = 360.0f;
    int score = 0;
    bool onGround = true;
    bool gameOver = false;

    void jump();
    void updateGame(float dt);
    void spawnObstacle();
    void endGame();
    void restart();
};

#endif
