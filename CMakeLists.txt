# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(ADS)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
								      # и для создания исполняемого проекта в отдельные функции

add_subdirectory(lib_easy_example)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example
add_subdirectory(lib_point)           # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_point
add_subdirectory(lib_point3d)         # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_point3d
add_subdirectory(lib_circle)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_circle
add_subdirectory(lib_sphere)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_sphere
add_subdirectory(lib_tvector)         # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_tvector
add_subdirectory(lib_mathvector)      # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_mathvector
add_subdirectory(lib_matrix)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_matrix
add_subdirectory(lib_trianglematrix)  # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_trianglematrix
add_subdirectory(lib_stack)           # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_stack
add_subdirectory(lib_queue)           # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_queue
add_subdirectory(lib_priority_queue)  # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_priority_queue
add_subdirectory(lib_node)            # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_node
add_subdirectory(lib_list)            # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_list
add_subdirectory(Algorithms)          # подключаем дополнительный CMakeLists.txt из подкаталога с именем Algorithms
add_subdirectory(main)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


