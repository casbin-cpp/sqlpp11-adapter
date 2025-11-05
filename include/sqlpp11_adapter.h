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

#ifndef CASBIN_CPP_SQLPP11_ADAPTER_H
#define CASBIN_CPP_SQLPP11_ADAPTER_H

#include <memory>
#include <string>
#include <vector>

#include "casbin/persist/adapter.h"
#include "casbin/util/util.h"
#include "sqlpp11/mysql/mysql.h"
#include "sqlpp11/sqlpp11.h"
#include "CasbinRule.h"

namespace casbin {

class Model;

class Sqlpp11Adapter : public Adapter {
public:
    Sqlpp11Adapter(const std::string& host, const std::string& user,
                   const std::string& password, const std::string& database,
                   unsigned int port = 3306);
    
    void LoadPolicy(const std::shared_ptr<Model>& model) override;
    void SavePolicy(Model& model) override;
    
    void CreateTable();
    void DropTable();

private:
    sqlpp::mysql::connection_config config_;
    std::shared_ptr<sqlpp::mysql::connection> db_;
    std::string table_name_;
    
    void LoadPolicyLine(const CasbinRuleTable::Row& row, const std::shared_ptr<Model>& model);
};

} // namespace casbin

#endif // CASBIN_CPP_SQLPP11_ADAPTER_H
