# Use this for installing AutobahnCpp into <prefix>/include.
cmake_minimum_required(VERSION 2.8)

project(autobahn-cpp)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wno-unused-local-typedefs -Wno-unknown-warning-option ${CMAKE_CXX_FLAGS}")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
    if ("${CMAKE_GENERATOR}" STREQUAL "Ninja")
        set(CMAKE_CXX_FLAGS "-fcolor-diagnostics ${CMAKE_CXX_FLAGS}")
    endif()
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0501)
endif()

if (MSVC)
    set (Boost_USE_MULTITHREADED TRUE)
    set (Boost_USE_STATIC_LIBS TRUE)
else ()
    set (Boost_USE_MULTITHREADED FALSE)
    set (Boost_USE_STATIC_LIBS FALSE)
endif ()

find_package(Boost REQUIRED COMPONENTS program_options system thread)
find_package(Libmsgpack REQUIRED)
#find_package(Threads REQUIRED)

if (Boost_FOUND)
    # Boost is a project wide global dependency.
    include_directories (${Boost_INCLUDE_DIRS})
    link_directories (${Boost_LIBRARY_DIRS})

    # Pretty print status
    message (STATUS "-- Include Directories")
    foreach (include_dir ${Boost_INCLUDE_DIRS})
        message (STATUS "       " ${include_dir})
    endforeach ()
    message (STATUS "-- Library Directories")
    foreach (library_dir ${Boost_LIBRARY_DIRS})
        message (STATUS "       " ${library_dir})
    endforeach ()
    message (STATUS "-- Libraries")
    foreach (boost_lib ${Boost_LIBRARIES})
        message (STATUS "       " ${boost_lib})
    endforeach ()
    message ("")
else ()
    message (FATAL_ERROR "Failed to find required dependency: boost")
endif ()

set(PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/autobahn.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/exceptions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_arguments.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_call.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_call.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_call_options.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_call_options.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_call_result.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_call_result.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_event.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_event_handler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_invocation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_invocation.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_message.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_message_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_procedure.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_publication.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_publication.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_register_request.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_register_request.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_registration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_registration.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_session.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_session.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_subscribe_request.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_subscribe_request.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_subscription.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_subscription.ipp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_unsubscribe_request.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/autobahn/wamp_unsubscribe_request.ipp)

foreach(h ${PUBLIC_HEADERS})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "include/" include "${h}")
    get_filename_component(HEADER_INCLUDE_DIRECTORY ${include} DIRECTORY)
    install(FILES ${h}
        DESTINATION ${HEADER_INCLUDE_DIRECTORY}
        COMPONENT "headers")
endforeach()

add_subdirectory(examples)
