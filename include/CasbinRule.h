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

#ifndef CASBIN_CPP_CASBINRULE_H
#define CASBIN_CPP_CASBINRULE_H

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

namespace casbin {

struct CasbinRuleTable : sqlpp::table_t<CasbinRuleTable,
    struct Id,
    struct Ptype,
    struct V0,
    struct V1,
    struct V2,
    struct V3,
    struct V4,
    struct V5>
{
    struct Id {
        struct _alias_t {
            static constexpr const char _literal[] = "id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T id;
                T& operator()() { return id; }
                const T& operator()() const { return id; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
    };

    struct Ptype {
        struct _alias_t {
            static constexpr const char _literal[] = "ptype";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T ptype;
                T& operator()() { return ptype; }
                const T& operator()() const { return ptype; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V0 {
        struct _alias_t {
            static constexpr const char _literal[] = "v0";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T v0;
                T& operator()() { return v0; }
                const T& operator()() const { return v0; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };

    struct V1 {
        struct _alias_t {
            static constexpr const char _literal[] = "v1";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T v1;
                T& operator()() { return v1; }
                const T& operator()() const { return v1; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };

    struct V2 {
        struct _alias_t {
            static constexpr const char _literal[] = "v2";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T v2;
                T& operator()() { return v2; }
                const T& operator()() const { return v2; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };

    struct V3 {
        struct _alias_t {
            static constexpr const char _literal[] = "v3";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T v3;
                T& operator()() { return v3; }
                const T& operator()() const { return v3; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };

    struct V4 {
        struct _alias_t {
            static constexpr const char _literal[] = "v4";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T v4;
                T& operator()() { return v4; }
                const T& operator()() const { return v4; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };

    struct V5 {
        struct _alias_t {
            static constexpr const char _literal[] = "v5";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t {
                T v5;
                T& operator()() { return v5; }
                const T& operator()() const { return v5; }
            };
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::can_be_null>;
    };

    using _value_type = sqlpp::no_value_t;
    struct _alias_t {
        static constexpr const char _literal[] = "casbin_rule";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t {
            T casbinRule;
            T& operator()() { return casbinRule; }
            const T& operator()() const { return casbinRule; }
        };
    };
};

} // namespace casbin

#endif // CASBIN_CPP_CASBINRULE_H