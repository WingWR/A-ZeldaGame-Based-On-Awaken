#ifndef __MICRO_MAP_H__
#define __MICRO_MAP_H__

#include "cocos2d.h"
#include<string>

class MicroMap : public cocos2d::Node {
private:


public:
    /*����΢�����ͼ*/
    static MicroMap* create(const std::string& mapName);

    /*��ʼ��΢�����ͼ*/
    bool init(const std::string& mapName);




};

#endif // __MICRO_MAP_H__