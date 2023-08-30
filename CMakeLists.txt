cmake_minimum_required(VERSION 3.12)

project(poly_sample_plan)
set(Pangolin_INCLUDE_DIRS,"/home/zhiqiangding/pangolin")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
add_library(test SHARED test.cc test.h)
# 添加可执行文件
add_executable(poly_sample_plan poly_sample_plan.cc)
target_link_libraries(poly_sample_plan ${Pangolin_LIBRARIES})
add_executable(main main.cc test)

