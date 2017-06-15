#include"SettingScene.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;
Scene* Setting::createScene()
{
	auto scene = Scene::create();
	auto layer = Setting::create();
	scene->addChild(layer);
	return scene;
}
bool Setting::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto music_text = Text::create("music","Arial",32 );
	music_text->setPosition(Vec2(visibleSize.width*0.25,visibleSize.height*0.7));
	this->addChild(music_text);
	auto music_slider = Slider::create();
	music_slider->loadBarTexture("sliderTrack.png");
	music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	music_slider->loadProgressBarTexture("sliderProgress.png");
	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");
	if (musicPercent == 0.0f) {
		musicPercent = 100.0f;
	}
	music_slider->setPercent(musicPercent);
	music_slider->setPosition(Vec2(visibleSize.width*0.6,visibleSize.height*0.7));
	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type) {
		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
			int percent = music_slider->getPercent();
			CocosDenshion::SimpleAudioEngine:: getInstance()->setBackgroundMusicVolume(float(percent) / 100);
			UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	this->addChild(music_slider);
	auto return_menu = Button::create("bt0.png");
	return_menu->setScale(2);
	return_menu->setTitleText("return");
	return_menu->setTitleFontName("Î¢ÈíÑÅºÚ");
	return_menu->setTitleFontSize(16);
	return_menu->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height*0.3));
	return_menu->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto transition = TransitionFade::create(2.0, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_menu);
	return true;
}