
#FIND_PACKAGE( Boost 1.34 )
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#	add_executable(fitoxml fitoxml.cpp)
#	target_link_libraries(fitoxml fi)    
#else()
#	message(STATUS "Boost not found, won't build fitoxml")
#endif()

include_directories(. ${PROJECT_SOURCE_DIR}/src)

add_executable(fitoxml fitoxml.cpp argument_helper.cpp)
target_link_libraries(fitoxml fi)    

add_executable(printtables printtables.cpp argument_helper.cpp)
target_link_libraries(printtables fi)    
