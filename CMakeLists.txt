PROJECT(screenshottest)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
set(Boost_USE_MULTITHREADED OFF)

find_package(Boost COMPONENTS system filesystem REQUIRED)

set(XF_SRCS
  firefoxcontrol.cpp
  screenshottest.cpp
)

ADD_EXECUTABLE(XF ${XF_SRCS})

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
target_link_libraries(XF ${Boost_LIBRARIES})
