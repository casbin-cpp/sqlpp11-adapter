#include "sqlpp11_adapter.h"
#include <gtest/gtest.h>

TEST(Sqlpp11AdapterTest, LoadPolicy) {
    // ����һ�� Sqlpp11Adapter ʵ��
    Sqlpp11Adapter adapter;

    // ����һ��ģ��
    auto model = std::make_shared<Model>();
    model->loadModel("path_to_your_model.conf");

    // ���ز���
    adapter.LoadPolicy(model);

    // �������Ƿ��Ѽ���
    // �⽫ȡ������Ĳ��Ժ�ģ��
    // ������һ��ʾ��
    ASSERT_TRUE(model->hasPolicy("p", "p", std::vector<std::string>{"alice", "data1", "read"}));
}

TEST(Sqlpp11AdapterTest, SavePolicy) {
    // ����һ�� Sqlpp11Adapter ʵ��
    Sqlpp11Adapter adapter;

    // ����һ��ģ��
    auto model = std::make_shared<Model>();
    model->loadModel("path_to_your_model.conf");

    // ���һЩ����
    model->addPolicy("p", "p", std::vector<std::string>{"alice", "data1", "write"});

    // �������
    adapter.SavePolicy(*model);

    // ���¼��ز����Լ�����Ƿ��ѱ���
    model->clearPolicy();
    adapter.LoadPolicy(model);

    // ����²����Ƿ����
    ASSERT_TRUE(model->hasPolicy("p", "p", std::vector<std::string>{"alice", "data1", "write"}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
