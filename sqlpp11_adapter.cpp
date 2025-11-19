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

namespace casbin {

namespace {
const std::string kDefaultTableName = "casbin_rule";
}

Sqlpp11Adapter::Sqlpp11Adapter(const std::string& host, const std::string& user,
                               const std::string& password, const std::string& database,
                               unsigned int port)
    : table_name_(kDefaultTableName) {
    config_.host = host;
    config_.user = user;
    config_.password = password;
    config_.database = database;
    config_.port = port;
    config_.debug = false;
    
    db_ = std::make_shared<sqlpp::mysql::connection>(config_);
}

void Sqlpp11Adapter::LoadPolicy(const std::shared_ptr<Model>& model) {
    CasbinRuleTable casbin_rule;

    try {
        auto result = (*db_)(sqlpp::select(all_of(casbin_rule)).from(casbin_rule).unconditionally());
        for (const auto& row : result) {
            LoadPolicyLine(row, model);
        }
    } catch (const sqlpp::exception& e) {
        std::cerr << "Error loading policy: " << e.what() << std::endl;
        throw;
    }
}

template<typename Row>
void Sqlpp11Adapter::LoadPolicyLine(const Row& row,
                                    const std::shared_ptr<Model>& model) {
    std::vector<std::string> tokens;
    tokens.push_back(row.ptype);
    
    if (!row.v0.is_null()) tokens.push_back(row.v0.value());
    if (!row.v1.is_null()) tokens.push_back(row.v1.value());
    if (!row.v2.is_null()) tokens.push_back(row.v2.value());
    if (!row.v3.is_null()) tokens.push_back(row.v3.value());
    if (!row.v4.is_null()) tokens.push_back(row.v4.value());
    if (!row.v5.is_null()) tokens.push_back(row.v5.value());

    if (tokens.size() < 2) {
        return;  // Need at least ptype and one value
    }

    std::string key = tokens[0];
    std::vector<std::string> sec_tokens(tokens.begin() + 1, tokens.end());
    
    if (model->HasSection("p") && model->HasAssertion("p", key)) {
        model->AddPolicy("p", key, sec_tokens);
    } else if (model->HasSection("g") && model->HasAssertion("g", key)) {
        model->AddPolicy("g", key, sec_tokens);
    }
}

void Sqlpp11Adapter::SavePolicy(Model& model) {
    try {
        DropTable();
        CreateTable();

        CasbinRuleTable casbin_rule;

        // Helper lambda to insert a single policy rule
        auto insertRule = [this, &casbin_rule](const std::string& ptype, 
                                                const std::vector<std::string>& rule) {
            auto insert = sqlpp::insert_into(casbin_rule).set(
                casbin_rule.ptype = ptype,
                casbin_rule.v0 = rule.size() > 0 ? sqlpp::value(rule[0]) : sqlpp::null,
                casbin_rule.v1 = rule.size() > 1 ? sqlpp::value(rule[1]) : sqlpp::null,
                casbin_rule.v2 = rule.size() > 2 ? sqlpp::value(rule[2]) : sqlpp::null,
                casbin_rule.v3 = rule.size() > 3 ? sqlpp::value(rule[3]) : sqlpp::null,
                casbin_rule.v4 = rule.size() > 4 ? sqlpp::value(rule[4]) : sqlpp::null,
                casbin_rule.v5 = rule.size() > 5 ? sqlpp::value(rule[5]) : sqlpp::null
            );
            (*db_)(insert);
        };

        // Save policy rules
        for (const auto& [ptype, ast] : model.m["p"].assertion_map) {
            for (const auto& rule : ast->policy) {
                insertRule(ptype, rule);
            }
        }

        // Save grouping rules
        for (const auto& [ptype, ast] : model.m["g"].assertion_map) {
            for (const auto& rule : ast->policy) {
                insertRule(ptype, rule);
            }
        }
    } catch (const sqlpp::exception& e) {
        std::cerr << "Error saving policy: " << e.what() << std::endl;
        throw;
    }
}

void Sqlpp11Adapter::CreateTable() {
    try {
        db_->execute("CREATE TABLE IF NOT EXISTS " + table_name_ +
                    " (id INT AUTO_INCREMENT PRIMARY KEY, "
                    "ptype VARCHAR(100) NOT NULL, "
                    "v0 VARCHAR(100), "
                    "v1 VARCHAR(100), "
                    "v2 VARCHAR(100), "
                    "v3 VARCHAR(100), "
                    "v4 VARCHAR(100), "
                    "v5 VARCHAR(100))");
    } catch (const sqlpp::exception& e) {
        std::cerr << "Error creating table: " << e.what() << std::endl;
        throw;
    }
}

void Sqlpp11Adapter::DropTable() {
    try {
        db_->execute("DROP TABLE IF EXISTS " + table_name_);
    } catch (const sqlpp::exception& e) {
        std::cerr << "Error dropping table: " << e.what() << std::endl;
        throw;
    }
}

} // namespace casbin