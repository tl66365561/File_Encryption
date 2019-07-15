## File_Encryption/文件加密

#A small file encryption project based on RSA algorithm./基与RSA算法实现的一个关于文件加密的小项目。

###RSA密钥产生过程：
1. 随机选择两个不相等的质数p和q(实际应用中，这两个质数越大，就越难破解)。
2. 计算p和q的乘积n，n = pq。
3. 计算n的欧拉函数φ(n)。
4. 随机选择一个整数e，条件是1< e < φ(n)，且e与φ(n) 互质。
5. 计算e对于φ(n)的模反元素d，使得de≡1 mod φ(n)。
7. 产生公钥(e,n)，私钥(d,n)。
