#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
using namespace geode::prelude;

// Velocidades: cambialas aca si queres otras
constexpr float SLOW = 0.5f;
constexpr float DEFAULT_SPEED = 1.0f;
constexpr float FAST = 1.5f;

static void applySpeed(float s) {
    CCDirector::get()->getScheduler()->setTimeScale(s);
}

class $modify(SpeedPause, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = CCMenu::create();
        menu->setPosition({0.f, 0.f});

        struct Opt { const char* text; float speed; float x; };
        Opt opts[] = {
            {"Slow", SLOW, 110.f},
            {"Default", DEFAULT_SPEED, 175.f},
            {"Fast", FAST, 240.f},
        };

        for (auto& o : opts) {
            auto spr = ButtonSprite::create(o.text);
            spr->setScale(0.5f);
            auto btn = CCMenuItemSpriteExtra::create(
                spr, this, menu_selector(SpeedPause::onSpeed));
            btn->setTag(static_cast<int>(o.speed * 100.f));
            btn->setPosition({o.x, 25.f});
            menu->addChild(btn);
        }
        this->addChild(menu, 100);
    }

    void onSpeed(CCObject* sender) {
        auto node = static_cast<CCNode*>(sender);
        applySpeed(node->getTag() / 100.f);
    }
};

// Al salir del nivel, volver a velocidad normal.
class $modify(PlayLayer) {
    void onQuit() {
        applySpeed(1.f);
        PlayLayer::onQuit();
    }
};
