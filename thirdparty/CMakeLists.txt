# Try to find system-installed GTest first (for nix builds)
find_package(GTest CONFIG QUIET)

if(GTest_FOUND)
  # Make GTest_FOUND visible to other CMakeLists
  set(GTest_FOUND TRUE CACHE BOOL "GTest was found" FORCE)
endif()

if(NOT GTest_FOUND)
  # Fall back to FetchContent for non-nix builds
  include(FetchContent)

  set(INSTALL_GTEST OFF CACHE BOOL "Install GTest - no need since embedded project")

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()
