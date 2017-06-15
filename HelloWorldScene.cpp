#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mmp.wav", true);
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto spritelist = SpriteFrameCache::getInstance();
	spritelist->addSpriteFramesWithFile("sc001.plist");
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	_scwidth = visibleSize.width;
	_scheight = visibleSize.height;
	_tileMap = TMXTiledMap::create("01.tmx");
	_tileMap->setAnchorPoint(Vec2::ZERO);
	_tileMap->setPosition(Vec2::ZERO);
	 _bar = _tileMap->getLayer("bar");
	 _prop = _tileMap->getLayer("prop");
	this->addChild(_tileMap,-1);
	auto objects = _tileMap->getObjectGroup("player");
	ValueMap map = objects->getObject("player1");
	int x = map.at("x").asInt()+32;
	int y = map.at("y").asInt()+32;
	_player1 = Sprite::createWithSpriteFrameName("car_01.png");
	_player1->setPosition(x, y);
	_tileMap->addChild(_player1,2);
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this-> schedule(schedule_selector(HelloWorld::update), 0.1f);
    return true;
}
bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	keys[keyCode] = true;
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	keys[keyCode] = false;
}
void HelloWorld::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Node::update(delta);
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow= EventKeyboard::KeyCode::KEY_UP_ARROW, downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		space = EventKeyboard::KeyCode::KEY_SPACE;
	if (HelloWorld::isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE) == true) {
		if(isplaceboom()==false)creatbomb();
		setplaceboom(true);
	}
	else {
		setplaceboom(false);
	}
	if (isKeyPressed(leftArrow)) {
		keyPressedDuration(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedDuration(rightArrow);
	}
	else if (isKeyPressed(upArrow)) {
		keyPressedDuration(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedDuration(downArrow);
	}
	else if (isKeyPressed(space)) {
		keyPressedDuration(space);
	}
	int jj = returnj();
	int ii = returni();
	int boomboomboom = (int)clock() - (int)boomtime[jj];
	if (boomboomboom >= 4900&&ii>jj) {
		bombboom();
	}
	thisprop(_player1->getPositionX()/64,12-int( _player1->getPositionY()/64));
}
void HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		leftdz();
		if (_player1->getPositionX() <= (32 + player1v)) {
			offsetX = 32 - _player1->getPositionX();
			offsetY = 0;
		}
		else if (map_x() - 1 < 0) {
			offsetX = -player1v; offsetY = 0;
		}
		else if(isthereabar(map_x() - 1,12- map_y()) == false){ offsetX = -player1v;
		offsetY = 0;
		}
		else if(_player1->getPositionX()-map_x()*64<=(32+player1v)){
			offsetX = 32 + map_x() * 64 - _player1->getPositionX();
			 offsetY = 0;
		}
		else {
			offsetX = -player1v;
			offsetY = 0;
		}
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		rightdz();
		if (_player1->getPositionX() >= (800 - player1v)) {
			offsetX =800- _player1->getPositionX();
			offsetY = 0;
		}
		else if (map_x() + 1 > 12) {
			offsetX = player1v; offsetY = 0;
		}
		else if (isthereabar(map_x() + 1,12- map_y()) == false) {
			offsetX = player1v;
			offsetY = 0;
		}
		else if (64 - _player1->getPositionX() + map_x() * 64 <= (32 + player1v)) {
			offsetX =  32 + map_x() * 64-_player1->getPositionX();
			offsetY = 0;
		}
		else {
			offsetX = player1v;
			offsetY = 0;
		}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		updz();
		if (_player1->getPositionY() >= (800 - player1v)) {
			offsetX = 0;
			offsetY = 800 - _player1->getPositionY();
		}
		else if (map_y() + 1 > 12) {
			offsetX = 0; offsetY = player1v;
		}
		else if (isthereabar(map_x(), 12- map_y() - 1) == false) {
			offsetX = 0;
			offsetY = player1v;
		}
		else if (64 - _player1->getPositionY() + map_y() * 64 <= (32 + player1v)) {
			offsetX = 0;
			offsetY = 32 + map_y() * 64 - _player1->getPositionY();
		}
		else {
			offsetX = 0;
			offsetY = player1v;
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		downdz();
		if (_player1->getPositionY() <= (32 + player1v)) {
			offsetX = 0;
			offsetY = 32 - _player1->getPositionY();
		}
		else if (map_y() - 1 < 0) {
			offsetX = 0; offsetY = -player1v;
		}
		else if (isthereabar(map_x(), 12 - map_y() + 1) == false) {
			offsetX = 0;
			offsetY = -player1v;
		}
		else if (_player1->getPositionY() - map_y() * 64 <= (32 + player1v)) {
			offsetX = 0;
			offsetY = 32 + map_y() * 64 - _player1->getPositionY();
		}
		else {
			offsetX = 0;
			offsetY = -player1v;
		}
		break;
	default:
		offsetY = offsetX = 0;
		break;
	};
	// 0.1s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.09, Vec2(_player1->getPositionX() + offsetX, _player1->getPositionY() + offsetY));
	_player1->runAction(moveTo);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom cust=omEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}
