#include <fstream>
#include <iostream>
#include <io.h>
#include <string>
#include <vector>
#include <cstdio>
void getFiles(const std::string& path, std::vector<std::string>& files, std::vector<std::string>& labelloc);
//获得标签和样本路径
using namespace std;
int main()
{
    vector<std::string> filenames;//用来存储文件名
    vector<std::string> labellocation;  //用来存储标签的
    string path = "C:\\Users\\xpp19\\Documents\\orl_faces";
    getFiles(path, filenames, labellocation);
    ofstream outfile("C:\\Users\\xpp19\\Documents\\test.txt");//写入txt文本中
    for (int i = 0; i < filenames.size(); i++)
    {
        outfile << filenames[i] << endl;
        outfile << labellocation[i] << endl;
    }
    system("pause");
    return 0;
}
void getFiles(const std::string& path, std::vector<std::string>& files, std::vector<std::string>& labelloc)
{
    //文件句柄
    intptr_t hFile = 0;
    //文件信息，_finddata_t需要io.h头文件
    struct _finddata_t fileinfo;
    std::string p;
    string prepath = string("C:\\Users\\xpp19\\Documents\\orl_faces");
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是目录,迭代之
            //如果不是,加入列表
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files, labelloc);
                    //此处进入迭代
                }
            }
            else
            {
                string pp = p.assign(path);
                //用来更新当前路径, 迭代到此处时, 路径为C:\\Users\\xpp19\\Documents\\orl_faces\\s1
                string ppsub = pp.erase(0, 35);
                //把前35个字符弹出, 因为\\表示一个字符, 所以弹出前35个,得到s1字符
                labelloc.push_back(ppsub);
                //压入s1字符串
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                //压入样本地址, 此时地址C:\\Users\\xpp19\\Documents\\orl_faces\\s1\\1.pgm
                /*这样每一个<Vector>files的元素都和<Vector>labellocation元素对应起来了*/
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}