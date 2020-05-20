//
// Created by rsanpui on 5/20/2020.
//

#ifndef PROJ_ANDROID_MAINMENU_H
#define PROJ_ANDROID_MAINMENU_H
#include "cocos2d.h"

class MainMenu : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::CCObject* pSender);
    CREATE_FUNC(MainMenu);
    void GoToGameScene( cocos2d::Ref *sender );
};


#endif //PROJ_ANDROID_MAINMENU_H
