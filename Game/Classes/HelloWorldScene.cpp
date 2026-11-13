
#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
        return false;

    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    float cx = origin.x + size.width / 2;
    float cy = origin.y + size.height / 2;

    addChild(LayerColor::create(
        Color4B(10, 12, 28, 255)
    ));

    auto title = Label::createWithSystemFont(
        "DASH REMAKE", "Arial", 42
    );

    title->setTextColor(Color4B(0, 230, 255, 255));
    title->setPosition(cx, cy + 115);
    addChild(title);

    auto subtitle = Label::createWithSystemFont(
        "THE NEXT RHYTHM", "Arial", 16
    );

    subtitle->setTextColor(Color4B(180, 190, 220, 255));
    subtitle->setPosition(cx, cy + 80);
    addChild(subtitle);

    const char* names[] = {
        "PLAY",
        "EDITOR",
        "GARAGE",
        "SETTINGS"
    };

    for (int i = 0; i < 4; i++)
    {
        auto label = Label::createWithSystemFont(
            names[i], "Arial", 25
        );

        auto button = MenuItemLabel::create(
            label,
            [this, i](Ref*)
            {
                if (i == 0)
                {
                    Director::getInstance()->replaceScene(
                        TransitionFade::create(
                            0.3f,
                            GameScene::createScene()
                        )
                    );
                    return;
                }

                const char* messages[] = {
                    "",
                    "EDITOR COMING SOON",
                    "GARAGE COMING SOON",
                    "SETTINGS COMING SOON"
                };

                auto message = Label::createWithSystemFont(
                    messages[i], "Arial", 18
                );

                message->setPosition(
                    Director::getInstance()->getVisibleSize() / 2
                );

                this->addChild(message, 10);

                message->runAction(Sequence::create(
                    DelayTime::create(1.5f),
                    RemoveSelf::create(),
                    nullptr
                ));
            }
        );

        button->setPosition(
            cx,
            cy + 20 - i * 55
        );

        auto menu = Menu::create(button, nullptr);
        menu->setPosition(Vec2::ZERO);
        addChild(menu, 2);
    }

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
