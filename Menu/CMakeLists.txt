# This CMakeLists.txt file is used for all subdirectories 
# to link all components with the main file

# Set the sources. Ideally all the .cpp file inside the directory
set(SOURCES
    "FirearmAttributeUIGroup.cpp"
    "FirearmSelectionUI.cpp"
    "FirearmUpgrade.cpp"
    "FirearmUpgradeUIGroup.cpp"
    "Shop.cpp"
)

# Add this directory as a static library
add_library(MENU STATIC ${SOURCES})

# Add this directory to global include
target_include_directories(MENU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include directories for this subdirectory use
target_include_directories(MENU PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
	${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)
target_include_directories(MENU PUBLIC   
    ${CMAKE_SOURCE_DIR}/UTILS
    ${CMAKE_SOURCE_DIR}/COMPONENTS
    ${CMAKE_SOURCE_DIR}/GAME_OBJECTS
    ${CMAKE_SOURCE_DIR}/MANAGER
    ${CMAKE_SOURCE_DIR}/GAME_CORE
)

# Link libraries for this subdirectory use
target_link_libraries(MENU PRIVATE
	${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
target_link_libraries(MENU PUBLIC
    UTILS
    COMPONENTS
    GAME_OBJECTS
    MANAGER
    GAME_CORE
)