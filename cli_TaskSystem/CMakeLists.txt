# 添加可执行文件和源文件
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/static/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# 添加头文件
set(Json_Include ${CMAKE_CURRENT_SOURCE_DIR}/../includes)
set(SQLite3MC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../sqlite3mc)

# 创建可执行文件
add_executable(TaskSystem ${SOURCES})

# 拷贝 DLL（注意目标名统一）
file(GLOB PLUGIN_DLLS "${CMAKE_CURRENT_SOURCE_DIR}/plugins/*.dll")

add_custom_command(TARGET TaskSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${PLUGIN_DLLS}
            $<TARGET_FILE_DIR:TaskSystem>
    COMMENT "Copying plugin DLLs (*.dll) to output directory"
)

# 添加头文件路径
target_include_directories(TaskSystem
    PUBLIC
    ${Json_Include}
    ${SQLite3MC_DIR}/include
)

# 如果你还用到了 .lib 文件
target_link_libraries(TaskSystem 
    ${SQLite3MC_DIR}/dll/sqlite3mc_icu_x64.lib
)
