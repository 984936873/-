#ifndef _setting_scene_
#define _setting_scene_
#include"cocos2d.h"
#include"MenuScene.h"
class Setting :public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Setting);
};
#endif 