
include(FetchContent)

FetchContent_Declare(sqlpp11
        GIT_REPOSITORY  https://github.com/rbock/sqlpp11
        GIT_TAG         origin/main
)
# Configure the project here as needed
set(BUILD_MYSQL_CONNECTOR ON)
# set(BUILD_MARIADB_CONNECTOR ON)
# set(BUILD_POSTGRESQL_CONNECTOR ON)
# set(BUILD_SQLITE3_CONNECTOR ON)
# set(BUILD_SQLCIPHER_CONNECTOR ON)

# set(USE_SYSTEM_DATE ON)

FetchContent_MakeAvailable(sqlpp11)