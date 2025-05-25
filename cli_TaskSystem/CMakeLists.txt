
# 添加可执行文件和源文件CMAKE_CURRENT_SOURCE_DIR表示CMakeLists.txt所在的目录
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/static/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
#添加头文件（根据实际的安装目录修改，linux上）
set(Json_Include ${CMAKE_CURRENT_SOURCE_DIR}/../includes)
set(SQLite3MC_DIR "F:/CS_learn/CPP_learn/TaskSystem/sqlite3mc")
# 创建可执行文件
add_executable(TaskSystem ${SOURCES})
# 添加 nlohmann 头文件路径
target_include_directories(TaskSystem
    PUBLIC
    ${Json_Include}
    ${SQLite3MC_DIR}/include
)
target_link_libraries(TaskSystem 
    ${SQLite3MC_DIR}/dll/sqlite3mc_icu_x64.lib
)


