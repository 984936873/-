#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include<time.h>
USING_NS_CC;
using namespace ui;

class HelloWorld : public cocos2d::Scene
{
private:
	TMXTiledMap * _tileMap;
	Sprite * _player1;
	Sprite * _player2;
	Sprite  *bomb[1000];
	TMXLayer * _bar;
	TMXLayer * _prop;
	int i = 0, j = 0;
	int player1v=16;
	int player2v=32;
	int player1life = 5;
	int bombnum1 = 1;
	int power1 = 2;
	int player2life = 5;
	int bombnum2 = 1;
	int power2 = 2;
	bool placeboom = false;
	int _scwidth, _scheight;
	clock_t boomtime[1000];
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
    static cocos2d::Scene* createScene();
	bool isplaceboom() {
		return placeboom;
	}
	void setplaceboom(int a) {
		placeboom = a;
	}
	void leftdz();
	void rightdz();
	void updz();
	void downdz();
	int whatisthis(int a, int b);
	void thisprop(int a, int b);
	int  map_x() {
		return _player1->getPositionX() / 64;
	}
	int map_y() {
		return (int(_player1->getPositionY()/64));
	}
	int returnplayer1v() {
		return player1v;
	}
	int returnplayer2v() {
		return player2v;
	}
	int returnj() {
		return j;
	}
	int returni() {
		return i;
	}
	void releasebar(int a, int b);
	void changeplayer1v(int a) {
		player1v =  a;
	}
	void changeplayer2v(int a) {
		player2v =  a;
	}
	void creatbomb() {
		auto playerbomb = Sprite::createWithSpriteFrameName("bomb0.png");
		playerbomb->setPosition((int)((_player1->getPositionX())/64)*64+32, ((int)_player1->getPositionY()/64)*64+32);
		this->addChild(playerbomb);
		bomb[i]=playerbomb;
		boomtime[i] = clock();
		if (i == 999)i = 0;
		else i = i + 1;
		auto playeranimationup = Animation::create();
		for (int i = 0; i < 4; i++) {
			playeranimationup->addSpriteFrameWithFile(StringUtils::format("bomb%d.png", i));
		}
		playeranimationup->setDelayPerUnit(5.0f / 40.0f);
		playeranimationup->setRestoreOriginalFrame(true);
		auto runboom = Animate::create(playeranimationup);
		auto runrunboom = RepeatForever::create(runboom);
		playerbomb->runAction(runrunboom);
	};
	void bombboom() {
		auto playerbomb = bomb[j];
		int bombarea = (playerbomb->getPositionX() - 32) / 64;
		int bargid=0;
		for (; bombarea <= ((playerbomb->getPositionX() - 32) / 64 + power1); bombarea++) {
			if (bombarea <= 12) {
				bargid = whatisthis(bombarea, 12 - (int)(playerbomb->getPositionY() / 64));
				if (bargid == 6)break;
				else if (bargid == 5) {
					releasebar(bombarea, 12 - (int)(playerbomb->getPositionY() / 64));
					break;
				}
			}
		}
			bombarea = (playerbomb->getPositionX() - 32) / 64;
			for (; bombarea >= ((playerbomb->getPositionX() - 32) / 64 - power1); bombarea--) {
				if (bombarea >= 0) {
					bargid = whatisthis(bombarea, 12 - (int)(playerbomb->getPositionY() / 64));
					if (bargid == 6)break;
					else if (bargid == 5) {
						releasebar(bombarea, 12 - (int)(playerbomb->getPositionY() / 64));
						break;
					}
				}
			}
			bombarea = (playerbomb->getPositionY() - 32) / 64;
			for (; bombarea >= ((playerbomb->getPositionY() - 32) / 64 - power1); bombarea--) {
				if (bombarea >= 0) {
					bargid = whatisthis(playerbomb->getPositionX()/64, 12 - bombarea);
					if (bargid == 6)break;
					else if (bargid == 5) {
						releasebar(playerbomb->getPositionX()/64, 12 - bombarea);
						break;
					}
				}
			}
			bombarea = (playerbomb->getPositionY() - 32) / 64;
			for (; bombarea <= ((playerbomb->getPositionY() - 32) / 64 + power1); bombarea++) {
				if (bombarea <= 12) {
				bargid = whatisthis(playerbomb->getPositionX()/64, 12 - bombarea);
				if (bargid == 6)break;
				else if (bargid == 5) {
					releasebar(playerbomb->getPositionX()/64, 12 - bombarea);
					break;
				}
			}
			}
		if (j == 999)j = 0;
		else j = j + 1;
		this->removeChild(playerbomb);
	}
    virtual bool init();
	void update(float delta) override;
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	void HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code);
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool isthereabar(int a, int b);

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
