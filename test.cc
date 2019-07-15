#include "RSA.h"
#include <iostream>
#include <stdlib.h>


void testString()
{
	RSA rsa;
	Key key = rsa.getKey();
	std::string strin;
	std::cout << "输入加密信息：" << std::endl;
	std::cin >> strin;

	std::vector<bm::int1024_t> strecrept = rsa.ecrept(strin, key.ekey, key.pkey);
	std::string strout = rsa.decrept(strecrept, key.dkey, key.pkey);
	std::cout << "加密后的信息: " << std::endl;
	rsa.printInfo(strecrept);
	//std::cout << strecrept << std::endl;
	std::cout << "解密后的信息: " << std::endl;
	std::cout << strout << std::endl;
}

void testFile()
{
	RSA rsa;
	Key key = rsa.getKey();
	std::string filename;
	std::cout << "输入文件名：" << std::endl;
	std::cin >> filename;
	rsa.ecrept(filename.c_str(), (filename + "ecrept.out.jpg").c_str(), key.ekey, key.pkey);
	rsa.decrept((filename + "ecrept.out.jpg").c_str(), (filename + "decrept.out").c_str(), key.dkey, key.pkey);
}

void testBigInter()
{
	bm::cpp_int a("123487385734758743756746437867477");
	std::cout << a << std::endl;
	std::cout << a / 2 << std::endl;
	std::cout << a % 2 << std::endl;
	std::cout << a % 7 << std::endl;

}
int main()
{
	//testString();
	//testFile();
	testBigInter();
	system("pause");

	return 0;
}


