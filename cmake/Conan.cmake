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
    https://bincrafters.jfrog.io/artifactory/api/conan/public-conan)

  conan_cmake_run(
    REQUIRES
    ${CONAN_EXTRA_REQUIRES}
    catch2/2.13.10
    docopt.cpp/0.6.3
    fmt/10.0.0
    spdlog/1.12.0
#   sol2/3.2.3-luajit
    sol2/3.3.0-exhaustive
    tsl-sparse-map/0.6.2
    simdjson/3.2.1
    rapidcsv/8.77
    vincentlaucsb-csv-parser/2.1.3
    roaring/1.3.0
    jfalcou-eve/v2023.02.15
    cppcodec/0.2
    cpr/1.10.4
    boost/1.82.0
    unordered_dense/4.0.1
#    reckless/3.0.3  # temporarily removing logging until ARM issue is figured out
    benchmark/1.8.2
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing)
endmacro()
