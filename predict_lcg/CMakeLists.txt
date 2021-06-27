cmake_minimum_required(VERSION 3.5)


project(Predict_LCG VERSION 1.0 LANGUAGES CXX)

set(SOURCES
    hacking_lcg.cpp
    inv.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
