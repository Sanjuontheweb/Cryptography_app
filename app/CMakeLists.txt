cmake_minimum_required(VERSION 3.16)

project(Cypherin)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    Qml
    Gui
)

qt_standard_project_setup()

qt_policy(SET QTP0001 NEW)

qt_add_executable(Cypherin
    main.cpp
    bridge.cpp
    ../backend/cryption/cryption_main.cpp
    ../backend/cryption/encyptDecrypt/file_cryption.cpp
    ../backend/cryption/file_handling/IO.cpp
    ../backend/cryption/file_handling/ReadFromEnv.cpp
    ../backend/cryption/processManagement/pM.cpp
    ../backend/cypher/verify_main.cpp
    ../backend/cypher/myevp_key.cpp
)

qt_add_qml_module(Cypherin
    URI gui_for_cypher
    QML_FILES
        Main.qml
	    cryption_window.qml
	    cypher_window.qml

    RESOURCES
    	resources/wallpaper.jpg
        usage.txt
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.

target_link_libraries(Cypherin
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
)

target_include_directories(Cypherin PRIVATE
    ../backend
    ../backend/cryption
    ../backend/cypher
    ../backend/cryption/file_handling
    ../backend/cryption/processManagement
    ../backend/cryption/encyptDecrypt
    ../backend/cryption/files

)
