
#pragma once 

//RSA:加解密公式
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
namespace bm = boost::multiprecision;

struct Key
{
	//公钥（ekey, pkey):(e,n)
	bm::int1024_t pkey;
	bm::int1024_t ekey;
	//私钥（dkey, pkey): (d, n)
	bm::int1024_t dkey;
};

class RSA
{
public:
	RSA();
	Key getKey()
	{
		return _key;
	}
	//加密
	void ecrept(const char* plain_file_in, const char* ecrept_file_out, bm::int1024_t ekey, bm::int1024_t pkey);
	//解密
	void decrept(const char* ecrept_file_in, const char* plain_file_out, bm::int1024_t ekey, bm::int1024_t pkey);
	//给字符串加密
	std::vector<bm::int1024_t> ecrept(std::string& str_in, bm::int1024_t ekey, bm::int1024_t pkey);

	//给字符串解密
	std::string decrept(std::vector<bm::int1024_t> ecrept_str, bm::int1024_t ekey, bm::int1024_t pkey);



	//打印
	void printInfo(std::vector<bm::int1024_t>& ecrept_str);


private:
	bm::int1024_t produce_prime(); //产生素数
	bool is_prime(bm::int1024_t prime);
	void produce_keys();
	bm::int1024_t produce_pkey(bm::int1024_t prime1, bm::int1024_t prime2);
	bm::int1024_t produce_orla(bm::int1024_t prime1, bm::int1024_t prime2);
	bm::int1024_t produce_ekey(bm::int1024_t orla);
	bm::int1024_t produce_gcd(bm::int1024_t ekey, bm::int1024_t orla); //最大公约数
	bm::int1024_t produce_dkey(bm::int1024_t ekey, bm::int1024_t orla);
	//加密单个信息
	bm::int1024_t ecrpt(bm::int1024_t msg, bm::int1024_t key, bm::int1024_t pkey);
private:
	Key _key;
};
 
