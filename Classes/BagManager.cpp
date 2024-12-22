#include "BagManager.h"
#include "audio/include/AudioEngine.h"

// ����ʵ�� 
BagManager* BagManager::_instance = nullptr;

// ��ȡ����ʵ�� 
BagManager* BagManager::getInstance()
{
    // ���ʵ�������ڣ�����һ���µ�ʵ��
    if (_instance == nullptr) 
    {
        _instance = new BagManager();  // ����ʵ��
        _instance->init();  // ��ʼ��ʵ��
    }
    return _instance;  // ����ʵ��ָ��
}

// ���캯��
BagManager::BagManager() : _isBagOpen(false), _bagPanel(nullptr)
{
    for (int i = 0; i < 40; i++)
        items[i] = nullptr;
    items_num = 0;
    // ����ʾ��������ı�ǩ�ÿ�
    coinsLabel = nullptr;
}

// ��������
BagManager::~BagManager()
{
    if (_bagPanel) 
        _bagPanel->removeFromParent();
    if (_bagBackground) 
        _bagBackground->release();
    if (_characterBackground)
        _characterBackground->release();
}

// ��ʼ������������
bool BagManager::init()
{
    if (!Node::init()) 
        return false;  // ��ʼ��ʧ��

    // ����������壬��Ϊ����UI������
    _bagPanel = Node::create();
    this->addChild(_bagPanel);  // �����������ӵ���ǰ�ڵ�
    _bagPanel->setVisible(false);  // Ĭ������±��������ص�
    
    return true;  // ��ʼ���ɹ�
}

// ��ʾ����
void BagManager::showBag(Player& _player)
{
    player = _player;
    player.x = _player.getXY().x;
    player.y = _player.getXY().y;
    // ���������δ�򿪣��򴴽�����ʾ��������
    if (!_isBagOpen)
    {
        // ��Ϸ��ͣ
        //Director::getInstance()->pause();

        // ���ű����򿪵���Ч
        cocos2d::AudioEngine::play2d("music/bag.mp3");

        // �������������壬�͹ر��������
        if (_taskBackground)
        {
            _bagPanel->removeAllChildren();
            _taskBackground = nullptr;
        }

        // ������������
        createBagBackground();

        // ������Ʒ���ڵ���Ʒ
        updateBagUI();

        // ������ɫ���
        createCharacterPanel();

        // ��������尴ť
        createTaskButton();

        // ���ű����򿪵���Ч
        cocos2d::AudioEngine::play2d("music/bag.mp3");

        _bagPanel->setVisible(true);  // ��ʾ�������
        _isBagOpen = true;
    }
}

// ��ʾ����(���غ���)
void BagManager::showBag()
{
    // ���������δ�򿪣��򴴽�����ʾ��������
    if (!_isBagOpen)
    {
        // ��Ϸ��ͣ
        //Director::getInstance()->pause();

        // �������������壬�͹ر��������
        if (_taskBackground)
        {
            _bagPanel->removeAllChildren();
            _taskBackground = nullptr;
        }

        // ������������
        createBagBackground();

        // ������Ʒ���ڵ���Ʒ
        updateBagUI();

        // ������ɫ���
        createCharacterPanel();

        // ��������尴ť
        createTaskButton();

        _bagPanel->setVisible(true);  // ��ʾ�������
        _isBagOpen = true;
    }
}

// ���ر���
void BagManager::hideBag(Player& _player)
{
    if (_isBagOpen)
    {
        // �ָ���Ϸ
        //Director::getInstance()->resume();
        // ���Źرձ�������Ч
        cocos2d::AudioEngine::play2d("music/bag.mp3");
        _bagPanel->setVisible(false);  // ���ر������
        _bagPanel->removeAllChildren(); // ����ӽڵ�
        _bagBackground = nullptr;  // �������ָ��
        _characterBackground = nullptr;
        coinsLabel = nullptr;
        _isBagOpen = false;  // ����״̬
        _player = player;
    }
}

// ���ر���(���غ���)
void BagManager::hideBag()
{
    if (_isBagOpen)
    {
        _bagPanel->setVisible(false);  // ���ر������
        _bagPanel->removeAllChildren(); // ����ӽڵ�
        _bagBackground = nullptr;  // �������ָ��
        _characterBackground = nullptr;
        coinsLabel = nullptr;
        _isBagOpen = false;  // ����״̬
    }
}

