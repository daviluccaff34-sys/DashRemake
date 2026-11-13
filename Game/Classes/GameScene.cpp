#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
        return false;

    auto size = Director::getInstance()->getVisibleSize();

    addChild(LayerColor::create(Color4B(12, 15, 35, 255)));

    ground = DrawNode::create();
    ground->drawSolidRect(
        Vec2(0, 0),
        Vec2(size.width, 65),
        Color4F(0.05f, 0.8f, 1.0f, 1.0f)
    );
    addChild(ground);

    cube = DrawNode::create();
    cube->drawSolidRect(
        Vec2(-20, -20),
        Vec2(20, 20),
        Color4F(0.1f, 1.0f, 0.8f, 1.0f)
    );
    cube->setPosition(100, 85);
    addChild(cube, 5);

    scoreLabel = Label::createWithSystemFont("0", "Arial", 30);
    scoreLabel->setPosition(size.width - 45, size.height - 40);
    addChild(scoreLabel, 10);

    auto instruction = Label::createWithSystemFont(
        "TOQUE PARA PULAR", "Arial", 18
    );
    instruction->setPosition(size.width / 2, size.height - 45);
    addChild(instruction);

    spawnObstacle();

    auto touch = EventListenerTouchOneByOne::create();
    touch->onTouchBegan = [this](Touch*, Event*)
    {
        if (gameOver)
            restart();
        else
            jump();

        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);

    scheduleUpdate();
    return true;
}

void GameScene::jump()
{
    if (onGround && !gameOver)
    {
        velocityY = 650.0f;
        onGround = false;
    }
}

void GameScene::spawnObstacle()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto obstacle = DrawNode::create();

    Vec2 triangle[] = {
        Vec2(-22, 0),
        Vec2(22, 0),
        Vec2(0, 45)
    };

    obstacle->drawSolidPoly(triangle, 3, Color4F(1.0f, 0.2f, 0.25f, 1.0f));
    obstacle->setPosition(size.width + 35, 65);
    obstacle->setTag(1); // ainda não foi ultrapassado
    addChild(obstacle, 4);
    obstacles.push_back(obstacle);
}

void GameScene::updateGame(float dt)
{
    auto size = Director::getInstance()->getVisibleSize();

    obstacleTimer += dt;
    if (obstacleTimer >= 1.55f)
    {
        obstacleTimer = 0.0f;
        spawnObstacle();
    }

    for (auto it = obstacles.begin(); it != obstacles.end();)
    {
        auto obstacle = *it;
        auto pos = obstacle->getPosition();
        pos.x -= obstacleSpeed * dt;
        obstacle->setPosition(pos);

        if (obstacle->getBoundingBox().intersectsRect(cube->getBoundingBox()))
        {
            endGame();
            return;
        }

        if (obstacle->getTag() == 1 && pos.x < cube->getPositionX())
        {
            obstacle->setTag(0);
            ++score;
            scoreLabel->setString(StringUtils::format("%d", score));
            if (score % 5 == 0)
                obstacleSpeed += 15.0f;
        }

        if (pos.x < -50)
        {
            removeChild(obstacle);
            it = obstacles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameScene::update(float dt)
{
    if (gameOver)
        return;

    velocityY -= 1600.0f * dt;

    auto pos = cube->getPosition();
    pos.y += velocityY * dt;

    if (pos.y <= 85.0f)
    {
        pos.y = 85.0f;
        velocityY = 0.0f;
        onGround = true;
    }

    cube->setPosition(pos);
    updateGame(dt);
}

void GameScene::endGame()
{
    if (gameOver)
        return;

    gameOver = true;

    auto size = Director::getInstance()->getVisibleSize();
    gameOverLabel = Label::createWithSystemFont(
        "FIM DE JOGO\nTOQUE PARA REINICIAR",
        "Arial",
        30
    );
    gameOverLabel->setAlignment(TextHAlignment::CENTER);
    gameOverLabel->setPosition(size.width / 2, size.height / 2);
    addChild(gameOverLabel, 20);
}

void GameScene::restart()
{
    Director::getInstance()->replaceScene(
        TransitionFade::create(0.2f, GameScene::createScene())
    );
}
