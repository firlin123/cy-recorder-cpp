cmake_minimum_required(VERSION 3.12...3.27 FATAL_ERROR)

PROJECT(cy_recorder_cpp
    VERSION 0.0.1
)

option(USE_SUBMODULES "Use source in local submodules instead of system libraries" ON)

set(CY_RECORDER_SOURCES src/cy_recorder.cpp src/to_json.cpp)
add_executable(cy_recorder ${CY_RECORDER_SOURCES})

if(USE_SUBMODULES)
    add_subdirectory(lib/socket.io-client-cpp)
    if(NOT TARGET sioclient)
        message(FATAL_ERROR "sioclient not found")
    endif()
    target_link_libraries(cy_recorder PRIVATE sioclient)

    set(MODULE_INCLUDE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/lib/rapidjson/include
    )
else()
    find_package(sioclient CONFIG REQUIRED)
    find_package(RapidJSON CONFIG REQUIRED)
    target_link_libraries(cy_recorder PRIVATE sioclient::sioclient)
    target_include_directories(cy_recorder PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
endif()

target_include_directories(cy_recorder PRIVATE ${MODULE_INCLUDE_DIRS})

find_package(OpenSSL)

if(OpenSSL_FOUND)
    add_executable(cy_recorder_tls ${CY_RECORDER_SOURCES})
    target_include_directories(cy_recorder_tls PRIVATE ${MODULE_INCLUDE_DIRS})
    if(USE_SUBMODULES)
        if(NOT TARGET sioclient_tls)
            message(FATAL_ERROR "sioclient_tls not found")
        endif()
        target_link_libraries(cy_recorder_tls PRIVATE sioclient_tls)
    else()
        target_link_libraries(cy_recorder_tls PRIVATE sioclient::sioclient_tls)
        target_include_directories(cy_recorder_tls PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
    endif()
    target_link_libraries(cy_recorder_tls PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

install(TARGETS cy_recorder DESTINATION /usr/bin)
if(OpenSSL_FOUND)
    install(TARGETS cy_recorder_tls DESTINATION /usr/bin)
endif()