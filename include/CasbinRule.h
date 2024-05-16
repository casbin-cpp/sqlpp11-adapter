#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>



struct CasbinRuleTable {
    struct Id {
        struct _alias_t {
            static constexpr const char _literal[] = "id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::must_not_insert, sqlpp::must_not_update>;
    };

    struct Ptype {
        struct _alias_t {
            static constexpr const char _literal[] = "ptype";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V0 {
        struct _alias_t {
            static constexpr const char _literal[] = "v0";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V1 {
        struct _alias_t {
            static constexpr const char _literal[] = "v1";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V2 {
        struct _alias_t {
            static constexpr const char _literal[] = "v2";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V3 {
        struct _alias_t {
            static constexpr const char _literal[] = "v3";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V4 {
        struct _alias_t {
            static constexpr const char _literal[] = "v4";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    struct V5 {
        struct _alias_t {
            static constexpr const char _literal[] = "v5";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        };
        using _traits = sqlpp::make_traits<sqlpp::varchar>;
    };

    using _traits = sqlpp::make_traits<sqlpp::integer>;
    using _columns_t = sqlpp::column_list<Id, Ptype, V0, V1, V2, V3, V4, V5>;

    static constexpr const char _literal[] = "casbin_rule";
    using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
};