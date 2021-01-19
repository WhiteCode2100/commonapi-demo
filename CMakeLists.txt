cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
set(SDK_PATH "/opt/sdk/aarch64-buildroot-linux-gnu_sdk-buildroot")

# define commonapi tool path
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)

#define commonapi include path
set(CAPICXX_CORE_PATH "${PROJECT_SOURCE_DIR}/capicxx-core-runtime/include")
set(CAPICXX_DBUS_PATH "${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/include")
set(CAPICXX_SOMEIP_PATH "${PROJECT_SOURCE_DIR}/capicxx-someip-runtime/include")
set(DBUS_PATH "${PROJECT_SOURCE_DIR}/dbus-1.10.10")
set(VSOMEIP_PATH "${PROJECT_SOURCE_DIR}/vsomeip/interface")
set(TIGER_FRAMEWORK_PATH "${PROJECT_SOURCE_DIR}/tiger-framework/")

#define commonapi link folder path
set(CAPICXX_CORE_LINK_PATH "${PROJECT_SOURCE_DIR}/capicxx-core-runtime/build")
set(CAPICXX_DBUS_LINK_PATH "${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/build")
set(CAPICXX_SOMEIP_LINK_PATH "${PROJECT_SOURCE_DIR}/capicxx-someip-runtime/build")
set(DBUS_LINK_PATH "${PROJECT_SOURCE_DIR}/dbus-1.10.10/dbus/.libs")
set(VSOMEIP_LINK_PATH "${PROJECT_SOURCE_DIR}/vsomeip/build")
set(TIGER_LINK_PATH "${PROJECT_SOURCE_DIR}/tiger-framework/build/tigerLogger")

# download capicxx-core-runtime and compile
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-core-runtime/)
execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/capicxx-core-runtime.git ${PROJECT_SOURCE_DIR}/capicxx-core-runtime")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-core-runtime && mkdir build && cd build && cmake .. && make")
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
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/dbus-1.10.10 && ./configure && make")
endif()

#compile dbus runtime
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/build/)
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime && mkdir build")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-dbus-runtime/build && PKG_CONFIG_PATH=${PROJECT_SOURCE_DIR}/dbus-1.10.10 cmake -DUSE_INSTALLED_COMMONAPI=OFF -DUSE_INSTALLED_DBUS=OFF .. && make")
endif()

# download vsomeip and compile
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/vsomeip/)
execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/vsomeip.git ${PROJECT_SOURCE_DIR}/vsomeip")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/vsomeip && mkdir build && cd build && cmake -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 .. && make")
endif()

# download capicxx-someip-runtime and compile
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime/)
execute_process(COMMAND bash -c "git clone https://github.com/GENIVI/capicxx-someip-runtime.git ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/capicxx-someip-runtime && mkdir build && cd build && cmake -DUSE_INSTALLED_COMMONAPI=OFF .. && make")
endif()

#download tiger framework and compiel
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/tiger-framework/)
execute_process(COMMAND bash -c "git clone git@githost.nevint.com:ds/tiger-imx8/tiger-framework.git ${PROJECT_SOURCE_DIR}/tiger-framework")
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/tiger-framework && mkdir build && cd build && cmake .. && make")
endif()

else()

execute_process(COMMAND bash -c "echo ${COMMONAPI_INCLUDE_DIRS}")
find_package(CommonAPI 3.2.0 REQUIRED CONFIG NO_CMAKE_PACKAGE_REGISTRY)
find_package(CommonAPI-DBus 3.2.0 REQUIRED CONFIG NO_CMAKE_PACKAGE_REGISTRY)
find_package (CommonAPI-SomeIP 3.2.0 REQUIRED)
find_package (vsomeip3 3.1.20 REQUIRED)

#define commonapi include path
set(CAPICXX_CORE_PATH "${COMMONAPI_INCLUDE_DIRS}")
set(DBUS_PATH "${SDK_PATH}/aarch64-buildroot-linux-gnu/sysroot/usr/include/dbus-1.0")
set(DBUS_PATH1 "${SDK_PATH}/aarch64-buildroot-linux-gnu/sysroot/usr/lib/dbus-1.0/include")
set(CAPICXX_DBUS_PATH "${COMMONAPI_DBUS_INCLUDE_DIRS}")
set(CAPICXX_SOMEIP_PATH "${COMMONAPI_SOMEIP_INCLUDE_DIRS}")
set(VSOMEIP_PATH "${VSOMEIP_INCLUDE_DIRS}")