// ������������尴ť
void BagManager::createTaskButton()
{
    // ������������尴ť
    auto taskButton = Button::create("Button/Button2.png");
    // ����ť�����ڱ���������
    taskButton->setAnchorPoint(Vec2(0.75, 0));
    taskButton->setPosition(Vec2(0, _bagBackground->getContentSize().height * 3 / 4));
    _bagBackground->addChild(taskButton);
    // �������
    auto taskLabel = Label::createWithTTF("MY Task", "fonts/arial.ttf", 16);
    taskLabel->setPosition(Vec2(taskButton->getContentSize().width / 2, taskButton->getContentSize().height / 2));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    taskLabel->setTextColor(Color4B(255, 215, 0, 255));
    taskButton->addChild(taskLabel);
    // ���ð�ť����¼�
    taskButton->addClickEventListener([=](Ref* sender) {
        hideBag();
        createTaskPanel();
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
}

// �����������
void BagManager::createTaskPanel()
{
    _bagPanel->setVisible(true);
    // ��Ϸ��ͣ
    //Director::getInstance()->pause();
    // ����������屳��ͼƬ
    _taskBackground = Sprite::create("Bag/task_background.png");
    _taskBackground->setPosition(Vec2(player.x, player.y));
    _bagPanel->addChild(_taskBackground);

    // ��������
    auto titleLabel = Label::createWithTTF("MY TASK", "fonts/Bebas.ttf", 32);
    titleLabel->setPosition(Vec2(_taskBackground->getContentSize().width / 2, _taskBackground->getContentSize().height - 20));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    titleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _taskBackground->addChild(titleLabel);

    // �����򿪱�����尴ť
    auto bagButton = Button::create("Button/Button2.png");
    // ����ť�����ڱ���������
    bagButton->setAnchorPoint(Vec2(0.75, 0));
    bagButton->setPosition(Vec2(0, _taskBackground->getContentSize().height * 3 / 4));
    _taskBackground->addChild(bagButton);
    // �������
    auto bagLabel = Label::createWithTTF("MY BAG", "fonts/arial.ttf", 16);
    bagLabel->setPosition(Vec2(bagButton->getContentSize().width / 2, bagButton->getContentSize().height / 2));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    bagLabel->setTextColor(Color4B(255, 215, 0, 255));
    bagButton->addChild(bagLabel);
    // ���ð�ť����¼�
    bagButton->addClickEventListener([=](Ref* sender) {
        _bagPanel->removeChild(_taskBackground);
        _taskBackground = nullptr;
        showBag();
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    updateTaskUI();
    
}

// �����������UI
void BagManager::updateTaskUI()
{
    // ��ʾ֧������
    // ���ù���
    createScrollView(Vec2(0, 40), myLineQuest);
    // ���֧���������
    auto sideQuestLabel = Label::createWithTTF("My Side Quest", "fonts/arial.ttf", 16);
    sideQuestLabel->setTextColor(Color4B(255, 215, 0, 255));
    sideQuestLabel->setPosition(Vec2(_taskBackground->getContentSize().width / 2, 180));
    _taskBackground->addChild(sideQuestLabel);

    // ��ʾ��������
    // ���ù���
    createScrollView(Vec2(0, 220), myMainlineTask);
    // ���֧���������
    auto mainlineTaskLabel = Label::createWithTTF("My Mainline Task", "fonts/arial.ttf", 16);
    mainlineTaskLabel->setTextColor(Color4B(255, 215, 0, 255));
    mainlineTaskLabel->setPosition(Vec2(_taskBackground->getContentSize().width / 2, 360));
    _taskBackground->addChild(mainlineTaskLabel);
}

// ���� ScrollView
void BagManager::createScrollView(Vec2 position, vector<task*> myTask)
{
    // ���� ScrollView
    auto scrollView = ScrollView::create();
    // ���ù�������Ĵ�С����ʾ������ť
    float scrollHeight = 2 * 50.0f + 30.0f;
    scrollView->setContentSize(Size(_taskBackground->getContentSize().width, scrollHeight));
    scrollView->setPosition(position);  // ���ù��������λ��
    scrollView->setDirection(ScrollView::Direction::VERTICAL);  // �������
    scrollView->setBounceEnabled(true);  // ���ûص�Ч��
    scrollView->setTouchEnabled(true);  // ���ô����¼�
    _taskBackground->addChild(scrollView);

    // ����һ�����ݽڵ㣨�������а�ť��
    auto contentNode1 = Node::create();
    scrollView->addChild(contentNode1);

    const int taskCount = 10;  // �����10������ť
    float buttonHeight = 50.0f;
    float gap = 20.0f;  // ��ť֮��ļ��

    // ��������ť
    for (int i = 0; i < taskCount; ++i)
    {
        // ��������ť
        auto taskButton = Button::create("Bag/taskName.png");
        taskButton->setPosition(Vec2(_taskBackground->getContentSize().width / 2, (taskCount - i - 0.5) * (buttonHeight + gap)));
        contentNode1->addChild(taskButton);

        if (i >= myTask.size())
        {
            // ��������ǩ
            auto taskLabel = Label::createWithTTF("Task " + std::to_string(i + 1), "fonts/arial.ttf", 16);
            taskLabel->setPosition(Vec2(taskButton->getContentSize().width / 2, taskButton->getContentSize().height / 2));
            taskButton->addChild(taskLabel);

            // ���ð�ť����¼�
            taskButton->addClickEventListener([=](Ref* sender) {
                cocos2d::AudioEngine::play2d("music/lock.mp3");
                });
            // ��ʾ����δ����
            auto lock = Button::create("Bag/lock.png");
            lock->setPosition(Vec2(taskButton->getContentSize().width, taskButton->getContentSize().height));
            taskButton->addChild(lock);
        }
        else
        {
            // ��������ǩ
            auto taskLabel = Label::createWithTTF(myTask[i]->taskName, "fonts/arial.ttf", 12);
            taskLabel->setPosition(Vec2(taskButton->getContentSize().width / 2, taskButton->getContentSize().height / 2));
            taskLabel->setTextColor(Color4B(255, 215, 0, 255));
            taskButton->addChild(taskLabel);
            // ���ð�ť����¼�
            taskButton->addClickEventListener([=](Ref* sender) {
                createTaskInfoPanel(myTask, i);
                cocos2d::AudioEngine::play2d("music/click.mp3");
                });
        }
    }
    // ������������߶ȣ�����������ܸ߶�Ҫ���ڹ�������ĸ߶ȣ�
    contentNode1->setContentSize(Size(_taskBackground->getContentSize().width, taskCount * (buttonHeight + gap) + 5));

    // ���� ScrollView �ڲ������Ĵ�С
    scrollView->setInnerContainerSize(contentNode1->getContentSize());
}

// ����������Ϣ���
void BagManager::createTaskInfoPanel(vector<task*> myTask, int index)
{
    // ��������Ϣ���
    auto taskInfoBackground = Sprite::create("Bag/task_info_background.png");
    float taskInfoBackground_x = _taskBackground->getPositionX() + _taskBackground->getContentSize().width / 2 + taskInfoBackground->getContentSize().width / 2;
    float taskInfoBackground_y = _taskBackground->getPositionY() + _taskBackground->getContentSize().height / 2 - taskInfoBackground->getContentSize().height / 2;
    taskInfoBackground->setPosition(Vec2(taskInfoBackground_x, taskInfoBackground_y));
    _bagPanel->addChild(taskInfoBackground);

    // ��������ʾ��������
    auto taskNameLabel = Label::createWithSystemFont(myTask[index]->taskName, "Arial", 24);
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    taskNameLabel->setTextColor(Color4B(255, 215, 0, 255));
    taskNameLabel->setPosition(Vec2(taskInfoBackground->getContentSize().width / 2, taskInfoBackground->getContentSize().height - 15));  // �����ڱ����Ϸ�
    taskInfoBackground->addChild(taskNameLabel);

    // ��������ʾ��Ʒ������ Label
    auto taskDescriptionLabel = Label::createWithSystemFont(myTask[index]->description, "Arial", 16);
    // ����ê��
    taskDescriptionLabel->setAnchorPoint(Vec2(0, 1));
    // �����ı������Ϊ��Ʒ��Ϣ�����Ŀ�ȣ������ʵ������߾ࣩ
    float maxWidth = taskInfoBackground->getContentSize().width - 10;  // �������ұ߾�
    // ��������Ⱥ͸߶�
    taskDescriptionLabel->setDimensions(maxWidth, 0);
    taskDescriptionLabel->setPosition(Vec2(10, taskInfoBackground->getContentSize().height - 40));  // �����ڱ����Ϸ�
    taskInfoBackground->addChild(taskDescriptionLabel);

    // ��ʾ�������
    if (myTask[index]->isFinished) // �������
    {
        auto taskProgressLabel = Label::createWithSystemFont("Finished", "Arial", 16);
        // ����ê��
        taskProgressLabel->setAnchorPoint(Vec2(0, 0.5));
        // ����������ɫΪ��ɫ
        taskProgressLabel->setTextColor(Color4B(0, 255, 0, 255));
        taskProgressLabel->setPosition(15, 15);
        taskInfoBackground->addChild(taskProgressLabel);
    }
    else
    {
        auto taskProgressLabel = Label::createWithSystemFont("Going", "Arial", 16);
        // ����ê��
        taskProgressLabel->setAnchorPoint(Vec2(0, 0.5));
        // ����������ɫΪ��ɫ
        taskProgressLabel->setTextColor(Color4B(255, 215, 0, 255));
        taskProgressLabel->setPosition(15, 15);
        taskInfoBackground->addChild(taskProgressLabel);
    }

    // �����رհ�ť������ť��
    auto closeButton = Button::create("Bag/close_button.png");
    closeButton->setPosition(Vec2(taskInfoBackground->getContentSize().width, taskInfoBackground->getContentSize().height)); // ���Ͻ�λ��
    closeButton->addClickEventListener([=](Ref* sender) {
        // �������ťʱ�Ƴ� itemInfoBackground
        taskInfoBackground->removeFromParent();  // �Ӹ��ڵ��Ƴ�
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    
    // ���رհ�ť��ӵ�������
    taskInfoBackground->addChild(closeButton);
}

// ���±���UI
void BagManager::updateBagUI()
{
    // ������Ʒ�����ӳߴ�ͼ��
    float xStart = 75.0f;  // ��ʼXλ��
    float yStart = _bagBackground->getContentSize().height - 80.0f;  // ��ʼYλ�ã��������������·���

    // ����5x8����Ʒ����
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 5; ++col)
        {
            // ����ÿ�����ӵ�����
            float xPos = xStart + col * 80;
            float yPos = yStart - row * 70;
            int index = row * 5 + col;

            // �����Ʒ��
            auto slot = Button::create("Bag/item_slot.png");
            slot->setPosition(Vec2(xPos, yPos));
            slot->addClickEventListener([=](Ref* sender) {
                slot_click(slot, row, col);
                });
            _bagBackground->addChild(slot);
            if (items[index] != NULL)
            {
                if (items[index]->image->getParent() == nullptr)// ͼ���Ƿ��и��ڵ�
                {
                    // ������Ʒͼ���λ�ò���ӵ���ť����
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);// ��Ӹ��ڵ�
                    items[index]->image->retain();
                }
                else
                {
                    items[index]->image->removeFromParent();// �Ƴ���ǰ�ĸ��ڵ�
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);
                    items[index]->image->retain();// ��֤ͼ����󲻱�����
                }
            }
        }
    // ���½�ɫ���
    createCharacterPanel();
}

// ������������
void BagManager::createBagBackground()
{
    // ���ñ�������ͼƬ
    _bagBackground = Sprite::create("Bag/bag_background.png");
    _bagBackground->setPosition(Vec2(player.x - 200, player.y));
    _bagPanel->addChild(_bagBackground);

    // ������������
    auto titleLabel = Label::createWithTTF("MY BAG", "fonts/Bebas.ttf", 32);
    titleLabel->setPosition(Vec2(_bagBackground->getContentSize().width / 2, _bagBackground->getContentSize().height - 20));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    titleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _bagBackground->addChild(titleLabel);

    showcoins();
}

// ��ʾ�������
void BagManager::showcoins()
{
   // ��ʾ��ǰ����Ľ����
   // �����ұ�ǩ�Ѿ����ڣ����������ݣ����򣬴����µĽ�ұ�ǩ
    if (coinsLabel) 
        // �������б�ǩ������
        coinsLabel->setString(to_string(player.coins));
    else
    {
        // ���ý��ͼ��
        auto coinsIcon = Sprite::create("Bag/coins.png");
        coinsIcon->setPosition(Vec2(_bagBackground->getContentSize().width - 120, 20));
        _bagBackground->addChild(coinsIcon);
        // �������������ǩ
        coinsLabel = Label::createWithTTF(to_string(player.coins), "fonts/arial.ttf", 16);
        // ����ǩ������ͼ���Ҳ�
        coinsLabel->setAnchorPoint(Vec2(0, 0.5));
        coinsLabel->setPosition(Vec2(_bagBackground->getContentSize().width - 90, 20));
        _bagBackground->addChild(coinsLabel);
    }
}

// ������ɫ���
void BagManager::createCharacterPanel()
{
    // ���ƽ�ɫ���UI
    createCharacterPanelUI();

    // ��ʾ��ɫ��Ϣ
    showCharacterInfo();

    // �ڽ�ɫ����������װ����
    float borderWidth = _characterBackground->getContentSize().width / 2;
    float borderHeight = _characterBackground->getContentSize().height / 2;
    Vec2 borderPosition = Vec2(borderWidth, borderHeight);
    // ����
    auto button1 = Button::create("Bag/item_slot.png");// ��Ӱ�ť
    button1->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y + borderHeight / 2 - 30));
    button1->addClickEventListener([=](Ref* sender) {
        // ���������Ч
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });// ��Ӱ�ť����¼�
    _characterBackground->addChild(button1);
    auto label1 = Label::createWithTTF("Weapon", "fonts/arial.ttf", 12);// ������� 
    label1->setPosition(Vec2(20, -6));
    button1->addChild(label1);

    // ��ȡ��ҵ�����ͼ�����õ�������
    if (player._weapon != nullptr) 
    {
        // ��ȡ����ͼ������
        auto weaponImage = player._weapon->image;
        weaponImage->retain(); // ��֤ͼ����󲻱�����
        weaponImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (weaponImage != nullptr) 
        {
            weaponImage->setPosition(Vec2(button1->getContentSize().width / 2, button1->getContentSize().height / 2));
            button1->addChild(weaponImage);  // ��ͼ����ӵ���������ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton1 = Button::create("Bag/close_button.png");
    closeButton1->setPosition(Vec2(button1->getContentSize().width, button1->getContentSize().height)); // ���Ͻ�λ��
    closeButton1->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._weapon != nullptr)
        {
            player.atk -= player._weapon->increase_attribute;
            player.criticalChance -= player._weapon->increase_criticalChance;
            auto _item = dynamic_cast<item*>(player._weapon); // ��������ָ��ת��Ϊ��Ʒ��ָ��
            player._weapon = nullptr; // ����ɫ����ָ����Ϊ��ָ��
            addItem(_item); // ��ж�µ�װ���Ż���Ʒ��
        }
        });
    button1->addChild(closeButton1);


    // ����
    auto button2 = Button::create("Bag/item_slot.png");
    button2->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y - borderHeight / 2 + 30));
    button2->addClickEventListener([=](Ref* sender) {
        // ���������Ч
        cocos2d::AudioEngine::play2d("music/click.mp3"); 
        });
    _characterBackground->addChild(button2);
    auto label2 = Label::createWithTTF("Armor", "fonts/arial.ttf", 12);
    label2->setPosition(Vec2(20, -6));
    button2->addChild(label2);

    // ��ȡ��ҵĻ���ͼ�����õ�������
    if (player._armor != nullptr)
    {
        // ��ȡ����ͼ������
        auto armorImage = player._armor->image;
        armorImage->retain(); // ��֤ͼ����󲻱�����
        armorImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (armorImage != nullptr)
        {
            armorImage->setPosition(Vec2(button2->getContentSize().width / 2, button2->getContentSize().height / 2));
            button2->addChild(armorImage);  // ��ͼ����ӵ���������ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton2 = Button::create("Bag/close_button.png");
    closeButton2->setPosition(Vec2(button2->getContentSize().width, button2->getContentSize().height)); // ���Ͻ�λ��
    closeButton2->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._armor != nullptr)
        {
            player.def -= player._armor->increase_attribute;
            auto _item = dynamic_cast<item*>(player._armor);
            player._armor = nullptr;
            addItem(_item);
        }
        });
    button2->addChild(closeButton2);


    // Ь��
    auto button3 = Button::create("Bag/item_slot.png");
    button3->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y + borderHeight / 2 - 30));
    button3->addClickEventListener([=](Ref* sender) {
        // ���������Ч
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    _characterBackground->addChild(button3);
    auto label3 = Label::createWithTTF("Shoes", "fonts/arial.ttf", 12);
    label3->setPosition(Vec2(20, -6));
    button3->addChild(label3);

    // ��ȡ��ҵ�Ь��ͼ�����õ�Ь����
    if (player._shoes != nullptr)
    {
        // ��ȡЬ��ͼ������
        auto shoesImage = player._shoes->image;
        shoesImage->retain(); // ��֤ͼ����󲻱�����
        shoesImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (shoesImage != nullptr)
        {
            shoesImage->setPosition(Vec2(button3->getContentSize().width / 2, button3->getContentSize().height / 2));
            button3->addChild(shoesImage);  // ��ͼ����ӵ�Ь������ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton3 = Button::create("Bag/close_button.png");
    closeButton3->setPosition(Vec2(0, button3->getContentSize().height)); // ���Ͻ�λ��
    closeButton3->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._shoes != nullptr)
        {
            player.speed -= player._shoes->increase_attribute;
            auto _item = dynamic_cast<item*>(player._shoes);
            player._shoes = nullptr;
            addItem(_item);
        }
        });
    button3->addChild(closeButton3);


    // ��Ʒ
    auto button4 = Button::create("Bag/item_slot.png");
    button4->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y - borderHeight / 2 + 30));
    button4->addClickEventListener([=](Ref* sender) {
        // ���������Ч
        cocos2d::AudioEngine::play2d("music/click.mp3");
        });
    _characterBackground->addChild(button4);
    auto label4 = Label::createWithTTF("Accessories", "fonts/arial.ttf", 12);
    label4->setPosition(Vec2(20, -6));
    button4->addChild(label4);

    // ��ȡ��ҵ���Ʒͼ�����õ���Ʒ��
    if (player._accessories != nullptr)
    {
        // ��ȡ��Ʒͼ������
        auto accessoriesImage = player._accessories->image;
        accessoriesImage->retain(); // ��֤ͼ����󲻱�����
        accessoriesImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (accessoriesImage != nullptr)
        {
            accessoriesImage->setPosition(Vec2(button4->getContentSize().width / 2, button4->getContentSize().height / 2));
            button4->addChild(accessoriesImage);  // ��ͼ����ӵ���Ʒ����ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton4 = Button::create("Bag/close_button.png");
    closeButton4->setPosition(Vec2(0, button4->getContentSize().height)); // ���Ͻ�λ��
    closeButton4->addClickEventListener([=](Ref* sender) {
        cocos2d::AudioEngine::play2d("music/click.mp3");
        if (player._accessories != nullptr)
        {
            // ��ɫ����Ϊ��
            player.setElementType(NONE);
            auto _item = dynamic_cast<item*>(player._accessories);
            player._accessories = nullptr;
            addItem(_item);
        }
        });
    button4->addChild(closeButton4);
}

// ���ƽ�ɫ���UI
void BagManager::createCharacterPanelUI()
{
    // ���ý�ɫ��屳��
    _characterBackground = Sprite::create("Bag/character_background.png");
    float characterBackground_x = _bagBackground->getPositionX() + _bagBackground->getContentSize().width / 2 + _characterBackground->getContentSize().width / 2;
    float characterBackground_y = _bagBackground->getPositionY() + _bagBackground->getContentSize().height / 2 - _characterBackground->getContentSize().height / 2;
    _characterBackground->setPosition(Vec2(characterBackground_x, characterBackground_y));
    _bagPanel->addChild(_characterBackground, -1);

    // ������ɫ������
    auto characterTitleLabel = Label::createWithTTF("MY CHARACTER", "fonts/Bebas.ttf", 32);
    characterTitleLabel->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height - 20));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    characterTitleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _characterBackground->addChild(characterTitleLabel);

    // ���Ʊ߿�
    float borderWidth = _characterBackground->getContentSize().width / 2;
    float borderHeight = _characterBackground->getContentSize().height / 2;

    Vec2 borderPosition = Vec2(borderWidth, borderHeight);

    auto drawNode = DrawNode::create();
    _characterBackground->addChild(drawNode);

    drawNode->drawRect(
        Vec2(borderPosition.x - borderWidth / 2, borderPosition.y - borderHeight / 2),
        Vec2(borderPosition.x + borderWidth / 2, borderPosition.y + borderHeight / 2),
        Color4F(1.0f, 1.0f, 1.0f, 1.0f)
    );

    // ����ɫͼ������ڱ߿���
    player.mySprite->setVisible(true); // ����Ϊ�ɼ�
    player.mySprite->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height / 2)); // �����ڱ߿�����
    if (player.mySprite->getParent() != nullptr)
    { // ����и��ڵ㣬���ȱ����ӽڵ㣬�ٴӸ��ڵ��Ƴ�
        player.mySprite->retain();
        player.mySprite->removeFromParent();
    }
    _characterBackground->addChild(player.mySprite);
}

