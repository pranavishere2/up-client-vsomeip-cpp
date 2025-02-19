/*
 * Copyright (c) 2024 General Motors GTO LLC
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-FileType: SOURCE
 * SPDX-FileCopyrightText: 2024 General Motors GTO LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _VSOMEIP_UTRANSPORT_H_
#define _VSOMEIP_UTRANSPORT_H_

// #include <cstddef>
// #include <unordered_map>
// #include <atomic>
#include <up-cpp/transport/UTransport.h>
#include <up-client-vsomeip-cpp/routing/SomeipRouter.hpp>
#include <memory>

class VsomeipUTransport : public uprotocol::utransport::UTransport {
public:

    /**
    * @brief The API provides an instance of the vsomeip session
    * @return instance of VsomeipUTransport
    */
    static VsomeipUTransport& instance(void) noexcept;

    /**
    * @brief Terminates the vsomeip utransport  - the API should be called by any class that called init
    * @return Returns OK on SUCCESS and ERROR on failure
    */
    uprotocol::v1::UStatus terminate() noexcept;

    /**
    * @brief Transmit UPayload to the topic using the attributes defined in UTransportAttributes.
    * @param message UMessage which contains attributes and payload information
    * @return Returns OKSTATUS if the payload has been successfully sent (ACK'ed), otherwise it
    * returns FAILSTATUS with the appropriate failure.
    */
    uprotocol::v1::UStatus send(const uprotocol::utransport::UMessage &message) noexcept;

    /**
    * Register listener to be called when UPayload is received for the specific topic.
    * @param topic Resolved UUri for where the message arrived via the underlying transport technology.
    * @param listener The method to execute to process the date for the topic.
    * @return Returns OKSTATUS if the listener is unregistered correctly, otherwise it returns FAILSTATUS
    * with the appropriate failure.
    */
    uprotocol::v1::UStatus registerListener(const uprotocol::v1::UUri &uri,
                                const uprotocol::utransport::UListener &listener) noexcept;

    /**
    * Unregister a listener for a given topic. Messages arriving on this topic will no longer be processed
    * by this listener.
    * @param topic Resolved UUri for where the listener was registered to receive messages from.
    * @param listener The method to execute to process the date for the topic.
    * @return Returns OKSTATUS if the listener is unregistered correctly, otherwise it returns FAILSTATUS
    * with the appropriate failure.
    */
    uprotocol::v1::UStatus unregisterListener(const uprotocol::v1::UUri &uri,
                                const uprotocol::utransport::UListener &listener) noexcept;

    uprotocol::v1::UStatus receive(const uprotocol::v1::UUri &uri,
                    const uprotocol::utransport::UPayload &payload,
                    const uprotocol::v1::UAttributes &attributes) noexcept;

private:
	VsomeipUTransport() {}
    VsomeipUTransport(const VsomeipUTransport&) = delete;
    VsomeipUTransport& operator=(const VsomeipUTransport&) = delete;
        /**
    * @brief init the VsomeipUTransport
    * @param listener UListener reference
    * @return Returns OK on SUCCESS and ERROR on failure
    */
    uprotocol::v1::UStatus init(const uprotocol::utransport::UListener &listener) noexcept;

    std::unique_ptr<SomeipRouter> router_;
};

#endif /*_VSOMEIP_UTRANSPORT_H_*/
