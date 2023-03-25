/*
 * @Author: zxczhuao
 * @Date: 2023-03-25 13:03:38
 * @LastEditTime: 2023-03-25 13:14:17
 * @FilePath: /CppCode/design/Single/HungrySingleton.cpp
 * @Description: 
 * 
 */
class HungrySingleton_1{
public:
    static HungrySingleton_1* getInstance(){
        return &instance;
    }
private:
    HungrySingleton_1(){};
    ~HungrySingleton_1(){};
    HungrySingleton_1(const HungrySingleton_1&) = delete;
    HungrySingleton_1& operator=(const HungrySingleton_1&) = delete;
    static HungrySingleton_1 instance;
};

HungrySingleton_1 HungrySingleton_1::instance;;