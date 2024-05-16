#ifndef CASBIN_CPP_SQLPP11_ADAPTER_H
#define CASBIN_CPP_SQLPP11_ADAPTER_H


#include <memory>
#include <string>
#include <vector>

#include "casbin/persist/adapter.h"
#include "casbin/util/util.h"
#include "sqlpp11/mysql/mysql.h"
#include "sqlpp11/sqlpp11.h"

namespace casbin {

struct CasbinRule;
struct Adapter;
class Model;

class Sqlpp11Adapter : public Adapter {
public:
    Sqlpp11Adapter();
    void LoadPolicy(const std::shared_ptr<Model>& model)
        ;
    void SavePolicy(Model& model);
    std::string GetFullTableName() const;
    void createTable();
    void dropTable();

private:
    sqlpp::mysql::connection_config config;
    sqlpp::mysql::connection db;
    CasbinRule savePolicyLine(const std::string& ptype, const std::vector<std::string>& rule);
    void LoadPolicyLine(CasbinRule line, const std::shared_ptr<Model>& model);
};

} // namespace casbin


#endif // CASBIN_CPP_SQLPP11_ADAPTER_H
