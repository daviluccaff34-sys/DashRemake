
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

    addChild(LayerColor::create(
        Color4B(12, 15, 35, 255)
    ));

    // Chão
    ground = DrawNode::create();

    ground->drawSolidRect(
        Vec2(0, 0),
        Vec2(size.width, 65),
        Color4F(0.05f, 0.8f, 1.0f, 1.0f)
    );

    addChild(ground);

    // Cubo
    cube = DrawNode::create();

    cube->drawSolidRect(
        Vec2(-20, -20),
        Vec2(20, 20),
        Color4F(0.1f, 1.0f, 0.8f, 1.0f)
    );

    cube->setPosition(100, 85);
    addChild(cube, 5);

    // Obstáculo
    auto obstacle = DrawNode::create();

    Vec2 triangle[] = {
        Vec2(-22, 0),
        Vec2(22, 0),
        Vec2(0, 45)
    };

    obstacle->drawSolidPoly(
        triangle,
        3,
        Color4F::RED
    );

    obstacle->setPosition(size.width - 100, 65);
    addChild(obstacle);

    auto instruction = Label::createWithSystemFont(
        "TOQUE PARA PULAR",
        "Arial",
        18
    );

    instruction->setPosition(
        size.width / 2,
        size.height - 45
    );

    addChild(instruction);

    auto touch = EventListenerTouchOneByOne::create();

    touch->onTouchBegan = [this](Touch*, Event*)
    {
        if (gameOver)
        {
            restart();
            return true;
        }

        jump();
        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(
        touch,
        this
    );

    scheduleUpdate();

    return true;
}

void GameScene::jump()
{
    if (onGround)
    {
        velocityY = 650;
        onGround = false;
    }
}

void GameScene::updateGame(float dt)
{
}

void GameScene::update(float dt)
{
    if (gameOver)
        return;

    auto size = Director::getInstance()->getVisibleSize();

    velocityY -= 1600 * dt;

    Vec2 pos = cube->getPosition();
    pos.y += velocityY * dt;

    if (pos.y <= 85)
    {
        pos.y = 85;
        velocityY = 0;
        onGround = true;
    }

    cube->setPosition(pos);
}

void GameScene::restart()
{
    Director::getInstance()->replaceScene(
        GameScene::createScene()
    );
}
