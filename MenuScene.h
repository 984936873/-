#ifndef _menu_scene_
#define _menu_scene_
#include "cocos2d.h"

class GameMenu : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameMenu);
};
#endif