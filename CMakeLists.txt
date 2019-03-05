cmake_minimum_required(VERSION 3.2)

project(allocator VERSION 1.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(allocator main.cpp)
add_executable(alloc_test alloc_test.cpp)
add_executable(stack_test stack_test.cpp)

set_target_properties(allocator alloc_test stack_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

################################################################################

install(TARGETS allocator RUNTIME DESTINATION bin)

################################################################################

enable_testing()

add_test(alloc_test alloc_test)
add_test(stack_test stack_test)

################################################################################

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_NAME allocator)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Anton Sochnev <an.sochnev@yandex.ru>")
set(CPACK_DEBIAN_PACKAGE_SECTION "homework")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION 
"some description should be here
 And here."
)
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})

include(CPack)

