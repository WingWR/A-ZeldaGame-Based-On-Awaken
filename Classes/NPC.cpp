#include <iostream>
#include "NPC.h"

/* 交互提示 */
void NPC::update() {
	CCLOG("update is being called");
	if (isTrigger()) {
		triggerTip();  // 玩家进入触发范围
	}
	else {
		trggerTipRemove();   // 玩家离开触发范围
	}
}

/* 判断是否在触发范围内 */
bool NPC::isTrigger() {
	if (who == nullptr)
		return false;

	int dx = who->mySprite->getPosition().x - x;
	int dy = who->mySprite->getPosition().y - y;

	return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);
}

/* 与NPC交互 */
void NPC::Chat() {
	/* 判断是否在触发范围内 */
	if (!this->isTrigger())
		return;

    /* 加入对话框chatPanel */
    auto winSize = Director::getInstance()->getWinSize();
	Vec2 where = Vec2(who->getXY().x , who->getXY().y- 180);
	if (role == "npc0")
		where = Vec2(winSize.width / 2, winSize.height - 1100);
    auto chatPanel = Sprite::create("UI/Panel5.png");

    chatPanel->setContentSize(Size(1800, 350));
    chatPanel->setPosition(where); 
	chatPanel->setOpacity(220);
    scene->addChild(chatPanel, 2);

	/* 加入npc */
	auto npcSprite = Sprite::create("Role/" + role + "/1.png");
	npcSprite->setPosition(Vec2(who->getXY().x - 430, who->getXY().y - 140));

	if (role == "npc0")
		npcSprite->setPosition(Vec2(winSize.width / 2 - 430, winSize.height - 1000));
	npcSprite->setScale(1.5f);
	scene->addChild(npcSprite, 3);

	/* 根据npc创建互动 */
	std::unordered_map<std::string, int> stringMap = {
		{"npc0", 0},
		{"npc1", 1},
		{"npc2", 2},
		{"npc3", 3},
		{"npc4", 4},
		{"npc5", 5},
		{"npc6", 6}
	};

	switch (stringMap[role]) {
	/* 教学npc */
	case 0:
		npc0([=]() {
			// 当npc0的对话逻辑完成后，移除UI
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			CCLOG("npc0-chat over.");
			});
		break;
	/* 解锁主线任务的npc */
	case 1:
		npc1([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			CCLOG("npc1-chat over.");
			});
		break;
	case 2:
		npc2([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			CCLOG("npc2-chat over.");
			});
		break;
	case 3:
		npc3([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc3-chat over.");
			});
		break;
	case 4:
		npc4([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc4-chat over.");
			});
		break;
	case 5:
		npc5([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc5-chat over.");
			});
		break;
	/* 其它npc */
	case 6:

		break;
	default:
		
		break;
	}

}

/* npc对话逻辑 */
/************ 教学npc ************/
void  NPC::npc0(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();
	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Hello! Welcome to this new world!", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 4);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("Nice to meet you!", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("I like this world.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button, 4);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1160));
	scene->addChild(Ans2Button, 4);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("Nice to meet you too!", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("Enjoy yourself here!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});
		});
}

/******** 解锁主线任务npc ********/
void NPC::npc1(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 1", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[0]) {
			Mtasks[0] = true;
			if (bag)
				bag->taskUnlock(1, 1);
			// 对话
			npcTxt1->setString("The 1st main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 1st main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc2(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 2", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[0]) {
			Mtasks[0] = true;
			if (bag)
				bag->taskUnlock(2, 1);
			// 对话
			npcTxt1->setString("The 2nd main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 2nd main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc3(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 3", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[0]) {
			Mtasks[0] = true;
			if (bag)
				bag->taskUnlock(3, 1);
			// 对话
			npcTxt1->setString("The 3rd main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 3rd main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc4(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 4", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[0]) {
			Mtasks[0] = true;
			if (bag)
				bag->taskUnlock(4, 1);
			// 对话
			npcTxt1->setString("The 4th main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 4th main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc5(std::function<void()> callback) {
	isChatting = true;

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("Taskkkkkk 5", "fonts/Lacquer.ttf", 30);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));///////////
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* NextButton */
	auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
	NextButton->ignoreContentAdaptWithSize(false);
	NextButton->setContentSize(Size(60, 60));
	NextButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
	NextButton->setOpacity(220);
	scene->addChild(NextButton, 2);
	/* NextButton监听 */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// 解锁任务
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[0]) {
			Mtasks[0] = true;
			if (bag)
				bag->taskUnlock(5, 1);
			// 对话
			npcTxt1->setString("The 5th main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 5th main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// 下一步:结束对话
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			CloseButton->removeFromParent();
			isChatting = false;
			if (callback) {
				callback();
			}
			return;
			});
		});
}

/************ 其它npc ************/
void NPC::npc6(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();

	/* npc说话-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc6 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 4);

	/* player回答选择1 */
	auto playerAns1 = Label::createWithTTF("This is player's answer 1", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player回答选择2 */
	auto playerAns2 = Label::createWithTTF("This is player's answer 2", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player回答选择1提交按钮 */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button, 4);
	/* player回答选择2提交按钮 */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1160));
	scene->addChild(Ans2Button, 4);

	/* 回答选择1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// 移除第一次问答的元素
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("This is npc6 speaking 2-1", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* 回答选择2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc说话-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("This is npc6 speaking 2-2", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 4);
		/* 结束对话 */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1150));
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
}
