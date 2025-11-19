# Copyright 2024 The casbin Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.19)

project(sqlpp11-adapter VERSION 1.0.0 LANGUAGES CXX)

# Project-wide setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(casbin REQUIRED)

# Add library target
add_library(sqlpp11_adapter STATIC
    sqlpp11_adapter.cpp
)

target_include_directories(sqlpp11_adapter
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(sqlpp11_adapter
    PUBLIC
        casbin
)

# Add test executable
add_executable(test
    test.cpp
    sqlpp11_adapter.cpp
)

target_include_directories(test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(test
    PRIVATE
        casbin
)

# Installation rules
install(TARGETS sqlpp11_adapter
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include/sqlpp11_adapter
    FILES_MATCHING PATTERN "*.h"
)
