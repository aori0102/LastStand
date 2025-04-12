# This CMakeLists.txt file is used for all subdirectories 
# to link all components with the main file

# Set the sources. Ideally all the .cpp file inside the directory
set(SOURCES
    "AnimationController.cpp"
    "BoxCollider.cpp"
    "GameComponent.cpp"
    "GameObject.cpp"
    "Humanoid.cpp"
    "RigidBody.cpp"
    "Transform.cpp"
)

# Add this directory as a static library
add_library(COMPONENTS STATIC ${SOURCES})

# Add this directory to global include
target_include_directories(COMPONENTS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories for this subdirectory use
target_include_directories(COMPONENTS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)
target_include_directories(COMPONENTS PUBLIC    
    ${CMAKE_SOURCE_DIR}/UTILS
    ${CMAKE_SOURCE_DIR}/GAME_OBJECTS
)

# Link libraries for this subdirectory use
target_link_libraries(COMPONENTS PRIVATE
	${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)
target_link_libraries(COMPONENTS PUBLIC     
    UTILS
    GAME_OBJECTS
)