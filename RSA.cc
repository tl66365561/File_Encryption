#include "RSA.h"
#include <time.h>
#include <iostream>
#include <fstream>
RSA::RSA()
{
	produce_keys();
}

//加密
void RSA::ecrept(const char* plain_file_in, const char* ecrept_file_out, bm::int1024_t ekey, bm::int1024_t pkey)
{
	std::ifstream fin(plain_file_in);
	std::ofstream fout(ecrept_file_out, std::ofstream::app);
	if (!fin.is_open())
	{
		std::cout << "open file failed!" << std::endl;
		return;
	}
	//判断文件有多大
	//太大，一次可能读不进来
	/*fin.seekg(0, fin.end);
	bm::int1024_t bytes = fin.tellg();*/
	
	/*seekg（）是对输入文件定位，它有两个参数：第一个参数是偏移量，第二个参数是基地址。
		对于第一个参数，可以是正负数值，正的表示向后偏移，负的表示向前偏移。而第二个参数可以是：
	
		tellg（）函数不需要带参数，它返回当前定位指针的位置，也代表着输入流的大小。
		
	*/
	//分批读文件
	const int NUM = 256;
	char buffer[NUM];
	bm::int1024_t buffer_out[NUM];
	int curNum;
	//打开文件，按块读取，逐段加密
	while (!fin.eof())
	{


		//给哪里读，从哪里写

		fin.read(buffer, NUM);
		//告诉你读了多少个字节
		curNum = fin.gcount();
		for (int i = 0; i < curNum; ++i)
		{
			buffer_out[i] = ecrpt((bm::int1024_t)buffer[i], ekey, pkey);
		}
		fout.write((char*)buffer_out, curNum*sizeof(bm::int1024_t));
	}
	fin.close();
	fout.close();
}
//解密
void RSA::decrept(const char* ecrept_file_in, const char* plain_file_out, bm::int1024_t dkey, bm::int1024_t pkey)
{
	std::ifstream fin(ecrept_file_in);
	std::ofstream fout(plain_file_out, std::ofstream::app);
	if (!fin.is_open())
	{
		std::cout << "open file failed!" << std::endl;
		return;
	}
	const int NUM = 256;
	bm::int1024_t buffer[NUM];
	char buffer_out[NUM];
	int curNum;
	//打开文件，按块读取，逐段解密
	while (!fin.eof())
	{
		fin.read((char*)buffer, NUM * sizeof(bm::int1024_t));
		//告诉你读了多少个字节
		curNum = fin.gcount();

		curNum /= sizeof(bm::int1024_t);
		
		for (int i = 0; i < curNum; ++i)
		{
			buffer_out[i] = (char)ecrpt(buffer[i], dkey, pkey);
		}
		fout.write(buffer_out, curNum);
	}
	fin.close();
	fout.close();


}
//给字符串加密
std::vector<bm::int1024_t> RSA::ecrept(std::string& str_in, bm::int1024_t ekey, bm::int1024_t pkey)
{
	std::vector<bm::int1024_t> vecout;
	size_t sz = str_in.size();
	vecout.resize(sz);
	for (const auto& e : str_in)
	{
		vecout.push_back(ecrpt(e, ekey, pkey));
	}
	return vecout;
}

//给字符串解密
std::string RSA::decrept(std::vector<bm::int1024_t> ecrept_str, bm::int1024_t dkey, bm::int1024_t pkey)
{
	std::string strout;
	for (const auto& e : ecrept_str)
	{
		strout.push_back((char)ecrpt(e, dkey, pkey));
	}
	return strout;
}

//打印
void RSA::printInfo(std::vector<bm::int1024_t>& ecrept_str)
{
	for (const auto& e : ecrept_str)
	{
		std::cout << e << "";
	}
	std::cout << std::endl;
}

//加密单个信息
//模幂运算
bm::int1024_t RSA::ecrpt(bm::int1024_t msg, bm::int1024_t key, bm::int1024_t pkey)
{
	//溢出
	/*bm::int1024_t ret = pow(msg, key);
	return ret % pkey;*/
	bm::int1024_t msg_out = 1;
	//A0 = a^(2^0) = a^1 = a;
	bm::int1024_t a = msg;
	bm::int1024_t b = key;
	bm::int1024_t c = pkey;
	while (b)
	{
		if (b & 1)
			//msg_out = A0*A1...*AI...An) %c;
			msg_out = (msg_out * a) % c;
		b >>= 1;
		//Ai = (A(i-1) * A(i-1)) % c
		a = (a*a) % c;

	}
	return msg_out;

}


bm::int1024_t RSA::produce_prime() //产生素数
{
	//随机选择素数
	srand((unsigned)time(nullptr));
	bm::int1024_t prime = 0;
	while (1)
	{
		prime = rand() % 50 + 2;
		if (is_prime(prime))
			break;
	}
	return prime;
}
bool RSA::is_prime(bm::int1024_t prime)
{
	if (prime < 2)
		return false;
	for (int i = 2; i <= sqrt(prime); ++i)
	{
		if (prime % i == 0)
			return false;
	}
	return true;
}

void RSA::produce_keys()
{
	bm::int1024_t prime1 = produce_prime();
	bm::int1024_t prime2 = produce_prime();
	while (prime1 == prime2)
	{
		prime2 = produce_prime();
	}
	_key.pkey = produce_pkey(prime1, prime2);
	bm::int1024_t orla = produce_orla(prime1, prime2);
	_key.ekey = produce_ekey(orla);
	_key.dkey = produce_dkey(_key.ekey, orla);
}
bm::int1024_t RSA::produce_pkey(bm::int1024_t prime1, bm::int1024_t prime2)
{
	// n = p*q;
	return prime1*prime2;
}
bm::int1024_t RSA::produce_orla(bm::int1024_t prime1, bm::int1024_t prime2)
{
	return (prime1 - 1)*(prime2 - 1);
}
bm::int1024_t RSA::produce_ekey(bm::int1024_t orla)
{
	//随机选择一个数  1<e<orla,  且 两者互质
	bm::int1024_t ekey;
	srand((unsigned)time(nullptr));
	while (1)
	{
		ekey = rand() % orla;  //肯定小于orla
		if (ekey > 1 && produce_gcd(ekey, orla) == 1)
			//找	到了
			break;
	}
	return ekey;
}
bm::int1024_t RSA::produce_gcd(bm::int1024_t ekey, bm::int1024_t orla) //最大公约数
{
	//gcd(a, b) == gcd(b, a%b);  欧几里得定理
	bm::int1024_t residual; //余数
	while (residual = ekey % orla)
	{
		//a = b
		ekey = orla;
		//b = a % b
		orla = residual;
	}
	return orla;
}
bm::int1024_t RSA::produce_dkey(bm::int1024_t ekey, bm::int1024_t orla)
{
	//(dkey * ekey) % orla == 1;  求dkey
	// x * 5 % 20 == 1
	bm::int1024_t dkey = orla / ekey;	
	while (1)
	{
		if ((dkey * ekey) % orla == 1)
			break;
		++dkey;
	}
	return dkey;
}

