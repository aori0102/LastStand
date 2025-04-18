# This CMakeLists.txt file is used for all subdirectories 
# to link all components with the main file

# Set the sources. Ideally all the .cpp file inside the directory
set(SOURCES
    "Ammunition.cpp"
    "Bullet.cpp"
    "Consumable.cpp"
    "DamageIndicator.cpp"
    "Firearm.cpp"
    "HotBar.cpp"
    "HotBarUI.cpp"
    "Inventory.cpp"
    "InventoryUI.cpp"
    "Item.cpp"
    "PauseMenu.cpp"
    "Pistol.cpp"
    "Player.cpp"
    "PlayerStatistic.cpp"
    "Rifle.cpp"
    "Shotgun.cpp"
    "StatusBar.cpp"
    "Zombie.cpp"
)

# Add this directory as a static library
add_library(GAME_OBJECTS STATIC ${SOURCES})

# Add this directory to global include
target_include_directories(GAME_OBJECTS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories for this subdirectory use
target_include_directories(GAME_OBJECTS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)
target_include_directories(GAME_OBJECTS PUBLIC
    ${CMAKE_SOURCE_DIR}/UTILS
    ${CMAKE_SOURCE_DIR}/ECS
)

# Link libraries for this subdirectory use
target_link_libraries(GAME_OBJECTS PRIVATE
	${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)
target_link_libraries(GAME_OBJECTS PUBLIC  
    UTILS
    COMPONENTS
)