bool HelloWorld::isthereabar(int a,int b) {
	int x= _bar->getTileGIDAt(ccp(a, b));
	if (x==5||x==6)return true;
	else return false;
}
void HelloWorld::leftdz() {
	auto playeranimationup = Animation::create();
	for (int i = 5; i < 9; i++) {
		playeranimationup->addSpriteFrameWithFile(StringUtils::format("car_%d.png", i));
	}
	playeranimationup->setDelayPerUnit(0.1f / 4.0f);
	playeranimationup->setRestoreOriginalFrame(true);
	auto runfup = Animate::create(playeranimationup);
	_player1->runAction(runfup);
}
void HelloWorld::rightdz() {
	auto playeranimationup = Animation::create();
	for (int i = 9; i < 13; i++) {
		playeranimationup->addSpriteFrameWithFile(StringUtils::format("car_%d.png", i));
	}
	playeranimationup->setDelayPerUnit(0.1f / 4.0f);
	playeranimationup->setRestoreOriginalFrame(true);
	auto runfup = Animate::create(playeranimationup);
	_player1->runAction(runfup);
}
void HelloWorld::updz() {
	auto playeranimationup = Animation::create();
	for (int i = 13; i < 17; i++) {
		playeranimationup->addSpriteFrameWithFile(StringUtils::format("car_%d.png", i));
	}
	playeranimationup->setDelayPerUnit(0.1f / 4.0f);
	playeranimationup->setRestoreOriginalFrame(true);
	auto runfup = Animate::create(playeranimationup);
	_player1->runAction(runfup);
}
void HelloWorld::downdz() {
	auto playeranimationup = Animation::create();
	for (int i = 1; i < 5; i++) {
		playeranimationup->addSpriteFrameWithFile(StringUtils::format("car_%d.png", i));
	}
	playeranimationup->setDelayPerUnit(0.1f / 4.0f);
	playeranimationup->setRestoreOriginalFrame(true);
	auto runfup = Animate::create(playeranimationup);
	_player1->runAction(runfup);
}
int HelloWorld::whatisthis(int a,int b){
	return _bar->getTileGIDAt(ccp(a, b));
}
void HelloWorld::releasebar(int a, int b) {
	_bar->setTileGID(0,ccp(a, b));
}
void  HelloWorld::thisprop(int a, int b){
	int x = _prop->getTileGIDAt(ccp(a, b));
	if (x == 1)player1v = player1v + 2;
	else if (x == 3)power1 = power1 + 1;
	else if (x == 4)bombnum1 = bombnum1 + 1;
	if(x!=0)_prop->setTileGID(0, ccp(a, b));
}