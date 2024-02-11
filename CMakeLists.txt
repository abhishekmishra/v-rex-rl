cmake_minimum_required ( VERSION 3.9 )

project ( v-rex-rl C )

set ( PRG_SOURCES
    main.c
)

add_executable( ${PROJECT_NAME} ${PRG_SOURCES} )

# raylib
find_package( raylib CONFIG REQUIRED )
target_link_libraries( ${PROJECT_NAME} PUBLIC raylib )

# raygui
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYGUI_INCLUDE_DIRS})

# !!!!NOTE/WARNING!!!
# The coll package is placed ahead of json-c such that arraylist.h from coll is used.
# TODO: coll package should be fixed to use another header file name.
find_package(coll CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC coll::coll)

find_package(json-c CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC json-c::json-c)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC CURL::libcurl)

# To find and use libarchive, as the vcpkg build does not have cmake config
# See https://github.com/microsoft/vcpkg/issues/8839#issuecomment-558066466
# for additional lookup to ZLIB
find_package(ZLIB REQUIRED)
find_package(lz4 REQUIRED)
find_package(BZip2 REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(LibLZMA REQUIRED)
find_path(LIBARCHIVE_INCLUDE_DIR archive.h)
find_library(LIBARCHIVE_LIBRARY archive)
include_directories(${LIBARCHIVE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBARCHIVE_LIBRARY} lz4::lz4 BZip2::BZip2 LibXml2::LibXml2 LibLZMA::LibLZMA ZLIB::ZLIB)
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

# clibdocker docker API
find_package(clibdocker CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC clibdocker::clibdocker)
