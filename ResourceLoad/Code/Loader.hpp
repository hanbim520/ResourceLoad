//
//  Loader.hpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

# define DLLIMPORT __declspec (dllexport)

#include <stdio.h>
#include <map>
#include <functional>
#include <string>

#include "FileHandle.h"


namespace EasyLoader {
    class Loader{
	public: 
		~Loader();
	private: 
		std::map<size_t, MapHandle> _mmapMomery;
		std::hash<std::string> ptr_hash;
    public:
        void* LoadMetadataFile(const char* fileName);
		void UnLoadMetadataFile(const char* fileName);
		int GetMetadataFileLength(const char* fileName);
		void ReleaseAllFiles();
    };
}


extern "C" {
	DLLIMPORT	void  Init();
	DLLIMPORT	void  Release();
	DLLIMPORT void*  LoadMetadataFile(const char* fileName);
	DLLIMPORT void UnLoadMetadataFile(const char* fileName);
	DLLIMPORT int GetMetadataFileLength(const char* fileName);
}

#endif /* Loader_hpp */
