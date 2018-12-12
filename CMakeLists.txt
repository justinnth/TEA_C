cmake_minimum_required(VERSION 3.13)
project(TEA C)

set(CMAKE_C_STANDARD 99)

add_library(. SHARED redBlackTree.c redBlackTree.h)
add_library(redBlackStatic STATIC redBlackTree.c redBlackTree.h)
set_target_properties(. PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        )
set_target_properties(redBlackStatic PROPERTIES
        OUTPUT_NAME ntree
        )

install(
        TARGETS . redBlackStatic
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

install(
        FILES redBlackTree.h
        DESTINATION include
)

add_executable(TEA main.c redBlackTree.c redBlackTree.h)
add_dependencies(TEA .)
target_link_libraries(TEA .)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES "~$;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)