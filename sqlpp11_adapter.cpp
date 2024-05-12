
#include "sqlpp11_adapter.h"
#include <string>
#include <casbin/casbin.h>
#include "casbin/persist/adapter.h"
#include "casbin/util/util.h"
#include "sqlpp11/mysql/mysql.h"
#include "sqlpp11/sqlpp11.h"
#include "CasbinRule.h"
namespace casbin {


struct Adapter {
    std::string driverName;
    std::string dataSourceName;
    std::string dataSourceAlias;
    bool dbSpecified;
    std::string tablePrefix;
    std::string tableName;
    sqlpp::mysql::connection db;

};
const std::string defaultTableName = "casbin_rule";

class Sqlpp11Adapter : public Casbin::Adapter {
public:
    sql::connection_config config;
    sql::connection db;

    Sqlpp11Adapter() : db(config) {
        config.host = "localhost";
        config.user = "root";
        config.password = "";
        config.database = "casbin";
        config.debug = true;
    }

    // Load policy from database
    void LoadPolicy(const std::shared_ptr<Model>& model) {
        CasbinRuleTable casbin_rule;

        try {
            auto result = db(sqlpp::select(all_of(casbin_rule)).from(casbin_rule).unconditionally());
            for (const auto& row : result) {
                LoadPolicyLine(row, model);
            }
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error loading policy: " << e.what() << std::endl;
        }
    }

    // Load policy line
    void LoadPolicyLine(const CasbinRuleTable::Row& row, const std::shared_ptr<Model>& model) {
        std::string lineText = row.ptype;
        if (!row.v0.is_null()) lineText += ", " + row.v0.value();
        if (!row.v1.is_null()) lineText += ", " + row.v1.value();
        if (!row.v2.is_null()) lineText += ", " + row.v2.value();
        if (!row.v3.is_null()) lineText += ", " + row.v3.value();
        if (!row.v4.is_null()) lineText += ", " + row.v4.value();
        if (!row.v5.is_null()) lineText += ", " + row.v5.value();

        casbin::LoadPolicyLine(lineText, model);
    }

    // Save policy to database
    void SavePolicy(Model& model) {
        try {
            dropTable();
            createTable();

            CasbinRuleTable casbin_rule;
            std::vector<sqlpp::insert_list_item_t<CasbinRuleTable>> lines;

            for (const auto& [ptype, ast] : model.m["p"].assertion_map) {
                for (const auto& rule : ast->policy) {
                    lines.push_back(insertPolicyLine(casbin_rule, ptype, rule));
                }
            }

            for (const auto& [ptype, ast] : model.m["g"].assertion_map) {
                for (const auto& rule : ast->policy) {
                    lines.push_back(insertPolicyLine(casbin_rule, ptype, rule));
                }
            }

            for (const auto& line : lines) {
                db(line);
            }
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error saving policy: " << e.what() << std::endl;
        }
    }

    // Save policy line
    sqlpp::insert_list_item_t<CasbinRuleTable> insertPolicyLine(CasbinRuleTable& table, const std::string& ptype, const std::vector<std::string>& rule) {
        return sqlpp::insert_into(table).set(
            table.ptype = ptype,
            table.v0 = rule.size() > 0 ? rule[0] : "",
            table.v1 = rule.size() > 1 ? rule[1] : "",
            table.v2 = rule.size() > 2 ? rule[2] : "",
            table.v3 = rule.size() > 3 ? rule[3] : "",
            table.v4 = rule.size() > 4 ? rule[4] : "",
            table.v5 = rule.size() > 5 ? rule[5] : ""
        );
    }

    // Get full table name
    std::string GetFullTableName() const {
        return tablePrefix + (tableName.empty() ? defaultTableName : tableName);
    }

    void createTable() {
        try {
            db.execute("CREATE TABLE IF NOT EXISTS " + GetFullTableName() +
                " (id INT AUTO_INCREMENT PRIMARY KEY, "
                "ptype VARCHAR(255), v0 VARCHAR(255), v1 VARCHAR(255), "
                "v2 VARCHAR(255), v3 VARCHAR(255), v4 VARCHAR(255), v5 VARCHAR(255))");
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error creating table: " << e.what() << std::endl;
        }
    }

    void dropTable() {
        try {
            db.execute("DROP TABLE IF EXISTS " + GetFullTableName());
        }
        catch (const sqlpp::exception& e) {
            std::cerr << "Error dropping table: " << e.what() << std::endl;
        }
    }
};

} // namespace casbin