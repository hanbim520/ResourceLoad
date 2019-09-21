//
//  main.cpp
//  ResourceLoad
//
//  Created by 张海军 on 8/2/19.
//  Copyright © 2019 张海军. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstddef>

#include "../Code/Loader.hpp"
#ifdef TARGET_WIN
//#include "DataInfoProto.pb.h"
#endif
static std::string fileName = "D:/abc.txt";
bool hasWrite = false;

EasyLoader::Loader *_loader = new  EasyLoader::Loader();
void DoTest()
{
	clock_t start, finish;
	double totaltime;
	std::mutex mMutext;


	start = clock();
	void* file = _loader->LoadMetadataFile(fileName.c_str());
	char* content = (char *)file;
	
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "mmap cost time: " << totaltime << " ms" << std::endl;
	return;
	// std::cout << content;
	char data[1000000];
	std::ifstream infile;
	start = clock();
	for (int i = 0; i < 1000; ++i) {
		memset(data, 0, 1000000);
#if TARGET_WIN
		mMutext.lock();
		infile.open(fileName);
		mMutext.unlock();
		//	infile >> data;
#else
		infile.open("/Users/zhanghaijun/Desktop/TENCENT_MSDKUnity_ALL_3.2.27.1_99388.zip");
		infile >> data;
#endif

	}

	infile.close();
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "normal cost time: " << totaltime << " ms"<< std::endl;
	
}


int main(int argc, const char * argv[]) {
	DoTest();
    getchar();
	_loader->UnLoadMetadataFile(fileName.c_str());
    return 0;
}
