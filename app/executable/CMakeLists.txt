if (NOT DEFINED GT_APPLICATION_MODE)
    set(GT_APPLICATION_MODE console)
endif()

if(GT_APPLICATION_MODE STREQUAL "console")
    add_subdirectory(console)
else()
    #add_subdirectory(console)
endif()
