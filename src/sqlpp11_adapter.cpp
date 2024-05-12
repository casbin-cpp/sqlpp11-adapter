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
#include <string>
#include <casbin/casbin.h>
#include "casbin/persist/adapter.h"
#include "casbin/util/util.h"
#include "sqlpp11/mysql/mysql.h"
#include "sqlpp11/sqlpp11.h"
#include "sql_casbin.h"
#include <mysql.h> // MySQL's own driver, needs to be loaded manually
#include "sql_casbin.h"
#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)

using namespace casbin;
using namespace sqlpp;
using namespace std;
using namespace mysql;
using namespace SQLPP11;
static const std::string relative_path = STRINGIFY(modelpath);
class Sqlpp11Adapter  {
public:
    sqlpp::mysql::connection db;
    sqlpp::mysql::connection connect(string host, unsigned int port, string user, string password, string database) {
        sqlpp::mysql::connection_config config;
        // Database address
        config.host = host;
        // Port number
        config.port = port;
        // Database login account
        config.user = user;
        // Database login password
        config.password = password;
        // The database to operate
        config.database = database;
        config.debug = true;
        sqlpp::mysql::connection db(config);
        return db;
    }

    void NewAdapter(string host,unsigned int port, string user, string password, string database) {
        db=connect(host,port,user,password,database);
        // If the database does not exist, create the database and table
        createTable();
    }
    // Load policy from database
    void LoadPolicy(const std::shared_ptr<Model>& model) {
        SQLPP11::CasbinRule casbin_rule{};

        try {
            for (const auto& row : db(sqlpp::select(all_of(casbin_rule)).from(casbin_rule).unconditionally())) {
                std::string ptype = row.ptype.is_null() ? "" : row.ptype.value();
                std::string v0 = row.v0.is_null() ? "" : row.v0.value();
                std::string v1 = row.v1.is_null() ? "" : row.v1.value();
                std::string v2 = row.v2.is_null() ? "" : row.v2.value();
                std::string v3 = row.v3.is_null() ? "" : row.v3.value();
                std::string v4 = row.v4.is_null() ? "" : row.v4.value();
                std::string v5 = row.v5.is_null() ? "" : row.v5.value();

                std::string lineText = ptype;
                if (!row.v0.is_null() && !v0.empty()) lineText += ", " + v0;
                if (!row.v1.is_null() && !v1.empty()) lineText += ", " + v1;
                if (!row.v2.is_null() && !v2.empty()) lineText += ", " + v2;
                if (!row.v3.is_null() && !v3.empty()) lineText += ", " + v3;
                if (!row.v4.is_null() && !v4.empty()) lineText += ", " + v4;
                if (!row.v5.is_null() && !v5.empty()) lineText += ", " + v5;
                casbin::LoadPolicyLine(lineText, model);
            }
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error loading policy: " << e.what() << std::endl;
        }
    }

    void SavePolicy(const std::shared_ptr<Model>& model) {
        SQLPP11::CasbinRule casbin_rule{};
        std::string v0;
        std::string v1;
        std::string v2;
        std::string v3;
        std::string v4;
        std::string v5;

        PoliciesValues p_policies = model->GetPolicy("p", "p");
        for (const auto& policy : p_policies) {
            if (policy.size() > 0 && !policy[0].empty()) v0 = policy[0];
            if (policy.size() > 1 && !policy[1].empty()) v1 = policy[1];
            if (policy.size() > 2 && !policy[2].empty()) v2 = policy[2];
            if (policy.size() > 3 && !policy[3].empty()) v3 = policy[3];
            if (policy.size() > 4 && !policy[4].empty()) v4 = policy[4];
            if (policy.size() > 5 && !policy[5].empty()) v5 = policy[5];

            // Query whether the data already exists in the database
            auto rows = db(select(all_of(casbin_rule)).from(casbin_rule).where(casbin_rule.ptype == "p" and casbin_rule.v0 == v0 and casbin_rule.v1 == v1 and casbin_rule.v2 == v2 and casbin_rule.v3 == v3 and casbin_rule.v4 == v4 and casbin_rule.v5 == v5));
            if (rows.empty()) {
                // If it does not exist, insert it
                db(insert_into(casbin_rule).set(casbin_rule.ptype = "p", casbin_rule.v0 = v0, casbin_rule.v1 = v1, casbin_rule.v2 = v2, casbin_rule.v3 = v3, casbin_rule.v4 = v4, casbin_rule.v5 = v5));
            }
        }

        PoliciesValues g_policies = model->GetPolicy("g", "g");
        for (const auto& policy : g_policies) {
            if (policy.size() > 0 && !policy[0].empty()) v0 = policy[0];
            if (policy.size() > 1 && !policy[1].empty()) v1 = policy[1];
            if (policy.size() > 2 && !policy[2].empty()) v2 = policy[2];
            if (policy.size() > 3 && !policy[3].empty()) v3 = policy[3];
            if (policy.size() > 4 && !policy[4].empty()) v4 = policy[4];
            if (policy.size() > 5 && !policy[5].empty()) v5 = policy[5];

            // Query whether the data already exists in the database
            auto rows = db(select(all_of(casbin_rule)).from(casbin_rule).where(casbin_rule.ptype == "g" and casbin_rule.v0 == v0 and casbin_rule.v1 == v1 and casbin_rule.v2 == v2 and casbin_rule.v3 == v3 and casbin_rule.v4 == v4 and casbin_rule.v5 == v5));
            if (rows.empty()) {
                // If it does not exist, insert it
                db(insert_into(casbin_rule).set(casbin_rule.ptype = "g", casbin_rule.v0 = v0, casbin_rule.v1 = v1, casbin_rule.v2 = v2, casbin_rule.v3 = v3, casbin_rule.v4 = v4, casbin_rule.v5 = v5));
            }
        }
    }

    //if the table or database does not exist, create it
    void createTable() {
        try {
            db.execute("CREATE DATABASE IF NOT EXISTS casbin");
            db.execute("USE casbin");
            db.execute("CREATE TABLE IF NOT EXISTS casbin_rule "
                       " (id INT AUTO_INCREMENT PRIMARY KEY, "
                       "ptype VARCHAR(255), v0 VARCHAR(255), v1 VARCHAR(255), "
                       "v2 VARCHAR(255), v3 VARCHAR(255), v4 VARCHAR(255), v5 VARCHAR(255))");
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error creating database or table: " << e.what() << std::endl;
        }
    }

    void dropTable() {
        try {
            db.execute("DROP TABLE IF EXISTS casbin_rule" );
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error dropping table: " << e.what() << std::endl;
        }
    }

    //empty function
    void AddPolicy() {

    };

    void RemovePolicy() {
    }

    void RemoveFilteredPolicy() {
    }
};