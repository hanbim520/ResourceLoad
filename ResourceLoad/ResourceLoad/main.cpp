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
#include "DataInfoProto.pb.h"

static std::string fileName = "I:/Github/ResourceLoad/ClientLog.txt";
bool hasWrite = false;

void WriteFile(JxSDK::DataInfo datas)
{
	std::string szFileName = "../ClientLog.txt";
	std::fstream output(szFileName, std::ios::out | std::ios::binary | std::ios::app);
	datas.SerializePartialToOstream(&output);
	output.flush();
	output.close();
	hasWrite = true;
}
EasyLoader::Loader *_loader = new  EasyLoader::Loader();
void DoTest()
{
	clock_t start, finish;
	double totaltime;
	std::mutex mMutext;


	start = clock();
	for (int i = 0; i < 1000; ++i)
	{
#if TARGET_WIN
		void* file = _loader->LoadMetadataFile(fileName.c_str());
		//	char* content = (char *)file;
		JxSDK::DataInfo dataTmp;
		dataTmp.ParseFromArray(file, sizeof(JxSDK::DataInfo));
#else
		void* file = _loader->LoadMetadataFile("/Users/zhanghaijun/Desktop/TENCENT_MSDKUnity_ALL_3.2.27.1_99388.zip");
		char* content = (char *)file;
#endif


	}
	
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
	
	if (hasWrite)return;
	JxSDK::DataInfo dataPb;
	dataPb.set_mapstr("fdfdsafaddfaas");
	dataPb.set_width(1024);
	dataPb.set_height(512);
	dataPb.set_size(1022);
	std::cout << sizeof(JxSDK::DataInfo) << std::endl;
	char * pData = new char[sizeof(JxSDK::DataInfo)];
	dataPb.SerializePartialToArray(pData, sizeof(JxSDK::DataInfo));
	if (sizeof(pData) == 0)
		std::cout << "error" << std::endl;
	//byte * pData2 = new byte[sizeof DataInfo];
	JxSDK::DataInfo dataTmp;
	dataTmp.ParseFromArray(pData, sizeof(JxSDK::DataInfo));
	WriteFile(dataTmp);
}


int main(int argc, const char * argv[]) {
	char ch = getchar();
	while (std::cin >> ch) {  //输入没有结束，cin 就返回 true，条件就为真
		DoTest();
	}
    getchar();
	_loader->UnLoadMetadataFile(fileName.c_str());
    return 0;
}
