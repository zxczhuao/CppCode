/*
 * @Author: zxczhuao
 * @Date: 2023-03-11 22:15:27
 * @LastEditTime: 2023-03-11 22:20:34
 * @FilePath: /CppCode/Vector/test.cpp
 * @Description: 
 * 
 */
#include "Vector.h"

void test1()
{
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	// int()
	// 为了支持泛型，内置类型也可以用类似于构造函数的方式创建变量
	int b = int();
	int c = int(3);
	v.Resize(10,c);

	auto vit = v.begin();
	while (vit != v.end())
	{
		if (*vit % 2 == 0)
			vit = v.Earse(vit);
		else
			++vit;
	}

	//for (int i = 0; i < (int)v.Size(); i++)
	//{
	//	cout << v[i] << " ";
	//}
	//cout << endl;
	/*Vector<string> v2;
	v2.PushBack("abc");
	v2.PushBack("def");
	v2.PushBack("ghi");
	v2.PushBack("jkl");
	v2.Insert(v2.begin(),"hao");
	v2.Insert(v2.end(), "zhong");
	v2.Insert(v2.begin() + 1, "guo");*/
	//v2[2] = "chaoqiwen shi xiaoguapi";
	//auto vit = v2.begin();
	//*vit = "xiaoguapi";
	//PrintVectorIterator(v2);
	PrintVectorIterator2(v);

}
int main()
{
	//vector<int> v;
	//cout << v.capacity() << endl;
	test1();
	//system("pause");
	return 0;
}