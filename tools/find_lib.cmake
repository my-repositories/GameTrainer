function(FIND_LIB ARG_NAME LIB_NAME)
    set(
            LIB_PATHS_TO_FIND
            "C:/Program Files (x86)/Windows Kits/*/Lib/*/*/${MY_PLATFORM}"
            "C:/Windows Kits/*/Lib/*/*/${MY_PLATFORM}"
            "C:/Program Files/Windows Kits/*/Lib/*/*/${MY_PLATFORM}"
    )

    set(LIB_FOUND_PATHS "")

    foreach(LIB_PATH_TO_FIND ${LIB_PATHS_TO_FIND})
        file(GLOB_RECURSE LIB_FILES ${LIB_PATH_TO_FIND}/${LIB_NAME})
        if (LIB_FILES)
            foreach(LIB_FILE ${LIB_FILES})
                get_filename_component(LIB_DIR ${LIB_FILE} DIRECTORY)
                set(LIB_FOUND_PATHS "${LIB_FOUND_PATHS};${LIB_DIR}")
            endforeach()
        endif()
    endforeach()

    FIND_LIBRARY(
            FOUND_LIB
            NAMES ${LIB_NAME}
            HINTS ${LIB_FOUND_PATHS}
            PATHS ${LIB_FOUND_PATHS}
    )

    set(${ARG_NAME} ${FOUND_LIB} PARENT_SCOPE)
endfunction()
