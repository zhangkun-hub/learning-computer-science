//浮点数(小数或实数)类型共3种：float、double、long double(很少用)
//不同的数据类型所表示范围和内存大小都不一样，由编译器来决定，可以用sizeof来确定
//小数取值范围比整数大
//c语言中的小数默认double类型
//不可以和unsigned组合，unsigned只能跟整数类型组合
#include<stdio.h>

int main()
{
    //1 小数类型
    //1.1 float单精度小数(精确度小数点后6位)，windows占4个字节(38位)
    float a = 3.14F; // 因为默认double类型，故float类型需添加F(或f)后缀
    printf("%f\n", a); 
    printf("%.2f\n", a); //.2表示保留小数点后两位

    //1.2 double双精度小数(精确度小数点后15位) windows占8个字节(308位)
    double b = 1.78;
    printf("%lf\n", b); //lf表示double所占字节长一点
    printf("%.3lf\n", b); //.3为保留小数点后3位

    //1.3 long double高精度小数(精确小数点后18~19位)，windows占8个字节，其他系统(12,16)
    long double c = 3.14159265L;
    __mingw_printf("%Lf\n", c); 
    printf("------------------------\n");
    /*
    注意：windows平台下printf不支持long double打印(结果为0.000000)，所以需使用MinGW-w64的专用函数
    而%f、%lf或%Lf默认打印6为小数(但double与long double的精度仍然保持)
    要打印出后面的小数则由.x来决定(x为你想打印出的小数个数)
    */

    //2 利用sizeof测量每一种数据类型占多少字节
    printf("%zu\n", sizeof(float));
    printf("%zu\n", sizeof(a));

    printf("%zu\n", sizeof(double));
    printf("%zu\n", sizeof(b));

    printf("%zu\n", sizeof(long double));
    printf("%zu\n", sizeof(c));

    return 0;
}