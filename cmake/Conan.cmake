macro(run_conan)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)

  conan_add_remote(
    NAME
    bincrafters
    URL
    https://api.bintray.com/conan/bincrafters/public-conan)

  conan_cmake_run(
    REQUIRES
    ${CONAN_EXTRA_REQUIRES}
    catch2/2.13.8
    docopt.cpp/0.6.3
    fmt/8.0.1
    spdlog/1.9.2
    luajit/2.0.5
    sol2/3.2.3
    tsl-sparse-map/0.6.2
    simdjson/1.0.2
    roaring/0.4.0
    jfalcou-eve/v2021.10.0
    cppcodec/0.2
    cpr/1.6.2
    reckless/3.0.3
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing)
endmacro()
