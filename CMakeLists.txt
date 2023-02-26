
cmake_minimum_required (VERSION 3.16)

project (AnyTypeErasure)

set(application_name "any-demo")

set(SOURCE_FILES
    Json.cpp
    main.cpp
    )

add_executable (${application_name} ${SOURCE_FILES})
