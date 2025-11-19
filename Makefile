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

CXX = g++
CXXFLAGS = -Wall -std=c++17 -I. -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lcasbin

TARGET = test

OBJS = sqlpp11_adapter.o test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

sqlpp11_adapter.o: sqlpp11_adapter.cpp include/sqlpp11_adapter.h include/CasbinRule.h
	$(CXX) $(CXXFLAGS) -c sqlpp11_adapter.cpp

test.o: test.cpp include/sqlpp11_adapter.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
