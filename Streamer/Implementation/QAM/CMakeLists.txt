# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2020 Metrological
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(PLAYER_NAME QAM)
message("Building ${PLAYER_NAME} Streamer....")

find_package(${NAMESPACE}Broadcast REQUIRED)
find_package(NXCLIENT REQUIRED)

set(LIB_NAME PlayerPlatform${PLAYER_NAME})

add_library(${LIB_NAME}
     PlayerImplementation.cpp)

set_target_properties(${LIB_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES)

if (PLUGIN_STREAMER_TS_SCANNING)
    target_compile_definitions(${LIB_NAME}
        PRIVATE
            ENABLE_TS_SCANNING)
endif(PLUGIN_STREAMER_TS_SCANNING)

target_include_directories(${LIB_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../)

target_link_libraries(${LIB_NAME}
    PRIVATE
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${NAMESPACE}Broadcast::${NAMESPACE}Broadcast)

install(TARGETS ${LIB_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)