// ��ʾ��ɫ��Ϣ
void BagManager::showCharacterInfo()
{
    //��ʾ��ɫ�����ԡ�HP��MP
    // ����
    string PlayerElementType;
    switch (player.elementType)
    {
    case 0:
        PlayerElementType = "None";
        break;
    case 1:
        PlayerElementType = "Fire";
        break;
    case 2:
        PlayerElementType = "Grass";
        break;
    case 3:
        PlayerElementType = "Ice";
        break;
    case 4:
        PlayerElementType = "Rock";
        break;
    }
    string player_elementType = "ElementType: " + PlayerElementType;
    auto elementTypeLabel = Label::createWithTTF(player_elementType, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    elementTypeLabel->setAnchorPoint(Vec2(0, 0.5));
    elementTypeLabel->setPosition(Vec2(200, 320));
    _characterBackground->addChild(elementTypeLabel);
    // HP
    string player_HP = "HP: " + to_string(player.current_hp);
    auto characterHP = Label::createWithTTF(player_HP, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterHP->setAnchorPoint(Vec2(0, 0.5));
    characterHP->setPosition(Vec2(1, 320));
    _characterBackground->addChild(characterHP);
    // �ȼ�
    string player_level = "level: " + to_string(player.level);
    auto characterLevel = Label::createWithTTF(player_level, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterLevel->setAnchorPoint(Vec2(0, 0.5));
    characterLevel->setPosition(Vec2(1, 300));
    _characterBackground->addChild(characterLevel);

    // ��ʾ��ɫ�Ĺ����������������ٶ�
    // ������
    string player_attack = "Attack: " + to_string(player.atk);
    auto characterAttack = Label::createWithTTF(player_attack, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterAttack->setAnchorPoint(Vec2(0, 0.5));
    characterAttack->setPosition(Vec2(80, 320));
    _characterBackground->addChild(characterAttack);
    // ������
    string player_defense = "Defense: " + to_string(player.def);
    auto characterDefense = Label::createWithTTF(player_defense, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterDefense->setAnchorPoint(Vec2(0, 0.5));
    characterDefense->setPosition(Vec2(80, 300));
    _characterBackground->addChild(characterDefense);

    // �ٶ�
    string player_speed = "Speed: " + to_string(player.speed);
    auto characterSpeed = Label::createWithTTF(player_speed, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterSpeed->setAnchorPoint(Vec2(0, 0.5));
    characterSpeed->setPosition(Vec2(200, 300));
    _characterBackground->addChild(characterSpeed);
}

// �����Ʒ���¼�
void BagManager::slot_click(Button* slot, int row, int col)
{
    // ���������Ч
    cocos2d::AudioEngine::play2d("music/click.mp3"); 

    // �������ʱ����Ƿ�����Ʒ
    if (items[row * 5 + col] != NULL)
    {
        // ����Ʒ��Ϣ���
        auto itemInfoBackground = Sprite::create("Bag/item_info_background.png");
        float itemInfoBackground_x = slot->getPosition().x + itemInfoBackground->getContentSize().width / 2 + slot->getContentSize().width / 2;
        float itemInfoBackground_y = slot->getPosition().y - itemInfoBackground->getContentSize().height / 2 + slot->getContentSize().height / 2;
        itemInfoBackground->setPosition(Vec2(itemInfoBackground_x, itemInfoBackground_y)); // �����������ڸ����Ա�
        _bagBackground->addChild(itemInfoBackground, 10);

        // �����رհ�ť������ť��
        auto closeButton = Button::create("Bag/close_button.png");
        closeButton->setPosition(Vec2(itemInfoBackground->getContentSize().width, itemInfoBackground->getContentSize().height)); // ���Ͻ�λ��
        closeButton->addClickEventListener([=](Ref* sender) {
            // �������ťʱ�Ƴ� itemInfoBackground
            itemInfoBackground->removeFromParent();  // �Ӹ��ڵ��Ƴ�
            cocos2d::AudioEngine::play2d("music/click.mp3");
            });

        // ���رհ�ť��ӵ�������
        itemInfoBackground->addChild(closeButton);

        // ��ȡ��Ʒ����
        string itemName = items[row * 5 + col]->getName();
        string itemDescription = items[row * 5 + col]->getDescription();

        // ��������ʾ��Ʒ���ֵ� Label
        auto itemNameLabel = Label::createWithSystemFont(itemName, "Arial", 24);
        // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
        itemNameLabel->setTextColor(Color4B(255, 215, 0, 255)); // Color4B�ĵ��ĸ�������͸����
        itemNameLabel->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 10));  // �����ڱ����Ϸ�
        itemInfoBackground->addChild(itemNameLabel);

        // ��������ʾ��Ʒ������ Label
        auto itemDescriptionLabel = Label::createWithSystemFont(itemDescription, "Arial", 16);
        // ����ê��
        itemDescriptionLabel->setAnchorPoint(Vec2(0, 1));
        // �����ı������Ϊ��Ʒ��Ϣ�����Ŀ�ȣ������ʵ������߾ࣩ
        float maxWidth = itemInfoBackground->getContentSize().width - 10;  // �������ұ߾�
        // ��������Ⱥ͸߶�
        itemDescriptionLabel->setDimensions(maxWidth, 0);
        itemDescriptionLabel->setPosition(Vec2(10, itemInfoBackground->getContentSize().height - 30));  // �����ڱ����Ϸ�
        itemInfoBackground->addChild(itemDescriptionLabel);

        // ����ʹ����Ʒ��ť
        auto useButton = Button::create("Bag/use_button.png");
        useButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 150));
        useButton->addClickEventListener([=](Ref* sender) {
            if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col]))
            {
                // װ������Ʒ
                if (equipItem(row * 5 + col))
                    itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }
            else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col]))
            {
                auto consumption=dynamic_cast<consumable*>(items[row * 5 + col]);
                if (player.current_hp + consumption->add_HP <= player.hp)
                    player.current_hp += consumption->add_HP;
                else
                    player.current_hp = player.hp;
                dynamic_cast<item*>(items[row * 5 + col]);
                // ������Ч
                cocos2d::AudioEngine::play2d("music/eat.mp3");

                // ��������Ʒ
                discardItems(row * 5 + col);
                itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }
            }); // ���������¼�
        itemInfoBackground->addChild(useButton);

        // ������Ʒ������Ϊ��ť��Ӳ�ͬ������
        if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col])) // ��Ʒ��װ����
        {
            auto itemEquipLabel = Label::createWithSystemFont("equip", "Arial", 16); // ��ť����ʾ����װ��
            itemEquipLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ����λ��
            useButton->addChild(itemEquipLabel);
        }
        else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col])) // ��Ʒ������Ʒ��
        {
            auto itemConsumeLabel = Label::createWithSystemFont("consume", "Arial", 16); // ��ť����ʾ��������
            itemConsumeLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ����λ��
            useButton->addChild(itemConsumeLabel);
        }

        // ����������Ʒ��ť
        auto dicardButton = Button::create("Bag/use_button.png");
        dicardButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 180));
        dicardButton->addClickEventListener([=](Ref* sender) {
            // ��������Ʒ
            discardItems(row * 5 + col);
            cocos2d::AudioEngine::play2d("music/item.mp3");
            itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }); // ���������¼�
        itemInfoBackground->addChild(dicardButton);
        // Ϊ��ť�������
        auto itemDiscardLabel = Label::createWithSystemFont("discard", "Arial", 16); // ��ť����ʾ���Ƕ���
        itemDiscardLabel->setPosition(Vec2(dicardButton->getContentSize().width / 2, dicardButton->getContentSize().height / 2)); // ����λ��
        dicardButton->addChild(itemDiscardLabel);

        // ����װ��ϵͳ
        // ��������װ����ť
        equipment* equipmentNeedsUpgraded = nullptr;
        // ֻ��װ���������ࡢ�����ࡢЬ����ſ�������
        if ((equipmentNeedsUpgraded = dynamic_cast<weapon*>(items[row * 5 + col])) != nullptr ||
            (equipmentNeedsUpgraded = dynamic_cast<armor*>(items[row * 5 + col])) != nullptr ||
            (equipmentNeedsUpgraded = dynamic_cast<shoes*>(items[row * 5 + col])) != nullptr)
        {
            // ���ð�ť��λ��
            auto upgradeButton = Button::create("Bag/use_button.png");
            upgradeButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 210));
            upgradeButton->addClickEventListener([=](Ref* sender) {
                if (player.coins >= equipmentNeedsUpgraded->equipment_cost && equipmentNeedsUpgraded->equipment_level < equipmentNeedsUpgraded->equipment_levelMax)
                {
                    // ��ɫ���������
                    player.coins -= equipmentNeedsUpgraded->equipment_cost;
                    // ������ʾ�������
                    showcoins();
                    // ����������������ֵ����������
                    equipmentNeedsUpgraded->increase_attribute *= 2;
                    equipmentNeedsUpgraded->equipment_level++;
                    equipmentNeedsUpgraded->equipment_cost *= 2;
                    equipmentNeedsUpgraded->updateDescription();
                    itemInfoBackground->removeFromParent();
                    slot_click(slot, row, col);
                    // ����������Ч
                    cocos2d::AudioEngine::play2d("music/upgrade.mp3");
                }
                else
                    cocos2d::AudioEngine::play2d("music/lock.mp3");
                });
            itemInfoBackground->addChild(upgradeButton);
            // Ϊ��ť�������
            auto equipmentUpgraddeLabel = Label::createWithSystemFont("upgrade", "Arial", 16); 
            equipmentUpgraddeLabel->setPosition(Vec2(upgradeButton->getContentSize().width / 2, upgradeButton->getContentSize().height / 2)); // ����λ��
            upgradeButton->addChild(equipmentUpgraddeLabel);
        }
    }
}

