# This CMakeLists.txt file is used for all subdirectories 
# to link all components with the main file

# Set the sources. Ideally all the .cpp file inside the directory
set(SOURCES
    "Align.cpp"
    "AnimationClip.cpp"
    "AnimationNode.cpp"
    "Bound.cpp"
    "Color.cpp"
    "Math.cpp"
    "Random.cpp"
    "Vector2.cpp"
)

# Add this directory as a static library
add_library(UTILS STATIC ${SOURCES})

# Add this directory to global include
target_include_directories(UTILS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories for this subdirectory use
target_include_directories(UTILS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)
target_include_directories(UTILS PUBLIC  
    ${CMAKE_SOURCE_DIR}/COMPONENTS
    ${CMAKE_SOURCE_DIR}/TEXTURE
    ${CMAKE_SOURCE_DIR}/GAME_CORE
)

# Link libraries for this subdirectory use
target_link_libraries(UTILS PRIVATE
	${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)
target_link_libraries(UTILS PUBLIC  
    COMPONENTS
    TEXTURE
    GAME_CORE
)