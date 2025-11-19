# Sqlpp11 Adapter

[![CI](https://github.com/casbin-cpp/sqlpp11-adapter/actions/workflows/ci.yml/badge.svg)](https://github.com/casbin-cpp/sqlpp11-adapter/actions/workflows/ci.yml)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Sqlpp11 Adapter is a [sqlpp11](https://github.com/rbock/sqlpp11) adapter for [Casbin](https://github.com/casbin/casbin-cpp). With this library, Casbin can load policy from MySQL database or save policy to it.

## Features

- Load policy from MySQL database
- Save policy to MySQL database
- Full support for Casbin policy management
- Built on top of the powerful sqlpp11 library

## Installation

### Requirements

- C++17 or higher
- CMake 3.19 or higher
- [Casbin-CPP](https://github.com/casbin/casbin-cpp)
- [sqlpp11](https://github.com/rbock/sqlpp11)
- MySQL client library

### Building from source

```bash
git clone https://github.com/casbin-cpp/sqlpp11-adapter
cd sqlpp11-adapter
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage

### Basic Example

```cpp
#include "include/sqlpp11_adapter.h"
#include <casbin/casbin.h>

int main() {
    // Create adapter with MySQL connection parameters
    auto adapter = std::make_shared<casbin::Sqlpp11Adapter>(
        "localhost",  // host
        "root",       // user
        "password",   // password
        "casbin",     // database
        3306          // port (default: 3306)
    );
    
    // Create the table (if it doesn't exist)
    adapter->CreateTable();
    
    // Create enforcer with model file and adapter
    auto enforcer = std::make_shared<casbin::Enforcer>(
        "path/to/model.conf", 
        adapter
    );
    
    // Load policy from database
    enforcer->LoadPolicy();
    
    // Add policies
    enforcer->AddPolicy("alice", "data1", "read");
    enforcer->AddPolicy("bob", "data2", "write");
    
    // Save policy to database
    enforcer->SavePolicy();
    
    // Check permissions
    if (enforcer->Enforce("alice", "data1", "read")) {
        // alice can read data1
    }
    
    return 0;
}
```

### Model Configuration

Create a model configuration file (e.g., `rbac_model.conf`):

```ini
[request_definition]
r = sub, obj, act

[policy_definition]
p = sub, obj, act

[role_definition]
g = _, _

[policy_effect]
e = some(where (p.eft == allow))

[matchers]
m = g(r.sub, p.sub) && r.obj == p.obj && r.act == p.act
```

## API Reference

### Constructor

```cpp
Sqlpp11Adapter(const std::string& host, 
               const std::string& user,
               const std::string& password, 
               const std::string& database,
               unsigned int port = 3306);
```

Creates a new adapter instance with the specified MySQL connection parameters.

### Methods

#### LoadPolicy

```cpp
void LoadPolicy(const std::shared_ptr<Model>& model) override;
```

Loads all policy rules from the database.

#### SavePolicy

```cpp
void SavePolicy(Model& model) override;
```

Saves all policy rules to the database (replaces existing policies).

#### CreateTable

```cpp
void CreateTable();
```

Creates the `casbin_rule` table if it doesn't exist.

#### DropTable

```cpp
void DropTable();
```

Drops the `casbin_rule` table if it exists.

## Database Schema

The adapter uses a table named `casbin_rule` with the following schema:

```sql
CREATE TABLE casbin_rule (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ptype VARCHAR(100) NOT NULL,
    v0 VARCHAR(100),
    v1 VARCHAR(100),
    v2 VARCHAR(100),
    v3 VARCHAR(100),
    v4 VARCHAR(100),
    v5 VARCHAR(100)
);
```

## Testing

To run the tests:

```bash
cd build
./test
```

Make sure you have a MySQL server running and accessible with the connection parameters used in the test.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Casbin](https://casbin.org/) - An authorization library that supports access control models
- [sqlpp11](https://github.com/rbock/sqlpp11) - A type safe SQL template library for C++