// ����Ʒ��ӵ�����
void BagManager::addItem(item* it)
{
    if (it == nullptr || it->image == nullptr)
        return; // ��Ч��Ʒ���˳�����
    if (items_num < 40) // ����û����ʱ�ſ��������Ʒ
    {
        int location = 0;
        // �ҵ��յ���Ʒ��
        for (int i = 0; i < 40; i++)
            if (items[i] == NULL)
            {
                location = i;
                break;
            }
        items[location] = it; // ������Ʒ��
        it->image->retain(); // ��֤��Ʒͼ�����������
        if (_isBagOpen)
            updateBagUI();
        items_num++; // ��Ʒ������1
        // �����Ʒ��Ч
        cocos2d::AudioEngine::play2d("music/item.mp3");
    }
    else
        cocos2d::AudioEngine::play2d("music/lock.mp3");
}

// ����Ʒ�ӱ����ж���
void BagManager::discardItems(int index)
{
    // ȷ����Ʒ����
    if (items[index] != nullptr)
    {
        // �Ƴ���Ʒ��ͼ�񣨴��丸�ڵ��Ƴ���
        items[index]->image->removeFromParent();
        // �����Ʒ����
        delete items[index];  // ɾ����Ʒ����
        items[index] = nullptr; // ��ո�λ��
        // ������Ʒ����
        items_num--;
        // �������UI�Ѿ���ʾ��ˢ��UI
        if (_isBagOpen)
            updateBagUI();
    }
}

