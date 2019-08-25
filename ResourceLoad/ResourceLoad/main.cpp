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

#include "../Code/Loader.hpp"

void DoTest()
{
	clock_t start, finish;
	double totaltime;

	EasyLoader::Loader *_loader = new  EasyLoader::Loader();

	start = clock();
	for (int i = 0; i < 1000; ++i)
	{
#if TARGET_WIN
		void* file = _loader->LoadMetadataFile("I:/UnityPro/MSDK/MSDK_Unity_3.2.27.1_99388.unityPackage");
		//	char* content = (char *)file;
#else
		void* file = _loader->LoadMetadataFile("/Users/zhanghaijun/Desktop/TENCENT_MSDKUnity_ALL_3.2.27.1_99388.zip");
		char* content = (char *)file;
#endif


	}

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "mmap cost time: " << totaltime << " ms" << std::endl;

	// std::cout << content;
	char data[1000000];
	std::ifstream infile;
	start = clock();
	for (int i = 0; i < 1000; ++i) {
		memset(data, 0, 1000000);
#if TARGET_WIN
		infile.open("I:/UnityPro/MSDK/MSDK_Unity_3.2.27.1_99388.unityPackage");
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
	// 在屏幕上写入数据
   // std::cout << data << std::endl;

}
int main(int argc, const char * argv[]) {
	char ch = getchar();
	while (std::cin >> ch) {  //输入没有结束，cin 就返回 true，条件就为真
		DoTest();
	}
    getchar();
    return 0;
}
