#include <iostream>
#include "NPC.h"

/* ������ʾ */
void NPC::update() {
	CCLOG("update is being called");
	if (isTrigger()) {
		triggerTip();  // ��ҽ��봥����Χ
	}
	else {
		trggerTipRemove();   // ����뿪������Χ
	}
}

/* �ж��Ƿ��ڴ�����Χ�� */
bool NPC::isTrigger() {
	if (who == nullptr)
		return false;

	int dx = who->mySprite->getPosition().x - x;
	int dy = who->mySprite->getPosition().y - y;

	return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);
}

/* ��NPC���� */
void NPC::Chat() {
	/* �ж��Ƿ��ڴ�����Χ�� */
	if (!this->isTrigger())
		return;

    /* ����Ի���chatPanel */
    auto winSize = Director::getInstance()->getWinSize();
	Vec2 where = Vec2(who->getXY().x , who->getXY().y- 180);
	if (role == "npc0")
		where = Vec2(winSize.width / 2, winSize.height - 1100);
    auto chatPanel = Sprite::create("UI/Panel5.png");

    chatPanel->setContentSize(Size(1800, 350));
    chatPanel->setPosition(where); 
	chatPanel->setOpacity(220);
    scene->addChild(chatPanel, 2);

	/* ����npc */
	auto npcSprite = Sprite::create("Role/" + role + "/1.png");
	npcSprite->setPosition(Vec2(who->getXY().x - 430, who->getXY().y - 140));

	if (role == "npc0")
		npcSprite->setPosition(Vec2(winSize.width / 2 - 430, winSize.height - 1000));
	npcSprite->setScale(1.5f);
	scene->addChild(npcSprite, 3);

	/* ����npc�������� */
	std::unordered_map<std::string, int> stringMap = {
		{"npc0", 0},
		{"npc1", 1},
		{"npc2", 2},
		{"npc3", 3},
		{"npc4", 4},
		{"npc5", 5},
		{"npc6", 6},
		{"npc7", 7},
		{"npc8", 8},
		{"npc9", 9}
	};

	switch (stringMap[role]) {
	/* ��ѧnpc */
	case 0:
		npc0([=]() {
			// ��npc0�ĶԻ��߼���ɺ��Ƴ�UI
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			CCLOG("npc0-chat over.");
			});
		break;
	/* �������������npc */
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
	/* ����npc */
	case 6:
		npc6([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc5-chat over.");
			});
		break;
	case 7:
		npc7([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc5-chat over.");
			});
		break;
	case 8:
		npc8([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc5-chat over.");
			});
		break;
	case 9:
		npc9([=]() {
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc5-chat over.");
			});
		break;
	default:
		
		break;
	}

}

/* npc��Ӧ���� */
void NPC::setTasks() {
	// ��������
	if (role == "npc1") {
		npc_task = new task("Task 1", "This is the 1st task.", 1, 0);
	}
	else if (role == "npc2") {
		npc_task = new task("Task 2", "This is the 2nd task.", 1, 0);
	}
	else if (role == "npc3") {
		npc_task = new task("Task 3", "This is the 3rd task.", 1, 0);
	}
	else if (role == "npc4") {
		npc_task= new task("Task 4", "This is the 4th task.", 1, 0);
	}
	else if (role == "npc5") {
		npc_task = new task("Final Task", "This is the 5th task.", 1, 0);
	}
	// ֧������
	else if (role == "npc6") {
		npc_task = new task("LTask 1", "This is the 1st task.", 0, 0);
	}
	else if (role == "npc7") {
		npc_task = new task("LTask 2", "This is the 2nd task.", 0, 0);
	}
	else if (role == "npc8") {
		npc_task = new task("LTask 3", "This is the 3rd task.", 0, 0);
	}
	else if (role == "npc9") {
		npc_task = new task("LTask 4", "This is the 4th task.", 0, 0);
	}
}

/* NPC�������� */
void NPC::NPCunlockTask(bool idx) {
	if (idx) {
		bag->taskUnlock(1, npc_task);
	}
	else {
		bag->taskUnlock(0, npc_task);
	}
}

/* NPC������� */
void NPC::NPCfinishTask() {
	npc_task->isFinished = true;
}