// �������ڵ���Ʒװ������ɫ����
bool BagManager::equipItem(int index)
{
    bool flag = true;
    if (items[index] != nullptr)
    {
        if (auto weaponItem = dynamic_cast<weapon*>(items[index])) // ��Ʒ��������
        {
            if (player._weapon == nullptr)
            {
                // ���½�ɫ����ָ��
                player._weapon = weaponItem;
                // ���ӽ�ɫ������
                player.atk += player._weapon->increase_attribute;
                // ���ӽ�ɫ������
                player.criticalChance += player._weapon->increase_criticalChance;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        else if (auto armorItem = dynamic_cast<armor*>(items[index])) // ��Ʒ�ǻ�����
        {
            if (player._armor == nullptr)
            {
                // ���½�ɫ����ָ��
                player._armor = armorItem;
                // ���ӽ�ɫ�ķ���ֵ
                player.def += player._armor->increase_attribute;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        else if (auto shoesItem = dynamic_cast<shoes*>(items[index])) // ��Ʒ��Ь����
        {
            if (player._shoes == nullptr)
            {
                // ���½�ɫЬ��ָ��
                player._shoes = shoesItem;
                // ���ӽ�ɫ���ٶ�
                player.speed += player._shoes->increase_attribute;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        else if (auto accessoriesItem = dynamic_cast<accessories*>(items[index])) // ��Ʒ����Ʒ��
        {
            if (player._accessories == nullptr)
            {
                // ���½�ɫ��Ʒָ��
                player._accessories = accessoriesItem;
                // �ı��ɫ������
                player.setElementType(player._accessories->setPlayerElementType);
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
            else
            {
                flag = false;
                cocos2d::AudioEngine::play2d("music/lock.mp3");
            }
        }
        cocos2d::AudioEngine::play2d("music/equip.mp3");
    }
    return flag;
}

// ��������(type:1����/0֧��)
void BagManager::taskUnlock(const bool type, task* newTask){
    if (type)
        myMainlineTask.push_back(newTask);
    else
        myLineQuest.push_back(newTask);

}