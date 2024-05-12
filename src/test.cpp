/*
 * Copyright 2020 The casbin Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "sqlpp11_adapter.cpp"
#include <gtest/gtest.h>
#include "casbin/casbin.h"
static const std::string model_path = relative_path+"/examples/model.conf";
TEST(Sqlpp11AdapterTest, LoadPolicy) {
// Create a Sqlpp11Adapter instance
Sqlpp11Adapter adapter;
adapter.NewAdapter("127.0.0.1",3306, "root", "125463", "casbin");
// Create a model
std::shared_ptr<casbin::Model> model = casbin::Model::NewModel();
model->LoadModel("../examples/model.conf");

// Load policy
adapter.LoadPolicy(model);

// Check if policy exists
ASSERT_TRUE(model->HasPolicy("p", "p", {"alice", "data1", "write"}));
}

TEST(Sqlpp11AdapterTest, SavePolicy) {
// Create a Sqlpp11Adapter instance
Sqlpp11Adapter adapter;
adapter.NewAdapter("127.0.0.1", 3306, "root", "125463", "casbin");
// Create a model
std::shared_ptr<casbin::Model> model = casbin::Model::NewModel();
model->LoadModel("../examples/model.conf");

// Add some policies
model->AddPolicy("p", "p", {"alice", "data1", "write"});

// Save policy
adapter.SavePolicy(model);

// Reload policy to check if it has been saved
model->ClearPolicy();
adapter.LoadPolicy(model);

// Check if new policy exists
ASSERT_TRUE(model->HasPolicy("p", "p", {"alice", "data1", "write"}));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
