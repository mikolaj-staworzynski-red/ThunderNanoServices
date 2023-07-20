/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "Module.h"

#include <core/core.h>

using namespace WPEFramework;

void eventHandler_pluginState(const JsonObject &parameters) {
    std::cout<<"ThunderLink::eventHandler_pluginState"<<std::endl;
}

int main(int argc, char** argv)
{
    Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T("127.0.0.1:55555")));
    {
        WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement> *remoteObjectController = nullptr;
        remoteObjectController = new WPEFramework::JSONRPC::LinkType<Core::JSON::IElement>("", "", false);
        if (nullptr != remoteObjectController)
        {
            //sleep(2); // first subscribe works fine with that sleep
            auto ev_ret = remoteObjectController->Subscribe<JsonObject>(10000, _T("statechange"), &eventHandler_pluginState);
            printf("[%s:%d] Controller - statechange event : %s : %d\n", __FILE__, __LINE__, (ev_ret == Core::ERROR_NONE) ? "subscribed" : "failed to subscribe", ev_ret);
            // second subscribe works fine
            ev_ret = remoteObjectController->Subscribe<JsonObject>(1000, _T("statechange"), &eventHandler_pluginState);
            printf("[%s:%d] Controller - statechange event : %s : %d\n", __FILE__, __LINE__, (ev_ret == Core::ERROR_NONE) ? "subscribed" : "failed to subscribe", ev_ret);
            delete remoteObjectController;
        }
    }

    return (0);
}
