# Set the minimum CMake version
cmake_minimum_required(VERSION 3.8)

# CMake policy for whatever reason
cmake_policy(SET CMP0079 NEW)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Set project name and version
project(LastStand VERSION 0.1)

# Link directories
add_subdirectory(Lib)
add_subdirectory(Utils)
add_subdirectory(GameCore)
add_subdirectory(Texture)
add_subdirectory(Components)
add_subdirectory(Manager)
add_subdirectory(Menu)
add_subdirectory(GameObjects)

# Set source file (main)
set(SOURCES
	main.cpp
)

# Make application executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_SOURCE_DIR}/GAME_CORE
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
	${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
	GAME_CORE
)

# Copy dll to solution output post-build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${CMAKE_SOURCE_DIR}/lib/SDL2/lib/x64/SDL2.dll"
	$<TARGET_FILE_DIR:${PROJECT_NAME}>

	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/lib/x64/SDL2_ttf.dll"
	$<TARGET_FILE_DIR:${PROJECT_NAME}>

	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${CMAKE_SOURCE_DIR}/lib/SDL2_image/lib/x64/SDL2_image.dll"
	$<TARGET_FILE_DIR:${PROJECT_NAME}>
)

function(copy_assets)
    # Define source and destination paths
    set(source "${CMAKE_SOURCE_DIR}/Asset")
    set(destination "${CMAKE_BINARY_DIR}/Asset")

    # Create command to copy the directory
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${source} ${destination}
        COMMENT "Copying assets directory"
    )
endfunction()

copy_assets()