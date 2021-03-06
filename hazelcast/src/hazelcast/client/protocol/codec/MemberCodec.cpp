/*
 * Copyright (c) 2008-2019, Hazelcast, Inc. All Rights Reserved.
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
//
// Created by ihsan demir on 5/11/15.
//

#include "hazelcast/client/protocol/codec/AddressCodec.h"
#include "hazelcast/client/protocol/codec/MemberCodec.h"
#include "hazelcast/client/protocol/ClientMessage.h"
#include "hazelcast/client/Member.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                Member MemberCodec::decode(ClientMessage &clientMessage) {
                    Address address = AddressCodec::decode(clientMessage);
                    std::string uuid = clientMessage.get<std::string>();
                    bool liteMember = clientMessage.get<bool>();
                    int32_t attributeSize = clientMessage.get<int32_t>();
                    std::map<std::string, std::string> attributes;
                    for (int i = 0; i < attributeSize; i++) {
                        std::string key = clientMessage.get<std::string>();
                        std::string value = clientMessage.get<std::string>();
                        attributes[key] = value;
                    }

                    return Member(address, uuid, liteMember, attributes);
                }
            }
        }
    }
}
