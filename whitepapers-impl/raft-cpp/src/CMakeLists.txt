add_library(raft_core
    raft/log.cpp
)

target_include_directories(raft_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(raft_core PUBLIC cxx_std_20)

target_compile_definitions(raft_core PUBLIC RAFT_DEBUG=1)

# add_executable(test_log examples/test_log.cpp)
# target_link_libraries(test_log PRIVATE raft_core)
