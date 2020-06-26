cmake_minimum_required(VERSION 3.15)

project(teoria)

file(GLOB SOURCES "src/*")

add_executable(teoria ${SOURCES})
