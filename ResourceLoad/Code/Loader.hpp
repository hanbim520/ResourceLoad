//
//  Loader.hpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#include <stdio.h>

namespace EasyLoader {
    class Loader{
    public:
        void* LoadMetadataFile(const char* fileName);
    };
}

#endif /* Loader_hpp */
