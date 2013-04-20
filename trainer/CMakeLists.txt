cmake_minimum_required(VERSION 2.8)

project( trainer )
find_package( OpenCV REQUIRED )

find_package( Boost 1.52 COMPONENTS filesystem program_options system REQUIRED )
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)
set(CMAKE_INCLUDE_PATH ${CMAKE_LIBRARY_PATH} /opt/local/include)

add_executable(
  trainer
  trainer.cpp
  feature_extractor.cpp
  vocabtree.cpp
)

add_executable(
  test_suite
  test_suite/test_suite.cpp
  feature_extractor.cpp
  vocabtree.cpp
)

target_link_libraries( trainer ${OpenCV_LIBS} ${Boost_LIBRARIES})

target_link_libraries( test_suite ${OpenCV_LIBS} ${Boost_LIBRARIES})