/* npc�Ի��߼� */
/************ ��ѧnpc ************/
void NPC::npc0(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();
	/* npc˵��-1 */
	auto npcTxt1 = Label::createWithTTF("Hello! Welcome to this new world!", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 4);

	/* player�ش�ѡ��1 */
	auto playerAns1 = Label::createWithTTF("Nice to meet you!", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player�ش�ѡ��2 */
	auto playerAns2 = Label::createWithTTF("I like this world.", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player�ش�ѡ��1�ύ��ť */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button, 4);
	/* player�ش�ѡ��2�ύ��ť */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1160));
	scene->addChild(Ans2Button, 4);

	/* �ش�ѡ��1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// �Ƴ���һ���ʴ��Ԫ��
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("Nice to meet you too!", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 4);
		/* �����Ի� */
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
	/* �ش�ѡ��2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("Enjoy yourself here!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 4);
		/* �����Ի� */
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

/******** ������������npc ********/
void NPC::npc1(std::function<void()> callback) {
	isChatting = true;

	/* npc˵��-1 */
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
	/* NextButton���� */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// ��������
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[0]) {
			Mtasks[0] = true;
			if (bag) {
				NPCunlockTask(1);
			}	
			// �Ի�
			npcTxt1->setString("The 1st main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 1st main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// ��һ��:�����Ի�
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			npcTxt1 = nullptr;
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

	/* npc˵��-1 */
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
	/* NextButton���� */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// ��������
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[1]) {
			Mtasks[1] = true;
			if (bag) {
				NPCunlockTask(1);
			}
				
			// �Ի�
			npcTxt1->setString("The 2nd main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 2nd main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// ��һ��:�����Ի�
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			npcTxt1 = nullptr;
			CloseButton->removeFromParent();
			CloseButton = nullptr;
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

	/* npc˵��-1 */
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
	/* NextButton���� */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// ��������
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[2]) {
			Mtasks[2] = true;
			if (bag) {
				NPCunlockTask(1);
			}
			// �Ի�
			npcTxt1->setString("The 3rd main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 3rd main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// ��һ��:�����Ի�
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 230));///////////
		scene->addChild(CloseButton, 4);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt1->removeFromParent();
			npcTxt1 = nullptr;
			CloseButton->removeFromParent();
			CloseButton = nullptr;
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

	/* npc˵��-1 */
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
	/* NextButton���� */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// ��������
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[3]) {
			Mtasks[3] = true;
			if (bag) {
				NPCunlockTask(1);
			}
			// �Ի�
			npcTxt1->setString("The 4th main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 4th main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// ��һ��:�����Ի�
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

	/* npc˵��-1 */
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
	/* NextButton���� */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// ��������
		NextButton->removeFromParent();
		NextButton = nullptr;
		if (!Mtasks[4]) {
			Mtasks[4] = true;
			if (bag) {
				NPCunlockTask(1);
			}
			// �Ի�
			npcTxt1->setString("The 5th main-line task is unlocked.\nClose the chat window and checkout your bag!");
		}
		else {
			npcTxt1->setString("The 5th main-line task has been unlocked.\nClose the chat window and checkout your bag!");
		}
		// ��һ��:�����Ի�
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

/************ ����npc ************/
void NPC::npc6(std::function<void()> callback) {
	isChatting = true;
	/* npc˵��-1 */
	auto npcTxt1 = Label::createWithTTF("What do you want to eat?", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* player�ش�ѡ��1 */
	auto playerAns1 = Label::createWithTTF("Apple!", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 2);
	/* player�ش�ѡ��2 */
	auto playerAns2 = Label::createWithTTF("Beer", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(who->getXY().x, who->getXY().y - 220));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 2);

	/* player�ش�ѡ��1�ύ��ť */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 160));
	scene->addChild(Ans1Button, 2);
	/* player�ش�ѡ��2�ύ��ť */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 220));
	scene->addChild(Ans2Button, 2);

	/* �ش�ѡ��1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		// ������ƻ��
		goods _goods;
		consumable* it = new consumable(_goods.apple);
		bag->addItem(it);
		// �Ƴ���һ���ʴ��Ԫ��
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("Here you are!", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 2);
		/* �����Ի� */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			isChatting = false;
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* �ش�ѡ��2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		// ������ơ��
		goods _goods;
		consumable* it = new consumable(_goods.beer);
		bag->addItem(it);
		// �Ƴ�UI���
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("Here you are!", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 2);
		/* �����Ի� */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			isChatting = false;
			npcTxt2_2->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});
		});
}

