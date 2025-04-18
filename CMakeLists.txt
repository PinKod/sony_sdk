cmake_minimum_required(VERSION 3.10)
project(CameraSDK_Project LANGUAGES C CXX)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(CRSDK_LIB_DIR "${CMAKE_SOURCE_DIR}/external/x86_64/crsdk")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(CRSDK_LIB_DIR "${CMAKE_SOURCE_DIR}/external/arm64/crsdk")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsigned-char -g -Wall -Werror -Wextra -pedantic \
    -Wno-unused-parameter \
    -Wno-unused-variable \
    -Wno-unknown-pragmas \
    -Wno-error=unknown-pragmas \
    -Wno-error=unused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char -std=c++17 -g -fpermissive -Wall -Werror -Wextra -pedantic \
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
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CRSDK_LIB_DIR} ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CRSDK_LIB_DIR}/CrAdapter ${CMAKE_BINARY_DIR}/bin
    COMMENT "Copying ${CMAKE_SYSTEM_PROCESSOR} libraries..."
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


file(GLOB LIB_C_SOURCES "lib_c/*.c")
# Utility library
add_library(lib_c SHARED
    ${LIB_C_SOURCES}
)
target_include_directories(lib_c PRIVATE ${CMAKE_SOURCE_DIR}/lib_c) 
target_link_directories(lib_c PRIVATE ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(lib_c PRIVATE
    Cr_Core
    Cr_PTP_IP
    Cr_PTP_USB
    monitor_protocol
    monitor_protocol_pf
    ssh2
    usb-1.0
)
add_dependencies(lib_c copy_libs)



file(GLOB APP_SOURCES "app/*.c")
# Sample application
add_executable(sample_app 
    ${APP_SOURCES}
)

target_include_directories(sample_app PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
)

add_dependencies(sample_app copy_libs)
target_link_libraries(sample_app PRIVATE 
    wrapper 
    utils
)




file(GLOB LIVE_IMAGE_SOURCES "live_image_service/*.c")
# Live Image Service executable
add_executable(live_image_service 
    ${LIVE_IMAGE_SOURCES}
)

target_include_directories(live_image_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(live_image_service copy_libs)
target_link_libraries(live_image_service PRIVATE 
    wrapper 
    utils
    lib_c
)





file(GLOB ISO_SERVICE "iso_service/*.c")
# Live Image Service executable
add_executable(iso_service 
    ${ISO_SERVICE}
)

target_include_directories(iso_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(iso_service copy_libs)
target_link_libraries(iso_service PRIVATE 
    wrapper 
    utils
    lib_c
)





file(GLOB APERTURE_SERVICE "aperture_service/*.c")
# Live Image Service executable
add_executable(aperture_service 
    ${APERTURE_SERVICE}
)

target_include_directories(aperture_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(aperture_service copy_libs)
target_link_libraries(aperture_service PRIVATE 
    wrapper 
    utils
    lib_c
)





file(GLOB WHITE_BALANCE_SERVICE "white_balance_service/*.c")
# Live Image Service executable
add_executable(white_balance_service 
    ${WHITE_BALANCE_SERVICE}
)

target_include_directories(white_balance_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(white_balance_service copy_libs)
target_link_libraries(white_balance_service PRIVATE 
    wrapper 
    utils
    lib_c
)





file(GLOB FOCUS_MODE_SERVICE "focus_mode_service/*.c")
# Live Image Service executable
add_executable(focus_mode_service 
    ${FOCUS_MODE_SERVICE}
)

target_include_directories(focus_mode_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(focus_mode_service copy_libs)
target_link_libraries(focus_mode_service PRIVATE 
    wrapper 
    utils
    lib_c
)









file(GLOB JPEG_QUALITY_SERVICE "jpeg_quality_service/*.c")
# Live Image Service executable
add_executable(jpeg_quality_service 
    ${JPEG_QUALITY_SERVICE}
)

target_include_directories(jpeg_quality_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(jpeg_quality_service copy_libs)
target_link_libraries(jpeg_quality_service PRIVATE 
    wrapper 
    utils
    lib_c
)







file(GLOB FILE_TYPE_SERVICE "file_type_service/*.c")
# Live Image Service executable
add_executable(file_type_service 
    ${FILE_TYPE_SERVICE}
)

target_include_directories(file_type_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(file_type_service copy_libs)
target_link_libraries(file_type_service PRIVATE 
    wrapper 
    utils
    lib_c
)






file(GLOB EXSPOSURE_CORRECTION_SERVICE "exsposure_correction_service/*.c")
# Live Image Service executable
add_executable(exsposure_correction_service 
    ${EXSPOSURE_CORRECTION_SERVICE}
)

target_include_directories(exsposure_correction_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(exsposure_correction_service copy_libs)
target_link_libraries(exsposure_correction_service PRIVATE 
    wrapper 
    utils
    lib_c
)






file(GLOB SHUTTER_SPEED_SERVICE "shutter_speed_service/*.c")
# Live Image Service executable
add_executable(shutter_speed_service 
    ${SHUTTER_SPEED_SERVICE}
)

target_include_directories(shutter_speed_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(shutter_speed_service copy_libs)
target_link_libraries(shutter_speed_service PRIVATE 
    wrapper 
    utils
    lib_c
)







file(GLOB CAMERA_SERVICE "camera_service/*.c")
# Live Image Service executable
add_executable(camera_service 
    ${CAMERA_SERVICE}
)

target_include_directories(camera_service PRIVATE 
    ${CMAKE_SOURCE_DIR}/c++_wrapper 
    ${CMAKE_SOURCE_DIR}/classes_methods 
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/lib_c
)
add_dependencies(camera_service copy_libs)
target_link_libraries(camera_service PRIVATE 
    wrapper 
    utils
    lib_c
)