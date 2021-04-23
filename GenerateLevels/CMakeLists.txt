set(PROJECT_NAME GenerateLevels)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "EnumBitOperations.h"
    "Game.h"
    "GameCell.h"
    "GameField.h"
    "IPlayer.h"
    "Step.h"
    "Vector2.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Players
    "GreedyPlayer.h"
    "GreedyPlayer2.h"
    "InteractivePlayer.h"
    "MCTSPlayer.h"
    "MiniMaxModifiedPlayer.h"
    "MiniMaxPlayer.h"
    "RandomPlayer.h"
)
source_group("Header Files\\Players" FILES ${Header_Files__Players})

set(Header_Files__Players__MCTS
    "MCTSNode.h"
    "MCTSTree.h"
)
source_group("Header Files\\Players\\MCTS" FILES ${Header_Files__Players__MCTS})

set(Source_Files
    "Game.cpp"
    "GameCell.cpp"
    "GameField.cpp"
    "Step.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Players
    "GreedyPlayer.cpp"
    "GreedyPlayer2.cpp"
    "InteractivePlayer.cpp"
    "MCTSPlayer.cpp"
    "MiniMaxModifiedPlayer.cpp"
    "MiniMaxPlayer.cpp"
    "RandomPlayer.cpp"
)
source_group("Source Files\\Players" FILES ${Source_Files__Players})

set(Source_Files__Players__MCTS
    "MCTSNode.cpp"
    "MCTSTree.cpp"
)
source_group("Source Files\\Players\\MCTS" FILES ${Source_Files__Players__MCTS})

set(Source_Files__main
    "GenerateLevels.cpp"
)
source_group("Source Files\\main" FILES ${Source_Files__main})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Players}
    ${Header_Files__Players__MCTS}
    ${Source_Files}
    ${Source_Files__Players}
    ${Source_Files__Players__MCTS}
    ${Source_Files__main}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GenerateLevels)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++17
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

