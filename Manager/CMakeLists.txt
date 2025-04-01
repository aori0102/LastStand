# This CMakeLists.txt file is used for all subdirectories 
# to link all components with the main file

# Set the sources. Ideally all the .cpp file inside the directory
set(SOURCES
    "AnimationManager.cpp"
    "GameManager.cpp"
    "ItemManager.cpp"
    "MediaManager.cpp"
    "PhysicsManager.cpp"
    "RenderManager.cpp"
    "UIEventManager.cpp"
    "WaveInfoUI.cpp"
    "WaveManager.cpp"
)

# Add this directory as a static library
add_library(MANAGER STATIC ${SOURCES})

# Add this directory to global include
target_include_directories(MANAGER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories for this subdirectory use
target_include_directories(MANAGER PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
target_include_directories(MANAGER PUBLIC  
    ${CMAKE_SOURCE_DIR}/TEXTURE
    ${CMAKE_SOURCE_DIR}/GAME_CORE
    ${CMAKE_SOURCE_DIR}/GAME_OBJECTS
    ${CMAKE_SOURCE_DIR}/MENU
)

# Link libraries for this subdirectory use
target_link_libraries(MANAGER PRIVATE
	${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
target_link_libraries(MANAGER PUBLIC     
    TEXTURE
    GAME_CORE
    GAME_OBJECTS
    MENU
)