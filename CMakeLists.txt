cmake_minimum_required(VERSION 3.13)
project(SelfBalancingBinaryTree)

add_subdirectory(
	"${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

set(
    SOURCE_FILES
    main.cpp
    RequestHandler.cpp
)

add_executable(
    tree
    ${SOURCE_FILES}
)

add_executable(
    test
    test.cpp
)

target_link_libraries(
    test PRIVATE
    gtest gtest_main
)