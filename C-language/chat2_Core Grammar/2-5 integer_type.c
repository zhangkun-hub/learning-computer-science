//整数类型共4种：short、int、long、long long
//不同数据类型所表示的范围和内存大小都不一样，由编译器来决定，可以用sizeof来确定
//但任何编译器都遵循short <= int <= long <= long long
//c语言中的整数类型默认int类型
#include<stdio.h>

int main()
{
    //1.定义short、int、long、long long四种数据类型的变量
    //格式：数据类型 + 变量名 = 数据值
    
    //short短整型：windows为2个字节（-32768 ~ 32767）
    short a = 32769; //注意：超出范围则会溢出，比如这里输出的则为-32767
    printf("%d\n", a);

    //int整型：windows为4个字节（-2147483648 ~ 2147483647）
    int b = 100;
    printf("%d\n", b);

    //long长整型：windows为4个字节；Linux中若32位则4个字节，若64位则8个字节
    long c = 1000L; //注意给long型赋值其要加L作为后缀，大小写都可(但最好写大写)
    printf("%ld\n", c); //注意打印long型变量，其 %d 要改为 %ld (l大小写都可)

    //long long(C99)超长整型：windows为8个字节(19位数)
    long long d = 1000000LL; //注意要加两个L后缀
    printf("%lld\n", d); //注意打印long型变量，其 %d 要改为 %lld (l大小写都可)
    printf("------------------------\n");

    //2.利用sizeof测量每一种数据类型占用多少字节
    //short
    printf("%zu\n", sizeof(short)); //注意：sizeof的占位符为%zu
    printf("%zu\n", sizeof(a));

    //int
    printf("%zu\n", sizeof(int)); 
    printf("%zu\n", sizeof(b));

    //long
    printf("%zu\n", sizeof(long)); 
    printf("%zu\n", sizeof(c));

    //long long
    printf("%zu\n", sizeof(long long)); 
    printf("%zu\n", sizeof(d));
    printf("------------------------\n");

    //扩展1.整数类型完整形式：例如short int e = 10; 但注意int int是错误的
    long int g = 10000L;
    printf("%ld\n", g);

    //扩展2.有符号整数、无符号整数的定义
    //2.1 有符号整数signed：正数、负数(默认是有符号整数,所以signed前缀可以省略)
    signed int h = 100;
    signed int l = -21;
    printf("%d\n", h);
    printf("%d\n", l);
    printf("------------------------\n");

    //2.2 无符号整数unsigned：正数(适用场景：比如定义一个变量表示序号),注意此时取值范围有变化
    unsigned int f = 999; //如果赋值负数会出错，结果为
    printf("%u\n",f); //注意：无符号整数的占位符为%u

    return 0;
}