cmake_minimum_required(VERSION 3.22)
project(c_dazuoye_v1_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(c_dazuoye_v1_0 main.c
        cards.c
        enemy.c
        level_config.c
        log.c
        math.c
        relic.c
        marco_struct_def_fucdeclaration.h)

target_link_libraries(c_dazuoye_v1_0 m)
