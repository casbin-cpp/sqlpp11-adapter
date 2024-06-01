#  Copyright 2021 The casbin Authors. All Rights Reserved.
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

#sqlpp11
include(FetchContent)

FetchContent_Declare(sqlpp11
  GIT_REPOSITORY https://github.com/rbock/sqlpp11
  GIT_TAG        origin/main
)

# Configure the project here as needed
set(BUILD_MYSQL_CONNECTOR ON)
# set(BUILD_MARIADB_CONNECTOR ON)
# set(BUILD_POSTGRESQL_CONNECTOR ON)
# set(BUILD_SQLITE3_CONNECTOR ON)
# set(BUILD_SQLCIPHER_CONNECTOR ON)

# set(USE_SYSTEM_DATE ON)

FetchContent_MakeAvailable(sqlpp11)

#casbin
include(FetchContent)

FetchContent_Declare(
        casbin
        GIT_REPOSITORY https://github.com/casbin/casbin-cpp.git
        GIT_TAG v1.59.0
)

set(CASBIN_BUILD_TEST OFF)            # If you don't need to build tests for casbin
set(CASBIN_BUILD_BENCHMARK OFF)       # If you don't need to build benchmarks for casbin
set(CASBIN_BUILD_BINDINGS OFF)        # If you don't need language bindings provided by casbin
set(CASBIN_BUILD_PYTHON_BINDINGS OFF) # If you don't need python bindings provided by casbin

# Making casbin and its targets accessible to our project
FetchContent_MakeAvailable(casbin)

FetchContent_GetProperties(casbin)

# If casbin wasn't populated, then manually populate it
if(NOT casbin_POPULATED)
    FetchContent_Populate(casbin)
    add_subdirectory(${casbin_SOURCE_DIR} ${casbin_BINARY_DIR})
endif()


#gtest
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)

# Populating manually, if not done automatically
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


#json
include(FetchContent)

set(JSON_Install ON)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
  DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)

FetchContent_MakeAvailable(json)

