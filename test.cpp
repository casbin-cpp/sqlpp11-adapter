// Copyright 2024 The casbin Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "include/sqlpp11_adapter.h"
#include <casbin/casbin.h>
#include <iostream>
#include <memory>

using namespace casbin;

void TestBasicOperations() {
    std::cout << "Testing basic adapter operations..." << std::endl;
    
    try {
        // Create adapter instance
        auto adapter = std::make_shared<Sqlpp11Adapter>(
            "localhost", "root", "", "casbin", 3306
        );
        
        // Create table
        adapter->CreateTable();
        std::cout << "Table created successfully" << std::endl;
        
        // Create enforcer
        auto enforcer = std::make_shared<Enforcer>("examples/rbac_model.conf", adapter);
        
        // Add policies
        enforcer->AddPolicy("alice", "data1", "read");
        enforcer->AddPolicy("bob", "data2", "write");
        enforcer->AddPolicy("data2_admin", "data2", "read");
        enforcer->AddPolicy("data2_admin", "data2", "write");
        
        // Add roles
        enforcer->AddGroupingPolicy("alice", "data2_admin");
        
        // Save policy to database
        enforcer->SavePolicy();
        std::cout << "Policy saved successfully" << std::endl;
        
        // Clear policy and reload from database
        enforcer->ClearPolicy();
        enforcer->LoadPolicy();
        std::cout << "Policy loaded successfully" << std::endl;
        
        // Test enforcement
        bool result1 = enforcer->Enforce("alice", "data1", "read");
        bool result2 = enforcer->Enforce("alice", "data1", "write");
        bool result3 = enforcer->Enforce("alice", "data2", "read");
        bool result4 = enforcer->Enforce("alice", "data2", "write");
        bool result5 = enforcer->Enforce("bob", "data2", "write");
        
        std::cout << "Enforcement results:" << std::endl;
        std::cout << "  alice, data1, read: " << (result1 ? "PASS" : "FAIL") << std::endl;
        std::cout << "  alice, data1, write: " << (!result2 ? "PASS (correctly denied)" : "FAIL (should be denied)") << std::endl;
        std::cout << "  alice, data2, read: " << (result3 ? "PASS" : "FAIL") << std::endl;
        std::cout << "  alice, data2, write: " << (result4 ? "PASS" : "FAIL") << std::endl;
        std::cout << "  bob, data2, write: " << (result5 ? "PASS" : "FAIL") << std::endl;
        
        if (result1 && !result2 && result3 && result4 && result5) {
            std::cout << "All tests PASSED!" << std::endl;
        } else {
            std::cerr << "Some tests FAILED!" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char** argv) {
    TestBasicOperations();
    return 0;
}
