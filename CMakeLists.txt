cmake_minimum_required(VERSION 3.21)
project(PasswordContainerProd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/mingw_64/lib/cmake")


find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
find_package(OpenSSL REQUIRED)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        Network
        REQUIRED)

add_executable(PasswordContainerProd
#        WIN32
        Application/main.cpp
        Application/MainWindow/MainWindow.h
        Application/MainWindow/MainWindow.cpp
        Application/Sections/Sections.cpp
        Application/Sections/Sections.h
        Application/Widgets/Widgets.cpp
        Application/Widgets/Widgets.h
        Application/Service/SqlDB/DataBase.cpp
        Application/Service/SqlDB/DataBase.h
        Application/User/User.cpp
        Application/User/User.h
        Application/Service/SqlQuery/SqlQuery.cpp
        Application/Service/SqlQuery/SqlQuery.h
        Application/Service/TextLinesValidators/Validators.cpp
        Application/Service/TextLinesValidators/Validators.h
        Application/main.cpp
        Application/Service/Update/UpdateQuery.cpp
        Application/Service/Update/UpdateQuery.h
        Application/Service/Email/EmailSender.cpp
        Application/Service/Email/EmailSender.h
        Application/Run/ApplicationRun.cpp
        Application/Run/ApplicationRun.h
)


target_link_libraries(PasswordContainerProd
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        Qt::Network
        OpenSSL::SSL
        OpenSSL::Crypto
        ${CURL_LIBRARIES}
)











if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()