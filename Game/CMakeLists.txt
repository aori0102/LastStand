# This CMakeLists.txt file is used for all subdirectories 
# to link all components with the main file

# Set the sources. Ideally all the .cpp file inside the directory
set(SOURCES
    "Game.cpp"
    "Player.cpp"
    "Type.cpp"
    "Projectile.cpp"
    "GameComponent.cpp"
    "Zombie.cpp"
    "Physics.cpp"
    "Humanoid.cpp"
    "Firearm.cpp"
    "FirearmUI.cpp"
    "Texture.cpp"
    "GameManager.cpp"
    "GameObject.cpp"
    "Transform.cpp"
    "BoxCollider.cpp"
    "Shop.cpp"
    "UIEvent.cpp"
    "Animation.cpp"
    "RenderManager.cpp"
    "StatusBar.cpp"
    "PlayerStatistic.cpp"
)

# Add this directory as a static library
add_library(GAME STATIC ${SOURCES})

# Add this directory to global include
target_include_directories(GAME PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories for this subdirectory use
target_include_directories(GAME PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
# target_include_directories(EVENT PUBLIC    SOME_OTHER_INCLUDE)

# Link libraries for this subdirectory use
target_link_libraries(GAME PRIVATE
	${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
# target_link_libraries(EVENT PUBLIC        SOME_OTHER_LIBRARIES)