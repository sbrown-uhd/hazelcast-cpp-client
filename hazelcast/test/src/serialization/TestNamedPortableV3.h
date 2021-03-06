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
// Created by sancar koyunlu on 05/04/15.
//


#ifndef HAZELCAST_TestNamedPortableV3
#define HAZELCAST_TestNamedPortableV3

#include "hazelcast/client/serialization/Portable.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace test {
            class TestNamedPortableV3 : public serialization::Portable {
            public:
                TestNamedPortableV3();

                TestNamedPortableV3(std::string name, short k);

                int getFactoryId() const;

                int getClassId() const;

                void writePortable(serialization::PortableWriter& writer) const;

                void readPortable(serialization::PortableReader& reader);

                virtual bool operator ==(const TestNamedPortableV3& m) const;

                virtual bool operator !=(const TestNamedPortableV3& m) const;

                std::string name;
                short k;
            };
        }
    }
}


#endif //HAZELCAST_TestNamedPortableV3