void NPC::npc7(std::function<void()> callback) {
	isChatting = true;
	/* npc˵��-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc6 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* player�ش�ѡ��1 */
	auto playerAns1 = Label::createWithTTF("This is player's answer 1", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 2);
	/* player�ش�ѡ��2 */
	auto playerAns2 = Label::createWithTTF("This is player's answer 2", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(who->getXY().x, who->getXY().y - 220));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 2);

	/* player�ش�ѡ��1�ύ��ť */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 160));
	scene->addChild(Ans1Button, 2);
	/* player�ش�ѡ��2�ύ��ť */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 220));
	scene->addChild(Ans2Button, 2);

	/* �ش�ѡ��1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		isChatting = false;
		// �Ƴ���һ���ʴ��Ԫ��
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("This is npc6 speaking 2-1", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 2);
		/* �����Ի� */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* �ش�ѡ��2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		isChatting = false;
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("This is npc6 speaking 2-2", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 2);
		/* �����Ի� */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
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

void NPC::npc8(std::function<void()> callback) {
	isChatting = true;
	/* npc˵��-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc6 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(who->getXY().x, who->getXY().y - 110));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1, 2);

	/* player�ش�ѡ��1 */
	auto playerAns1 = Label::createWithTTF("This is player's answer 1", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(who->getXY().x, who->getXY().y - 160));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 2);
	/* player�ش�ѡ��2 */
	auto playerAns2 = Label::createWithTTF("This is player's answer 2", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(who->getXY().x, who->getXY().y - 220));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 2);

	/* player�ش�ѡ��1�ύ��ť */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 160));
	scene->addChild(Ans1Button, 2);
	/* player�ش�ѡ��2�ύ��ť */
	auto Ans2Button = ui::Button::create("Button/Choice2Button.png", "Button/Choice2ButtonClicked.png");
	Ans2Button->ignoreContentAdaptWithSize(false);
	Ans2Button->setContentSize(Size(40, 40));
	Ans2Button->setTitleFontSize(24);
	Ans2Button->setPosition(Vec2(who->getXY().x - 250, who->getXY().y - 220));
	scene->addChild(Ans2Button, 2);

	/* �ش�ѡ��1 */
	Ans1Button->addClickEventListener([=](Ref* sender) mutable {
		isChatting = false;
		// �Ƴ���һ���ʴ��Ԫ��
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice1 */
		auto npcTxt2_1 = Label::createWithTTF("This is npc6 speaking 2-1", "fonts/Lacquer.ttf", 35);
		npcTxt2_1->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_1->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_1, 2);
		/* �����Ի� */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
		CloseButton->addClickEventListener([=](Ref* sender) mutable {
			npcTxt2_1->removeFromParent();
			CloseButton->removeFromParent();
			if (callback) {
				callback();
			}
			return;
			});

		});
	/* �ش�ѡ��2 */
	Ans2Button->addClickEventListener([=](Ref* sender) mutable {
		isChatting = false;
		npcTxt1->removeFromParent();
		playerAns1->removeFromParent();
		playerAns2->removeFromParent();
		Ans1Button->removeFromParent();
		Ans2Button->removeFromParent();
		/* npc˵��-2-choice2 */
		auto npcTxt2_2 = Label::createWithTTF("This is npc6 speaking 2-2", "fonts/Lacquer.ttf", 35);
		npcTxt2_2->setPosition(Vec2(who->getXY().x, who->getXY().y - 120));
		npcTxt2_2->setTextColor(Color4B(0, 0, 0, 255));
		scene->addChild(npcTxt2_2, 2);
		/* �����Ի� */
		auto CloseButton = ui::Button::create("Button/CloseButton.png", "Button/CloseButtonClicked.png");
		CloseButton->ignoreContentAdaptWithSize(false);
		CloseButton->setContentSize(Size(40, 40));
		CloseButton->setTitleFontSize(24);
		CloseButton->setPosition(Vec2(who->getXY().x, who->getXY().y - 180));
		scene->addChild(CloseButton, 2);
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

void NPC::npc9(std::function<void()> callback) {
	isChatting = true;

	/* npc˵��-1 */
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
	/* NextButton���� */
	NextButton->addClickEventListener([=](Ref* sender)mutable {
		// ��������
		NextButton->removeFromParent();
		NextButton = nullptr;
		npcTxt1->setString("hahaha");
		
		// ��һ��:�����Ի�
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