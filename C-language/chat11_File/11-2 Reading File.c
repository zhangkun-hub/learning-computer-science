/*
读取文件：把本地文件的数据，读到程序中来
1.步骤：
    (1)打开文件：fopen。
    (2)读文件：(注意：对于中文的读取，需要在记事本的编码中选相应的编码格式，比如此处为UTF-8)
            fgetc:一次读一个字符，读到就返回该字符，读不到返回-1；
            fgets:一次读一行字符(以换行符为标准)，读到就返回该行字符串，读不到返回NULL；
            fread:一次多个字符，可以跨行处理。
    (3)关闭文件：fclose。

2.上面函数的格式：
    打开文件：FILE* file = fopen("文件路径", "模式") # 注：file是可随便定义变量名，此处file为例。
        其中文件类型指针(FILE)一定要大写；文件路径一定要避免转义字符；模式见下面三的内容
    
    读文件：int a = fgetc(file);  
        其中file是(1)中fopen输出的指针file；而返回值为整数变量a，用来接收读取的数据

    读文件：char* str = fgets(arr, a, file)
        参数：arr是字符串类型，用来承载读取到一行的数据，其字符串长度一般取为1024或其整数倍；
                a表示拿多少字节数来承载数据，可小于字符串arr长度(一般造成浪费，所以没必要)；
                file是(1)中fopen输出的指针file；
        返回值：字符串str用来承载读取到一行的数据结果
                与arr承载数据相同,所以可不写,但一般写上用来判断没读到的结束条件NULL

    读文件：int n = fread(arr, m, a, file)
        参数：arr是任意类型数组，用来承载读取到的多个数据，其长度一般取为1024或其整数倍；
                m为数组每个元素所占的字节数，一般选char类型，则m = 1；
                a表示每次拿多少字节数来承载数据，可小于字符串arr长度(一般造成浪费，所以没必要)；
                file是(1)中fopen输出的指针file；
        返回值：变量n表示每次读到数据的字节数，没有数据则返回0。
        细节：在fread函数读取文件时，每次尽可能的把数组装满，返回当前读到的有效字节数。
        举例：文件：70字节；数组长度：30
            第一次运行fread：读取前30个字节，把数组装填满，fread函数返回30；
            第二次运行fread：读取后30个字节，把数组装填满，fread函数返回30；
            第三次运行fread：读取剩余10个字节，并放在把数组中，fread函数返回10；
            第四次运行fread：没有数据可读取了，fread函数返回0。

    关闭文件：fclose(file)  # 对(1)中fopen返回的指针file对应的文件进行关闭。
*/
#include<stdio.h>

int main()
{
    // 示例1 打开文件用fgetc进行编辑
    printf("------------- 示例1 --------------\n");   
    // 文件a.txt位置：D:\VSCode\Computer_Languages_learning\C-code\chat11_File\w.txt
    // 1.打开文件
    FILE* file = fopen("D:\\VSCode\\Computer_Languages_learning\\C-code\\chat11_File\\w.txt",
        "r");

    // 2.用fgetc函数读取数据
    int c;
    while ((c = fgetc(file)) != -1)
    {
        printf("%c", c);
    }
    printf("\n");
    
    // 3.关闭文件
    fclose(file);


    // 示例2 用fgets进行编辑
    printf("------------- 示例2 --------------\n");  
    // 1.打开文件
    FILE* file2 = fopen("D:\\VSCode\\Computer_Languages_learning\\C-code\\chat11_File\\w.txt",
        "r");  // r是只读模式

    // 2.用fgets读取数据
    char arr[1024];  // 一般写1024或其整数倍
    char* str;
    while ((str = fgets(arr, 1024, file2)) != NULL)
    {
        printf("%s", str);
    }
    printf("\n");

    // 3.关闭文件
    fclose(file2);


    // 示例3 用fread进行编辑
    printf("------------- 示例3 --------------\n");  
    // 1.打开文件
    FILE* file3 = fopen("D:\\VSCode\\Computer_Languages_learning\\C-code\\chat11_File\\w.txt",
        "r");

    // 2.用fread读取数据
    char arr2[1024];  // 一般写1024或其整数倍
    int n;
    while ((n = fread(arr2, 1, 1024, file3)) != 0)
    {
        // 通过for循环将读取的数据按照其长度n打印,从而避免直接打印整个数组,使未赋值空位被打印乱码
        for (int i = 0; i < n; i++)
        {
            printf("%c", arr2[i]);
        }
        
    }
    printf("\n");

    // 3.关闭文件
    fclose(file3);




    return 0;
}