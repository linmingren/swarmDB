add_library(storage STATIC
        storage.cpp
        storage.hpp
        storage_base.hpp
        )

target_link_libraries(storage)
add_dependencies(storage jsoncpp)
target_include_directories(storage PRIVATE ${JSONCPP_INCLUDE_DIRS})

add_subdirectory(test)
