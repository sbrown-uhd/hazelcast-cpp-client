//
// Created by sancar koyunlu on 9/4/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "hazelcast/client/queue/AddAllRequest.h"
#include "hazelcast/client/queue/QueuePortableHook.h"
#include "hazelcast/client/serialization/PortableWriter.h"


namespace hazelcast {
    namespace client {
        namespace queue {
            AddAllRequest::AddAllRequest(const std::string& name, std::vector<serialization::pimpl::Data>& dataList)
            :name(name)
            , dataList(dataList) {

            };

            int AddAllRequest::getFactoryId() const {
                return queue::QueuePortableHook::F_ID;
            }

            int AddAllRequest::getClassId() const {
                return queue::QueuePortableHook::ADD_ALL;
            }

            void AddAllRequest::write(serialization::PortableWriter& writer) const {
                writer.writeUTF("n", name);
                writer.writeLong("t", 0);
                writer.writeInt("s", dataList.size());
                serialization::ObjectDataOutput& out = writer.getRawDataOutput();
                for (int i = 0; i < dataList.size(); ++i) {
                    dataList[i].writeData(out);
                }
            };

        }
    }
}

