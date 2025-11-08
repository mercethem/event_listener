# Requires CMake version 3.20 or higher
cmake_minimum_required(VERSION 3.20)

# ----- VCPKG (Static Linking) Configuration -----
# vcpkg toolchain file must be set BEFORE project() call!
set(CMAKE_TOOLCHAIN_FILE "C:/Users/merce/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "vcpkg toolchain file")
# Use static .lib files (removes DLL dependency)
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")

# Set project name
project(event_listener LANGUAGES CXX)

# Require C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Runtime library setting (Use static runtime - compatible with vcpkg)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # Prevent LNK4098 warning
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
endif()

# ----- Find Required Libraries -----
# For <thread>
find_package(Threads REQUIRED)

# Find libcurl installed via vcpkg (This will also find zlib)
# Try CONFIG mode first (vcpkg modern), otherwise use MODULE mode
find_package(CURL CONFIG QUIET)
if(NOT CURL_FOUND)
    find_package(CURL MODULE QUIET)
endif()

# If CURL not found, try to find it manually from vcpkg
if(NOT CURL_FOUND)
    set(VCPKG_ROOT "C:/Users/merce/vcpkg")
    set(VCPKG_INSTALLED_DIR "${VCPKG_ROOT}/installed/x64-windows-static")
    
    # Find CURL include directory from vcpkg
    if(EXISTS "${VCPKG_INSTALLED_DIR}/include")
        set(CURL_INCLUDE_DIRS "${VCPKG_INSTALLED_DIR}/include")
        if(EXISTS "${VCPKG_INSTALLED_DIR}/include/curl/curl.h")
            set(CURL_FOUND TRUE)
            message(STATUS "CURL found manually from vcpkg: ${CURL_INCLUDE_DIRS}")
        endif()
    endif()
endif()

if(NOT CURL_FOUND)
    message("")
    message("==========================================")
    message("WARNING: CURL library not found!")
    message("==========================================")
    message("")
    message("Email features will not work!")
    message("")
    message("To install CURL, run these commands in PowerShell:")
    message("  cd C:\\Users\\merce\\vcpkg")
    message("  .\\vcpkg install curl:x64-windows-static")
    message("")
    message("After installation:")
    message("  1. In CLion: File > Settings > Build > CMake > Delete CMake Cache")
    message("  2. Or delete the cmake-build-debug folder")
    message("  3. Rebuild the project")
    message("")
    message("==========================================")
    message(FATAL_ERROR "CURL not found, build stopped")
endif()

# Create an executable named 'event_listener'
add_executable(event_listener
        main.cpp
        src/core/ApplicationBuilder.cpp
        src/config/ConfigLoader.cpp
        src/config/Configuration.cpp
        src/logging/ConsoleColor.cpp
        src/logging/ConsoleLogger.cpp
        src/input/DirectoryInputHandler.cpp
        src/email/EmailContentBuilder.cpp
        src/email/EmailFormatter.cpp
        src/input/EmailInputHandler.cpp
        src/email/EmailNotificationListener.cpp
        src/email/EmailSender.cpp
        src/events/EventDispatcher.cpp
        src/input/ExtensionInputHandler.cpp
        src/filesystem/FileExtensionFilter.cpp
        src/filesystem/FileSystemHelper.cpp
        src/filesystem/FileSystemWatcher.cpp
        src/input/ProviderConverter.cpp
        src/filesystem/StringConverter.cpp
        src/utils/TimeFormatter.cpp
        config.ini
)

# Tell compiler where to find header (.h) files
target_include_directories(event_listener PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
# Add CURL include directory
if(CURL_FOUND)
    if(CURL_INCLUDE_DIRS)
        target_include_directories(event_listener PUBLIC ${CURL_INCLUDE_DIRS})
    endif()
endif()

# Link libraries to our project
target_link_libraries(event_listener PUBLIC
        Threads::Threads # For <thread>
)
# Link CURL
if(CURL_FOUND)
    if(TARGET CURL::libcurl)
        target_link_libraries(event_listener PUBLIC CURL::libcurl)
    elseif(CURL_LIBRARIES)
        target_link_libraries(event_listener PUBLIC ${CURL_LIBRARIES})
    else()
        # Find lib file manually from vcpkg
        set(VCPKG_INSTALLED_DIR "C:/Users/merce/vcpkg/installed/x64-windows-static")
        if(EXISTS "${VCPKG_INSTALLED_DIR}/lib/libcurl.lib")
            target_link_libraries(event_listener PUBLIC "${VCPKG_INSTALLED_DIR}/lib/libcurl.lib")
        elseif(EXISTS "${VCPKG_INSTALLED_DIR}/lib/curl.lib")
            target_link_libraries(event_listener PUBLIC "${VCPKG_INSTALLED_DIR}/lib/curl.lib")
        endif()
    endif()
    
    # CURL's Windows dependencies
    target_link_libraries(event_listener PUBLIC
        ws2_32      # Windows Sockets API
        crypt32     # SChannel (for SSL/TLS)
        winmm       # Windows Multimedia (for some CURL features)
        iphlpapi    # IP Helper API (for if_nametoindex)
        secur32     # Security Support Provider Interface (for SSPI)
    )
    
    # Find and add zlib (for compression)
    find_package(ZLIB QUIET)
    if(ZLIB_FOUND)
        if(TARGET ZLIB::ZLIB)
            target_link_libraries(event_listener PUBLIC ZLIB::ZLIB)
        elseif(ZLIB_LIBRARIES)
            target_link_libraries(event_listener PUBLIC ${ZLIB_LIBRARIES})
        endif()
    else()
        # Find zlib manually from vcpkg
        if(EXISTS "${VCPKG_INSTALLED_DIR}/lib/zlib.lib")
            target_link_libraries(event_listener PUBLIC "${VCPKG_INSTALLED_DIR}/lib/zlib.lib")
        elseif(EXISTS "${VCPKG_INSTALLED_DIR}/lib/zlibd.lib")
            target_link_libraries(event_listener PUBLIC "${VCPKG_INSTALLED_DIR}/lib/zlibd.lib")
        endif()
    endif()
endif()