endif()

find_package(Boost 1.58 COMPONENTS log log_setup system thread REQUIRED)

include(FindPkgConfig)
pkg_check_modules(DBus REQUIRED dbus-1>=1.4)

#generate source file form fidl 
execute_process(COMMAND ${SDK_PATH}/bin/capicxx-core-tools/commonapi-core-generator-linux-x86_64 -sk ${PROJECT_SOURCE_DIR}/fidl/M4Agent.fidl -d ${PROJECT_SOURCE_DIR}/src-gen/core)
execute_process(COMMAND ${SDK_PATH}/bin/capicxx-dbus-tools/commonapi-dbus-generator-linux-x86_64 ${PROJECT_SOURCE_DIR}/fidl/M4Agent.fidl -d ${PROJECT_SOURCE_DIR}/src-gen/dbus)
execute_process(COMMAND ${SDK_PATH}/bin/capicxx-someip-tools/commonapi-someip-generator-linux-x86 ${PROJECT_SOURCE_DIR}/fidl/M4Agent.fdepl -d ${PROJECT_SOURCE_DIR}/src-gen/someip)

#include all head file folders
include_directories(
    inc
    src-gen/core
    src-gen/dbus
    src-gen/someip
    ${CAPICXX_CORE_PATH}
    ${CAPICXX_DBUS_PATH}
    ${CAPICXX_SOMEIP_PATH}
	${DBUS_PATH}
	${DBUS_PATH1}
	${VSOMEIP_PATH}
	${TIGER_FRAMEWORK_PATH}
)

#link all runtime libs folder
link_directories(
    ${CAPICXX_CORE_LINK_PATH}
    ${CAPICXX_DBUS_LINK_PATH}
    ${CAPICXX_SOMEIP_LINK_PATH}
    ${DBUS_LINK_PATH}
	${VSOMEIP_LINK_PATH}
	${TIGER_LINK_PATH}
)

#generator dbus applications
add_executable(M4AgentClientDbus
	src/M4AgentClient.cpp
	src-gen/dbus/v1/commonapi/nio_m4_agent/M4AgentDBusProxy.cpp
	src-gen/dbus/v1/commonapi/nio_m4_agent/M4AgentDBusDeployment
)
target_link_libraries(M4AgentClientDbus libtigerLogger.a ${Boost_LIBRARIES} CommonAPI CommonAPI-DBus dbus-1)
add_executable(M4AgentServiceDbus
	src/M4AgentService.cpp
	src/M4AgentStubImpl.cpp
	src/M4Interface.cpp
	src-gen/dbus/v1/commonapi/nio_m4_agent/M4AgentDBusStubAdapter.cpp
	src-gen/core/v1/commonapi/nio_m4_agent/M4AgentStubDefault
	src-gen/dbus/v1/commonapi/nio_m4_agent/M4AgentDBusDeployment
)
target_link_libraries(M4AgentServiceDbus libtigerLogger.a ${Boost_LIBRARIES} CommonAPI CommonAPI-DBus dbus-1)

#generate someip applications
add_executable(M4AgentClientSomeip
	src/M4AgentClient.cpp
	src-gen/someip/v1/commonapi/nio_m4_agent/M4AgentSomeIPProxy.cpp
	src-gen/someip/v1/commonapi/nio_m4_agent/M4AgentSomeIPDeployment.cpp
)
target_link_libraries(M4AgentClientSomeip libtigerLogger.a ${Boost_LIBRARIES} CommonAPI CommonAPI-SomeIP vsomeip3)
add_executable(M4AgentServiceSomeip
	src/M4AgentService.cpp
	src/M4AgentStubImpl.cpp
	src/M4Interface.cpp
	src-gen/someip/v1/commonapi/nio_m4_agent/M4AgentSomeIPStubAdapter.cpp
	src-gen/core/v1/commonapi/nio_m4_agent/M4AgentStubDefault
	src-gen/someip/v1/commonapi/nio_m4_agent/M4AgentSomeIPDeployment
)
target_link_libraries(M4AgentServiceSomeip libtigerLogger.a ${Boost_LIBRARIES} CommonAPI CommonAPI-SomeIP vsomeip3)
