#include <iostream>

// PropertyBuilderByName 用于生成类的成员变量
// 并生成set和get方法
// type 为变量类型
// access_permission 为变量的访问权限(public, priavte, protected)
#define PropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type m_##name;\
    public:\
    inline void set##name(type v) {\
        m_##name = v;\
    }\
    inline type get##name() {\
        return m_##name;\
    }\

#define PointerPropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type* m_##name;\
    public:\
        inline void set##name(type* v){\
            m_##name = v;\
        }\
        inline type* get##name(){\
            return m_##name;\
        }

class Test {
    PropertyBuilderByName(int, A, private)
    PointerPropertyBuilderByName(double, pB, private)
};

int main() {
    Test t;
    int a = 10;
    double b = 1.234;
    t.setA(a);
    std::cout << "a = " << t.getA() << std::endl;
    t.setpB(&b);
    std::cout << "b = " << *(t.getpB()) << std::endl;
    system("pause");
    return 0;
}

// ————————————————
// 版权声明：本文为CSDN博主「This is bill」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/Scythe666/article/details/48846761
