cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
set(SDK_PATH "/opt/sdk/aarch64-buildroot-linux-gnu_sdk-buildroot")
set(PKG_CONFIG_PATH "${PROJECT_SOURCE_DIR}/dbus-1.10.10/")

# define commonapi tool path
if(DEFINED CMAKE_TOOLCHAIN_FILE)
set(CMAKE_BUILD "cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE")
set(DBUS_CONFIGURE "./configure --host=aarch64-buildroot-linux-gnu CC=${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-gcc --prefix=/usr --disable-tests")
else()
set(CMAKE_BUILD "cmake")
set(DBUS_CONFIGURE "./configure")
endif()

# download capicxx-core-runtime and compile
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-core-runtime/)
execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/capicxx-core-runtime.git ${PROJECT_SOURCE_DIR}/capicxx-core-runtime")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-core-runtime && mkdir build && cd build && ${CMAKE_BUILD} .. && make")
endif()

#download dbus runtime
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/)
execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/capicxx-dbus-runtime.git ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime")
endif()

#download dbus
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/dbus-1.10.10.tar.gz)
execute_process(COMMAND bash -c "wget http://dbus.freedesktop.org/releases/dbus/dbus-1.10.10.tar.gz -P ${PROJECT_SOURCE_DIR}")
endif()

#compile dbus
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/dbus-1.10.10/)
execute_process(COMMAND bash -c "tar -xzf ${PROJECT_SOURCE_DIR}/dbus-1.10.10.tar.gz -C ${PROJECT_SOURCE_DIR}")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/dbus-1.10.10 && for i in ../capicxx-dbus-runtime/src/dbus-patches/*.patch; do patch -p1 < $i; done")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/dbus-1.10.10 && ${DBUS_CONFIGURE} && make")
endif()

#compile dbus runtime
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/build/)
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime && mkdir build")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/build && ${CMAKE_BUILD} -DUSE_INSTALLED_COMMONAPI=OFF -DUSE_INSTALLED_DBUS=OFF .. && make")
endif()

# # download vsomeip and compile
# if(NOT EXISTS ${PROJECT_SOURCE_DIR}/vsomeip/)
# execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/vsomeip.git ${PROJECT_SOURCE_DIR}/vsomeip")
# execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/vsomeip && mkdir build && cd build && ${CMAKE_BUILD} -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 .. && make")
# endif()

# # download capicxx-someip-runtime and compile
# if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime/)
# execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/capicxx-someip-runtime.git ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime")
# execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime && mkdir build && cd build && ${CMAKE_BUILD} -DUSE_INSTALLED_COMMONAPI=OFF .. && make")
# endif()

# #generate source file form fidl 
# execute_process(COMMAND ${SDK_PATH}/bin/capicxx-core-tools/commonapi-core-generator-linux-x86_64 -sk ${PROJECT_SOURCE_DIR}/fidl/HelloWorld.fidl -d ${PROJECT_SOURCE_DIR}/src-gen/core)
# execute_process(COMMAND ${SDK_PATH}/bin/capicxx-dbus-tools/commonapi-dbus-generator-linux-x86_64 ${PROJECT_SOURCE_DIR}/fidl/HelloWorld.fidl -d ${PROJECT_SOURCE_DIR}/src-gen/dbus)
# execute_process(COMMAND ${SDK_PATH}/bin/capicxx-someip-tools/commonapi-someip-generator-linux-x86 ${PROJECT_SOURCE_DIR}/fidl/HelloWorld.fdepl -d ${PROJECT_SOURCE_DIR}/src-gen/someip)

# #include all head file folders
# include_directories(
#     inc
#     src-gen/core
#     src-gen/dbus
#     src-gen/someip
#     ${PROJECT_SOURCE_DIR}/capicxx-core-runtime/include
#     ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/include
#     ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime/include
#     ${PROJECT_SOURCE_DIR}/dbus-1.10.10
#     ${PROJECT_SOURCE_DIR}/vsomeip/interface
# )

# #link all runtime libs folder
# link_directories(
#     ${PROJECT_SOURCE_DIR}/capicxx-core-runtime/build
#     ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/build
#     ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime/build
#     ${PROJECT_SOURCE_DIR}/dbus-1.10.10/dbus/.libs
#     ${PROJECT_SOURCE_DIR}/vsomeip/build
# )

# #generator dbus applications
# add_executable(HelloWorldClientDbus
# 	src/HelloWorldClient.cpp
# 	src-gen/dbus/v1/commonapi/HelloWorldDBusProxy.cpp
# 	src-gen/dbus/v1/commonapi/HelloWorldDBusDeployment
# )
# target_link_libraries(HelloWorldClientDbus CommonAPI CommonAPI-DBus dbus-1)
# add_executable(HelloWorldServiceDbus
# 	src/HelloWorldService.cpp
# 	src/HelloWorldStubImpl.cpp
# 	src-gen/dbus/v1/commonapi/HelloWorldDBusStubAdapter.cpp
# 	src-gen/core/v1/commonapi/HelloWorldStubDefault
# 	src-gen/dbus/v1/commonapi/HelloWorldDBusDeployment
# )
# target_link_libraries(HelloWorldServiceDbus CommonAPI CommonAPI-DBus dbus-1)

# #generate someip applications
# add_executable(HelloWorldClientSomeip
# 	src/HelloWorldClient.cpp
# 	src-gen/someip/v1/commonapi/HelloWorldSomeIPProxy.cpp
# 	src-gen/someip/v1/commonapi/HelloWorldSomeIPDeployment.cpp
# )
# target_link_libraries(HelloWorldClientSomeip CommonAPI CommonAPI-SomeIP vsomeip3)
# add_executable(HelloWorldServiceSomeip
# 	src/HelloWorldService.cpp
# 	src/HelloWorldStubImpl.cpp
# 	src-gen/someip/v1/commonapi/HelloWorldSomeIPStubAdapter.cpp
# 	src-gen/core/v1/commonapi/HelloWorldStubDefault
# 	src-gen/someip/v1/commonapi/HelloWorldSomeIPDeployment
# )
# target_link_libraries(HelloWorldServiceSomeip CommonAPI CommonAPI-SomeIP vsomeip3)
