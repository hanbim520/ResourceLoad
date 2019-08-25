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
#include <map>

#include "FileHandle.h"

namespace EasyLoader {
    class Loader{
	private: 
		std::map<const char*, void*> _mmapMomery;
    public:
        void* LoadMetadataFile(const char* fileName);
		void UnLoadMetadataFile(const char* fileName);
    };
}

#endif /* Loader_hpp */
