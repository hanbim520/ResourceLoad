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
		if (fileName == nullptr)return NULL;
		int error = 0;
		size_t strHash = ptr_hash((char*)fileName);
		auto iter = _mmapMomery.find(strHash);
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
			MapHandle mapHandle;
			mapHandle.length = strlen((char *)fileBuffer);
			mapHandle.ptr = fileBuffer;
			_mmapMomery.insert(std::pair<size_t, MapHandle>(strHash, mapHandle));
			return fileBuffer;
		}
		else {
			return iter->second.ptr;
		}
	}
	void Loader::UnLoadMetadataFile(const char* fileName)
	{
		if (fileName == nullptr)return;
		int error = 0;
		size_t strHash = ptr_hash((char*)fileName);
		auto iter = _mmapMomery.find(strHash);
		if (iter == _mmapMomery.end())
		{
			return ;
		}
		else {
			MemoryMappedFile::Unmap(iter->second.ptr);
			iter->second.ptr = nullptr;
			_mmapMomery.erase(strHash);
		}
		
	}

	int Loader::GetMetadataFileLength(const char* fileName)
	{
		size_t strHash = ptr_hash((char*)fileName);
		auto iter = _mmapMomery.find(strHash);
		if (iter == _mmapMomery.end())
		{
			return 0;
		}
		return iter->second.length;
	}
	void Loader::ReleaseAllFiles()
	{
		for (auto iter = _mmapMomery.begin(); iter != _mmapMomery.end(); iter++) {
			MemoryMappedFile::Unmap(iter->second.ptr);
			iter->second.ptr = nullptr;
		}
		_mmapMomery.clear();
	}

	Loader::~Loader() {
		ReleaseAllFiles();
	}
}

extern "C" {
	EasyLoader::Loader *loader = nullptr;
	void InitEasyLoader() {
		loader = new EasyLoader::Loader();
	}
	void ReleaseEasyLoader()
	{
		if (loader != nullptr)
		{
			delete(loader);
			loader = nullptr;
		}
	}
	void *LoadMetadataFile(const char *fileName) 
	{
		if (loader == nullptr)return nullptr;
		return  loader->LoadMetadataFile(fileName);
	}
	void UnLoadMetadataFile(const char *fileName)
	{
		if (loader == nullptr)return ;
		return loader->UnLoadMetadataFile(fileName);
	}
	int GetMetadataFileLength(const char* fileName)
	{
		if (loader == nullptr)return 0;
		return loader->GetMetadataFileLength(fileName);
	}
}