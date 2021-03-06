#include <iostream>
#include <memory>
#include <string>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/ACNReader.h"

using namespace std;

int main(){
    auto lf = Nuz::IEngine::GetGameDevice().GetLocalFile(); //获取本地文件系统实例
    Nuz::IEngine::GetGameDevice().GetFileSystem().Mount(lf,"e");    //把本地文件系统挂载到文件系统的目录“e”下
    auto acn = NuzUtils::IACNReader::CreateACNReader("/e/test/NuzUtils/ACNReader/test.acn");   //加载acn文件
    acn -> SaveToBinaryFile("/test/NuzUtils/ACNReader/test.elf");	//输出二进制的acn文件
    acn = NuzUtils::IACNReader::CreateACNReader("/e/test/NuzUtils/ACNReader/test.elf");	//读取二进制的acn文件

    while(1){
        std::string arg;
        auto opr = acn -> GetOpr(arg);	//取得acn要求的操作和参数
        cout<<"ACN OPR:"<<int(opr)<<" "<<arg<<endl;	//输出操作和参数
        if(opr == NuzUtils::IACNReader::ACNOpr::End) break;	//如果结束则退出
    }

    cout<<acn -> GetCurrentDir()<<endl;	//输出当前目录
    return 0;
}
