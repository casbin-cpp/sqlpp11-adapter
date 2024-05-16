#  Copyright 2020 The casbin Authors. All Rights Reserved.
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
cmake_minimum_required(VERSION 3.19)

set(CMAKE_WARN_DEPRECATED ON)

#sqlpp11
project(Test VERSION 0.1 LANGUAGES CXX)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#casbin
add_executable(test )

target_link_libraries(test PRIVATE casbin)

set(test_INCLUDE_DIR ${casbin_SOURCE_DIR}/include)
target_include_directories(test PRIVATE ${myexec_INCLUDE_DIR})


target_link_libraries(test
        PRIVATE
        sqlpp11::sqlpp11
        # Corresponding targets for the connectors. These connectors need to be enabled in the the dependencies/sqlpp11 folder. These targets automatically link against sqlpp11::sqlpp11 and therefore sqlpp11::sqlpp11 doesn't need to be linked manually again
        # sqlpp11::sqlite3
        # sqlpp11::sqlcipher
        # sqlpp11::mysql
        # sqlpp11::mariadb
        # sqlpp11::postgresql
)

target_sources(test
        PRIVATE
        sqlpp11_adapter.cpp
        test.cpp
)
