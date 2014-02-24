//
// Created by sancar koyunlu on 9/12/13.
// Copyright (c) 2013 hazelcast. All rights reserved.




#ifndef HAZELCAST_ListAddAllRequest
#define HAZELCAST_ListAddAllRequest

#include "hazelcast/client/collection/CollectionAddAllRequest.h"

namespace hazelcast {
    namespace client {
        namespace list {
            class HAZELCAST_API ListAddAllRequest : public collection::CollectionAddAllRequest {
            public:
                ListAddAllRequest(const std::string &name, const std::string &serviceName, const std::vector<serialization::pimpl::Data> &valueList, int index);

                int getClassId() const;

                void write(serialization::PortableWriter &writer) const;

            private:
                int index;
            };
        }
    }
}

#endif //HAZELCAST_ListAddAllRequest
