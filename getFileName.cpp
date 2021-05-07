#include <fstream>
#include <iostream>
#include <io.h>
#include <string>
#include <vector>
#include <cstdio>

void getFiles(const std::string& path, std::vector<std::string>& files);
using namespace std;

int main()
{
	vector<std::string> filenames;//用来存储文件名
	string path = "C:\\openCV\\opencv\\newBuild\\install\\x64\\vc15\\lib";
	getFiles(path, filenames);
	ofstream outfile("C:\\openCV\\opencv\\newBuild\\install\\x64\\vc15\\libs.txt");//写入txt文本中
	for (int i = 0; i < filenames.size(); i++)
	{
		if (filenames.size() > 0) {
			outfile << filenames[i] << endl;
			cout << "filenames is ok" << endl;
		}
	}
	system("pause");
	return 0;
}


void getFiles(const std::string& path, std::vector<std::string>& files)
{
	//文件句柄
	intptr_t hFile = 0;
	//文件信息，_finddata_t需要io.h头文件
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之;如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					getFiles(p.assign(path).append("\\").append(fileinfo.name),files);
				}
			}
			else
			{
				files.push_back(fileinfo.name);  //压入文件名
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
