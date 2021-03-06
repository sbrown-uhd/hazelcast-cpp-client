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

#include "hazelcast/util/Util.h"
#include "hazelcast/util/ILogger.h"

#include "hazelcast/client/protocol/codec/ClientAuthenticationCustomCodec.h"
#include "hazelcast/client/serialization/pimpl/Data.h"
#include "hazelcast/client/Address.h"
#include "hazelcast/client/Member.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                const ClientMessageType ClientAuthenticationCustomCodec::REQUEST_TYPE = HZ_CLIENT_AUTHENTICATIONCUSTOM;
                const bool ClientAuthenticationCustomCodec::RETRYABLE = true;
                const ResponseMessageConst ClientAuthenticationCustomCodec::RESPONSE_TYPE = (ResponseMessageConst) 107;

                std::auto_ptr<ClientMessage> ClientAuthenticationCustomCodec::encodeRequest(
                        const serialization::pimpl::Data &credentials,
                        const std::string *uuid,
                        const std::string *ownerUuid,
                        bool isOwnerConnection,
                        const std::string &clientType,
                        uint8_t serializationVersion,
                        const std::string &clientHazelcastVersion) {
                    int32_t requiredDataSize = calculateDataSize(credentials, uuid, ownerUuid, isOwnerConnection,
                                                                 clientType, serializationVersion,
                                                                 clientHazelcastVersion);
                    std::auto_ptr<ClientMessage> clientMessage = ClientMessage::createForEncode(requiredDataSize);
                    clientMessage->setMessageType((uint16_t) ClientAuthenticationCustomCodec::REQUEST_TYPE);
                    clientMessage->setRetryable(RETRYABLE);
                    clientMessage->set(credentials);
                    clientMessage->set(uuid);
                    clientMessage->set(ownerUuid);
                    clientMessage->set(isOwnerConnection);
                    clientMessage->set(clientType);
                    clientMessage->set(serializationVersion);
                    clientMessage->set(clientHazelcastVersion);
                    clientMessage->updateFrameLength();
                    return clientMessage;
                }

                int32_t ClientAuthenticationCustomCodec::calculateDataSize(
                        const serialization::pimpl::Data &credentials,
                        const std::string *uuid,
                        const std::string *ownerUuid,
                        bool isOwnerConnection,
                        const std::string &clientType,
                        uint8_t serializationVersion,
                        const std::string &clientHazelcastVersion) {
                    int32_t dataSize = ClientMessage::HEADER_SIZE;
                    dataSize += ClientMessage::calculateDataSize(credentials);
                    dataSize += ClientMessage::calculateDataSize(uuid);
                    dataSize += ClientMessage::calculateDataSize(ownerUuid);
                    dataSize += ClientMessage::calculateDataSize(isOwnerConnection);
                    dataSize += ClientMessage::calculateDataSize(clientType);
                    dataSize += ClientMessage::calculateDataSize(serializationVersion);
                    dataSize += ClientMessage::calculateDataSize(clientHazelcastVersion);
                    return dataSize;
                }

                ClientAuthenticationCustomCodec::ResponseParameters::ResponseParameters(ClientMessage &clientMessage) {
                    serverHazelcastVersionExist = false;
                    clientUnregisteredMembersExist = false;


                    status = clientMessage.get<uint8_t>();


                    address = clientMessage.getNullable<Address>();


                    uuid = clientMessage.getNullable<std::string>();


                    ownerUuid = clientMessage.getNullable<std::string>();


                    serializationVersion = clientMessage.get<uint8_t>();
                    if (clientMessage.isComplete()) {
                        return;
                    }

                    serverHazelcastVersion = clientMessage.get<std::string>();
                    serverHazelcastVersionExist = true;

                    clientUnregisteredMembers = clientMessage.getNullableArray<Member>();
                    clientUnregisteredMembersExist = true;
                }

                ClientAuthenticationCustomCodec::ResponseParameters
                ClientAuthenticationCustomCodec::ResponseParameters::decode(ClientMessage &clientMessage) {
                    return ClientAuthenticationCustomCodec::ResponseParameters(clientMessage);
                }

                ClientAuthenticationCustomCodec::ResponseParameters::ResponseParameters(
                        const ClientAuthenticationCustomCodec::ResponseParameters &rhs) {
                    status = rhs.status;
                    address = std::auto_ptr<Address>(new Address(*rhs.address));
                    uuid = std::auto_ptr<std::string>(new std::string(*rhs.uuid));
                    ownerUuid = std::auto_ptr<std::string>(new std::string(*rhs.ownerUuid));
                    serializationVersion = rhs.serializationVersion;
                    serverHazelcastVersion = rhs.serverHazelcastVersion;
                    clientUnregisteredMembers = std::auto_ptr<std::vector<Member> >(
                            new std::vector<Member>(*rhs.clientUnregisteredMembers));
                }

            }
        }
    }
}

