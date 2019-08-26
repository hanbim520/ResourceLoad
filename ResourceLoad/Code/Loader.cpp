//
//  Loader.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//
#include "Loader.hpp"
#include "FileHandle.h"
#include "MemoryMappedFile.hpp"
#include "File.hpp"
#include <map>

namespace EasyLoader {
	void* Loader::LoadMetadataFile(const char* fileName)
	{
		if (fileName == nullptr)return;
		int error = 0;
		auto iter = _mmapMomery.find(fileName);
		if (iter == _mmapMomery.end())
		{
			
			FileHandle* handle = File::Open(fileName, kFileModeOpen, kFileAccessRead, kFileShareRead, kFileOptionsNone, &error);
			if (error != 0)
				return NULL;

			void* fileBuffer = MemoryMappedFile::Map(handle);

			File::Close(handle, &error);
			if (error != 0)
			{
				MemoryMappedFile::Unmap(fileBuffer);
				fileBuffer = NULL;
				return NULL;
			}
			_mmapMomery.insert(std::pair<const char*, void*>(fileName, fileBuffer));
			return fileBuffer;
		}
		else {
			return iter->second;
		}
	}
	void Loader::UnLoadMetadataFile(const char* fileName)
	{
		if (fileName == nullptr)return;
		int error = 0;
		auto iter = _mmapMomery.find(fileName);
		if (iter == _mmapMomery.end())
		{
			return ;
		}
		else {
			MemoryMappedFile::Unmap(iter->second);
			iter->second = NULL;
			_mmapMomery.erase(fileName);
		}
		
	}
}
