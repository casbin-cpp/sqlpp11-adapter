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