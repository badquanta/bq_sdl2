include(ExternalProject)
find_package(Git REQUIRED)
ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/lib/doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir} CACHE INTERNAL "Path to include folder for doctest")

#######################################################################
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
ExternalProject_Add(
    bq_utils
    PREFIX ${CMAKE_BINARY_DIR}/lib/bq_utils
    GIT_REPOSITORY /home/badquanta/bq_utils++ #https://github.com/badquanta/bq_utils.git
    TIMEOUT 10
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    #CONFIGURE_COMMAND ""
    #BUILD_COMMAND ""
    #INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)
ExternalProject_Get_Property(bq_utils source_dir)
set(BQ_UTILS_INCLUDE_DIRS ${source_dir}/src CACHE INTERNAL "Path to include folder for bq_utils")
