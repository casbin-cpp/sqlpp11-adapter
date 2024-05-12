
#include <iostream>
#include <string>
#include "sqlpp11/sqlpp11.h"
#include "sqlpp11_adapter.cpp"'
#include "casbin/casbin.h"
#include "casbin/model/model.h"
using namespace sqlpp;
using namespace std;
using namespace sqlpp::mysql;
using namespace casbin;


int main()

{
    // std::shared_ptr<mysql::connection> db = connect_database();
    Sqlpp11Adapter  ss;
    std::shared_ptr<casbin::Model> m = casbin::Model::NewModel();
    m->LoadModel("/model.conf");

   // m->AddPolicy("p", "p", { "alice", "data1", "write" });
    
    ss.LoadPolicy(m);

    PoliciesValues p_policies = m->GetPolicy("p", "p"); int p = p_policies.size();
    std::cout << "p policies:" << std::endl;
    for (const auto& policy : p_policies) {
        for (const auto& field : policy) {
            std::cout << field << " ";
            
        }
        std::cout<<policy.size()<< std::endl;
    }
    std::cout << p << std::endl;
    bool s;
   

   
   std::vector<std::string> f = { "alice", "data1", "write" };s=  m->HasPolicy("p","p", f);
   std::cout << f.size() << std::endl;
   std::cout<<s<<std::endl;
    
  return 0;
}