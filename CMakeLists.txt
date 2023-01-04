cmake_minimum_required(VERSION 3.0.0)

project(WET2)

set(MTM_FLAGS_DEBUG "-std=c++11 -Wall")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(WET2 main23a2.cpp AVLnode.h HashTable.h HashTable.cpp Player.h Player.cpp Team.h Team.cpp worldcup23a2.h worldcup23a2.cpp wet2util.h UnionFind.h RankTree.h UnionFind.cpp)
