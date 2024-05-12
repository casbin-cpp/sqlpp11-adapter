#include "sqlpp11_adapter.h"
#include <gtest/gtest.h>

TEST(Sqlpp11AdapterTest, LoadPolicy) {
    // 创建一个 Sqlpp11Adapter 实例
    Sqlpp11Adapter adapter;

    // 创建一个模型
    auto model = std::make_shared<Model>();
    model->loadModel("path_to_your_model.conf");

    // 加载策略
    adapter.LoadPolicy(model);

    // 检查策略是否已加载
    // 这将取决于你的策略和模型
    // 以下是一个示例
    ASSERT_TRUE(model->hasPolicy("p", "p", std::vector<std::string>{"alice", "data1", "read"}));
}

TEST(Sqlpp11AdapterTest, SavePolicy) {
    // 创建一个 Sqlpp11Adapter 实例
    Sqlpp11Adapter adapter;

    // 创建一个模型
    auto model = std::make_shared<Model>();
    model->loadModel("path_to_your_model.conf");

    // 添加一些策略
    model->addPolicy("p", "p", std::vector<std::string>{"alice", "data1", "write"});

    // 保存策略
    adapter.SavePolicy(*model);

    // 重新加载策略以检查它是否已保存
    model->clearPolicy();
    adapter.LoadPolicy(model);

    // 检查新策略是否存在
    ASSERT_TRUE(model->hasPolicy("p", "p", std::vector<std::string>{"alice", "data1", "write"}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
