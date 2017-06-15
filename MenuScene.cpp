#include"MenuScene.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"HelloWorldScene.h"
#include"SettingScene.h"

USING_NS_CC;
using namespace ui;
Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}
bool GameMenu::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto start_button = Button::create("bt0.png");
	start_button->setScale(2);
	start_button->setTitleText("start game");
	start_button->setTitleFontName("Î¢ÈíÑÅºÚ");
	start_button->setTitleFontSize(16);
	start_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.7));
	start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0, HelloWorld::createScene()); 
			Director::getInstance()->replaceScene(transition);
	}
	});
	this->addChild(start_button);
	auto set_button = Button::create("bt0.png");
	set_button->setScale(2);
	set_button->setTitleText("setting");
	set_button->setTitleFontName("Î¢ÈíÑÅºÚ");
	set_button->setTitleFontSize(16);
	set_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.5));
	set_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0,Setting::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(set_button);
	auto quitgame = Button::create("bt0.png");
	quitgame->setScale(2);
	quitgame->setTitleText("end");
	quitgame->setTitleFontName("Î¢ÈíÑÅºÚ");
	quitgame->setTitleFontSize(16);
	quitgame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.3));
	quitgame->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
				return;
#endif
				Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
#endif

		}
	});
	this->addChild(quitgame);
	return true;

}