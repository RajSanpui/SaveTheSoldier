//
// Created by rsanpui on 5/14/2020.
//

#ifndef PROJ_ANDROID_PHYSICSCLASS_H
#define PROJ_ANDROID_PHYSICSCLASS_H

#include "cocos2d.h"

class PhysicsClass : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();

    void menuCloseCallback(cocos2d::CCObject* pSender);
    CREATE_FUNC(PhysicsClass);
private:
    cocos2d::Sprite* soldierSprite;
    void addBoulder(float dt);
    void initializePhysics(cocos2d::Sprite* sprite);
    void initTouch();
    void moveSoldier(cocos2d::Touch* toque, cocos2d::Event* event);
};



#endif //PROJ_ANDROID_PHYSICSCLASS_H
