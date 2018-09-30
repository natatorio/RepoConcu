cmake_minimum_required(VERSION 2.8)
project(01.Procesos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_1")
add_executable(ejemplo1 main1.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_2")
add_executable(ejemplo2 main2.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_3")
add_executable(ejemplo3 main3.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_4")
add_executable(ejemplo4 main4.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_5")
add_executable(ejemplo5 main5.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_6")
add_executable(ejemplo6 main6.cc)
