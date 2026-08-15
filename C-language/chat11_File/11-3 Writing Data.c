/*
写文件：
1.步骤：
    (1)打开文件：fopen。
    (2)读文件：(注意：对于中文的读取，需要在记事本的编码中选相应的编码格式，比如此处为UTF-8)
            fputc:一次写一个字符，返回写出的字符，写出失败则返回整数-1；
            fputs:一次写一个字符串，返回为成功返回的非数，一般忽略返回值；
            fwrite:一次写多个字符，返回写出的个数。
    (3)关闭文件：fclose。

2.上面函数的格式：其中打开文件步骤记作：FILE* file = fopen("文件路径", "w")  # w是只写模式
    (1)int b = fputc(a, file)  
        参数：a为要写入的字符，要求输入整数类型。原理通过ASCII码转换为字符，比如98 ---> b。
        返回值：整数类型b为写出的字符(通过ASCII码转换)，所以用%c打印，
                但如果写出失败则返回整数-1，用%d打印。

    (2)int n = fputs(str, file)
        参数：str为要写入的字符串。
        返回值：n为整数类型，表示如果写成功就为非负数，一般忽略(因为如果写出失败，就会有EOF的错误)

    (3)int d = fputs(arr, m, a, file)
        参数：数组arr是写入的数据内容；
              m表示数组中每个元素所占的字节数；
              a表示拿多少字节数来承载每次写入的数据，可小于arr长度(一般造成浪费，所以没必要)。
        返回值：d表示每次写入的数据所占的字节个数。
*/
#include<stdio.h>

int main()
{ 
    // 文件b.txt位置：D:\VSCode\Computer_Languages_learning\C-code\chat11_File\x.txt
    // 1.打开文件
    FILE* file = fopen("D:\\VSCode\\Computer_Languages_learning\\C-code\\chat11_File\\x.txt",
        "w");  // w是只写模式

    // 2.写出数据
    // (1)用fputc函数写出数据
    int c = fputc(98, file);
    printf("%c\n", c);  // b

    // (2)用fputs函数写出数据
    int n = fputs("你好的很abc", file);
    printf("%d\n", n);  // 0  (表示写出成功)

    // (3)用fwrite函数写出数据
    char arr[] = {97, 98, 99, 100, 101}; // 里面的数字通过ASCII码转换为字符
    int n2 = fwrite(arr, 1, 5, file);
    printf("%d\n", n2);  // 5    (即写入的数据为5个字节数)
    
    // 3.关闭文件
    fclose(file);




    return 0;
}