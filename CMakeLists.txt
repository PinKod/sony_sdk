cmake_minimum_required(VERSION 3.10)
project(CameraSDK_Project LANGUAGES C CXX)

# Set compiler flags
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG -Wall -Werror -Wextra -pedantic \
#     -Wno-unused-parameter \
#     -Wno-unused-variable \
#     -Wno-unknown-pragmas \
#     -Wno-error=unknown-pragmas \
#     -Wno-error=unused-variable")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -fpermissive -Wall -Werror -Wextra -pedantic \
#     -Wno-unused-parameter \
#     -Wno-unused-variable \
#     -Wno-unknown-pragmas \
#     -Wno-error=unknown-pragmas \
#     -Wno-error=unused-variable")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g -Wall -Werror -Wextra -pedantic \
    -Wno-unused-parameter \
    -Wno-unused-variable \
    -Wno-unknown-pragmas \
    -Wno-error=unknown-pragmas \
    -Wno-error=unused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -g -fpermissive -Wall -Werror -Wextra -pedantic \
    -Wno-unused-parameter \
    -Wno-unused-variable \
    -Wno-unknown-pragmas \
    -Wno-error=unknown-pragmas \
    -Wno-error=unused-variable")    

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set RPATH to handle shared libraries in the same directory
set(CMAKE_BUILD_RPATH "$ORIGIN")

# Copy external libraries to build directory
add_custom_target(copy_libs ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/external/crsdk ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/external/crsdk/CrAdapter ${CMAKE_BINARY_DIR}/bin
    COMMENT "Copying external libraries..."
)


file(GLOB WRAPPER_SOURCES "c++_wrapper/*.cpp")
file(GLOB CLASS_METHODS_SOURCES "classes_methods/*.cpp")
# Wrapper library
add_library(wrapper SHARED 
    ${WRAPPER_SOURCES}
    ${CLASS_METHODS_SOURCES}
)
target_include_directories(wrapper PRIVATE ${CMAKE_SOURCE_DIR}/c++_wrapper)
target_include_directories(wrapper PRIVATE ${CMAKE_SOURCE_DIR}/classes_methods)
target_link_directories(wrapper PRIVATE ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(wrapper PRIVATE
    Cr_Core
    Cr_PTP_IP
    Cr_PTP_USB
    monitor_protocol
    monitor_protocol_pf
    ssh2
    usb-1.0
)
add_dependencies(wrapper copy_libs)


file(GLOB UTILS_SOURCES "utils/*.cpp")
# Utility library
add_library(utils SHARED
    ${UTILS_SOURCES}
)
target_include_directories(utils PRIVATE ${CMAKE_SOURCE_DIR}/utils) 
target_link_directories(utils PRIVATE ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(utils PRIVATE
    Cr_Core
    Cr_PTP_IP
    Cr_PTP_USB
    monitor_protocol
    monitor_protocol_pf
    ssh2
    usb-1.0
)
add_dependencies(utils copy_libs)



file(GLOB APP_SOURCES "app/*.c")
# Sample application
add_executable(sample_app 
    ${APP_SOURCES}
)

target_include_directories(sample_app PRIVATE ${CMAKE_SOURCE_DIR}/c++_wrapper ${CMAKE_SOURCE_DIR}/classes_methods ${CMAKE_SOURCE_DIR}/utils)
add_dependencies(sample_app copy_libs)
target_link_libraries(sample_app PRIVATE 
    wrapper 
    utils
)