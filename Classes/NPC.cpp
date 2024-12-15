#include <iostream>
#include <NPC.h>

/* �ж��Ƿ��ڴ�����Χ�� */
bool NPC::isTrigger() {
	if (who == nullptr)
		return false;

	int dx = who->mySprite->getPosition().x - x;
	int dy = who->mySprite->getPosition().y - y;

	if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2)) {
		return true;
	}
	return false;
}

/* ��NPC���� */
void NPC::Chat() {
	/* �ж��Ƿ��ڴ�����Χ�� */
	if (!isTrigger())
		return;

    /* ����Ի���chatPanel */
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 where = Vec2(winSize.width / 2, winSize.height - 1100);
    auto chatPanel = Sprite::create("UI/Panel4.png");
    chatPanel->setContentSize(Size(1800, 330));
    chatPanel->setPosition(where); 
	chatPanel->setOpacity(190);
    scene->addChild(chatPanel, 2);

	/* ����npc */
	auto npcSprite = Sprite::create("Role/" + role + "/1.png");
	npcSprite->setPosition(Vec2(winSize.width / 2 - 330, winSize.height - 1000));
	npcSprite->setScale(2.5 * scale);
	scene->addChild(npcSprite, 3);

	/* ����npc�������� */
	std::unordered_map<std::string, int> stringMap = {
		{"npc1", 1},
		{"npc2", 2},
		{"npc3", 3}
	};

	switch (stringMap[role]) {
	case 1:
		npc1([=]() {
			//�� npc1�ĶԻ��߼���ɺ��Ƴ�UI
			npcSprite->removeFromParent();
			chatPanel->removeFromParent();
			log("npc1-chat over.");
			});
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	default:
		
		break;
	}

}

void NPC::npc1(std::function<void()> callback) {
	auto winSize = Director::getInstance()->getWinSize();

	/* npc˵��-1 */
	auto npcTxt1 = Label::createWithTTF("This is npc1 speaking 1", "fonts/Lacquer.ttf", 35);
	npcTxt1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1000));
	npcTxt1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(npcTxt1,4);

	/* player�ش�ѡ��1 */
	auto playerAns1 = Label::createWithTTF("This is player's answer 1", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns1->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1080));
	playerAns1->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns1, 4);
	/* player�ش�ѡ��2 */
	auto playerAns2 = Label::createWithTTF("This is player's answer 2", "fonts/KuaiLe_Chinese.ttf", 25);
	playerAns2->setPosition(Vec2(winSize.width / 2 + 50, winSize.height - 1160));
	playerAns2->setTextColor(Color4B(0, 0, 0, 255));
	scene->addChild(playerAns2, 4);

	/* player�ش�ѡ��1�ύ��ť */
	auto Ans1Button = ui::Button::create("Button/Choice1Button.png", "Button/Choice1ButtonClicked.png");
	Ans1Button->ignoreContentAdaptWithSize(false);
	Ans1Button->setContentSize(Size(40, 40));
	Ans1Button->setTitleFontSize(24);
	Ans1Button->setPosition(Vec2(winSize.width / 2 - 200, winSize.height - 1080));
	scene->addChild(Ans1Button,4);
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
		auto npcTxt2_1 = Label::createWithTTF("This is npc1 speaking 2-1", "fonts/Lacquer.ttf", 35);
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
		CloseButton->addClickEventListener([=](Ref* sender) mutable{
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
		auto npcTxt2_2 = Label::createWithTTF("This is npc1 speaking 2-2", "fonts/Lacquer.ttf", 35);
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

