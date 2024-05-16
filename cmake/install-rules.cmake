if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/echidna-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

set(package echidna)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install targets
install(
    TARGETS echidna_echidna
    EXPORT echidnaTargets
    RUNTIME COMPONENT echidna_Runtime
    LIBRARY COMPONENT echidna_Runtime
    NAMELINK_COMPONENT echidna_Development
    ARCHIVE COMPONENT echidna_Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(IMPORTED_RUNTIME_ARTIFACTS wgpu)


# Write package file for installations
write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    echidna_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(echidna_INSTALL_CMAKEDIR)

# Install config file to the install directory
install(
    FILES cmake/install-config.cmake
    DESTINATION "${echidna_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT echidna_Development
)

# Install ConfigVersion file
install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${echidna_INSTALL_CMAKEDIR}"
    COMPONENT echidna_Development
)

# Install export 'echidnaTargets.cmake'
install(
    EXPORT echidnaTargets
    NAMESPACE echidna::
    DESTINATION "${echidna_INSTALL_CMAKEDIR}"
    COMPONENT echidna_Development
)

# Include CPack
if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()