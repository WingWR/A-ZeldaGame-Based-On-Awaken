#include "SetMicroMapCamera.h"

bool SetMicroMapCamera::init() {

    //����С��ͼ��������ϵ��ӽǣ�

    miniMapCamera = Camera::createOrthographic(200.0f, 200.0f, 1.0f, 1000.0f);
    miniMapCamera->setPosition3D(Vec3(0, 0, 1500));  // ������������ڽϸߵ�λ��
    miniMapCamera->setDepth(-1);  // С��ͼ���������ȵ����������
    this->addChild(miniMapCamera);

    // ע���������¼�
    auto listener = EventListenerMouse::create();
    listener->onMouseScroll = [=](EventMouse* event) {
        // ��ȡ���ֵĹ�������
        float scrollY = event->getScrollY();

        // ��ȡ��ǰ�������λ��
        Vec3 cameraPosition = miniMapCamera->getPosition3D();

        // ���ݹ��ֵķ���ı��������Z��߶�
        // ���Ϲ�����Z��ֵ���ӣ��������ǰ
        // ���¹�����Z��ֵ���٣���������
        cameraPosition.z += scrollY * 10.0f;  // 10.0f�ǿ��ƹ��������ȵ�ϵ�������Ե���

        // ����������ĸ߶ȣ�Z�᷶Χ��
        cameraPosition.z = std::min(cameraPosition.z, 1800.0f);  // ���߶�
        cameraPosition.z = std::max(cameraPosition.z, 1000.0f);  // ��С�߶�

        // �����������λ��
        miniMapCamera->setPosition3D(cameraPosition);

        CCLOG("Camera Position: %f, %f, %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        };

    // ��ȡ�¼�����������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

// ���������¼����ƶ�С��ͼ�����
void  SetMicroMapCamera::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        if (currentCamera == mainCamera) {
            // �л���С��ͼ�����
            //Director::getInstance()->getRunningScene()->setCamera(miniMapCamera);
            currentCamera = miniMapCamera;
        }
    }

    if (currentCamera == miniMapCamera) {
        // ����С��ͼ��������ƶ�
        Vec3 cameraPos = miniMapCamera->getPosition3D();

        // ʹ�� WASD ������������ƶ�
        if (keyCode == EventKeyboard::KeyCode::KEY_W) {
            cameraPos.y += 10.0f;  // ����
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
            cameraPos.y -= 10.0f;  // ����
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
            cameraPos.x -= 10.0f;  // ����
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
            cameraPos.x += 10.0f;  // ����
        }

        miniMapCamera->setPosition3D(cameraPos);  // ���������λ��
    }
}

// �����ͷ��¼����л����������
void SetMicroMapCamera::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        if (currentCamera == miniMapCamera) {
            // �л����������
            //Director::getInstance()->getRunningScene()->setCamera(mainCamera);
            currentCamera = mainCamera;
        }
    }
}