/*
一、C语言编译过程：4个阶段
    1.预处理阶段：由预处理器执行，处理所有#开头的指令（包括宏）。
        输入：.c源文件
        输出：.i文件（预处理后的代码）
        命令：gcc -E source.c -o source.i

    2.编译阶段：将预处理后的C代码编译成汇编代码。
        输入：.i文件
        输出：.s汇编文件
        命令：gcc -S source.i -o source.s

    3.汇编阶段：将汇编代码转为机器指令。
        输入：.s汇编文件
        输出：.o目标文件（机器码）
        命令：gcc -c source.s -o source.o

    3.链接阶段：解析外部引用，合并多个目标文件。
        输入：.o目标文件 + 库文件
        输出：可执行文件（如a.out）
        命令：gcc source.o -o program


二、预处理过程：
    1.特点：用于处理以#开头的代码，其在预处理结束后均会消失，不属于最终可执行程序的一部分，不会占用
            运行时内存，只是代码本身占用磁盘空间，并只在编译前的预处理阶段起作用。

    2.主要功能：(不止以下四种)
        (1)文件包含​ (#include)：将头文件内容插入源代码。预处理后：#include被替换为头文件内容。
            例如：
                #include <stdio.h>    // 插入标准库文件
                #include "myheader.h" // 插入自定义头文件
            
        (2)宏展开​ (#define)：在预处理后，宏代码会被展开或替换
            例如：
                #define PI 3.14159
                #define MAX(a,b) ((a)>(b)?(a):(b))

        (3)条件编译​ (#if, #ifdef, #ifndef)：
            例如：(以下代码预处理后，在非DEBUG模式下被替换为空)
                #ifdef DEBUG
                printf("Debug info\n");
                #endif


三、宏：
    1.定义：是C/C++中的预处理器指令，在编译之前由预处理器进行文本替换。
            注：宏的核心思想：简单的文本替换。

    2.宏的使用：
        (1)无参宏(对象宏)：#define 宏名 替换文本
            例如：
                #define PI 3.14159    // 预处理后PI便会替换成3.14159
                #define NEWLINE '\n'  // 预处理后NEWLINE便会替换成'\n'，即换行符操作

        (2)带参宏(函数宏)：#define 宏名(参数列表) 替换文本
            例如：
                #define SQUARE(x) ((x) * (x))  // 相当于对输入参数x进行x*x操作的函数
                #define MAX(a, b) ((a) > (b) ? (a) : (b))  // 相当于比较a,b谁更大的函数

        (3)多行宏：用\操作
            例如以下的安全的交换宏：
                #define SAFE_SWAP(a, b) do { \
                    typeof(a) temp = (a); \
                    (a) = (b); \
                    (b) = temp; \
                } while(0)

        (4)条件编译宏：见下面代码的第4个

        (5)取消宏定义：#undef 宏名

    3.特殊用法：
        (1)字符串化运算符(#)：例如：
            #define STRINGIFY(x) #x       // STRINGIFY(Hello)的输出结果是"Hello"

        (2)连接运算符(##)：例如：
            #define CONCAT(a, b) a##b    // CONCAT(value, 1)的输出结果为value1

    4.作用：
        (1)定义常量（最常用），比如53行定义的常量PI。
        (2)定义带参数的宏，达到类似函数的效果。

    5.优缺点：
        优点：
            (1)提高代码复用性：减少重复代码
            (2)提高可维护性：修改一处，全局生效
            (3)条件编译：实现跨平台、不同配置
            (4)编译时计算：常量表达式在编译时求值
            (5)无类型限制：泛型编程
            (6)调试信息：__FILE__、__LINE__等
        缺点：
            (1)调试困难：宏展开后源码与调试信息不一致
            (2)无类型检查：容易产生隐藏错误
            (3)副作用：参数可能被多次求值
            (4)作用域问题：宏是全局的，可能产生命名冲突
            (5)复杂难懂：复杂的宏难以理解和维护
*/
#include <stdio.h>
#include <time.h>

// ========== 适合使用宏的场景 ==========

// 1. 头文件保护
#ifndef MYHEADER_H
#define MYHEADER_H
// 头文件内容
#endif

// 2. 条件编译
#define DEBUG_MODE
#ifdef DEBUG_MODE
    #define DEBUG_LOG(msg) printf("[DEBUG] %s\n", msg)
#else
    #define DEBUG_LOG(msg)
#endif

// 3. 编译时常量
#define PI 3.141592653589793
#define MAX_BUFFER_SIZE 1024
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

// 4. 简单、无副作用的操作
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define IS_POWER_OF_TWO(x) (((x) & ((x) - 1)) == 0)

// 5. 平台特定代码
#ifdef _WIN32
    #define PATH_SEPARATOR "\\"
#else
    #define PATH_SEPARATOR "/"
#endif

// ========== 适合使用全局变量的场景 ==========

// 1. 需要修改的值
int global_counter = 0;           // 需要计数
volatile int interrupt_flag = 0;  // 中断标志

// 2. 复杂数据结构
typedef struct {
    int x, y;
} Point;
Point global_origin = {0, 0};     // 需要初始化和修改

// 3. 需要取地址的操作
int* get_global_counter_ptr() {
    return &global_counter;       // 可以获取地址
}

// 4. 需要类型检查
const double pi_var = 3.141592653589793;  // 类型安全

// 5. 运行时确定的常量
const int screen_width = 1920;    // 可能在运行时从配置读取
const int screen_height = 1080;

int main() {
    // 使用宏的例子
    DEBUG_LOG("程序开始");
    
    double radius = 5.0;
    double area = PI * radius * radius;  // 编译时计算
    
    int a = 5, b = 3;
    int min_val = MIN(a, b);              // 简单操作
    
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = ARRAY_SIZE(arr);        // 数组大小
    
    char path[256];
    sprintf(path, "home%stest", PATH_SEPARATOR);  // 平台相关
    
    printf("面积: %.2f\n", area);
    printf("最小值: %d\n", min_val);
    printf("数组大小: %zu\n", size);
    printf("路径分隔符: %s\n", PATH_SEPARATOR);
    
    // 使用全局变量的例子
    global_counter++;  // 可以修改
    printf("计数器: %d\n", global_counter);
    
    global_origin.x = 10;  // 可以修改结构体字段
    printf("原点: (%d, %d)\n", global_origin.x, global_origin.y);
    
    int* counter_ptr = get_global_counter_ptr();
    printf("计数器地址: %p\n", (void*)counter_ptr);
    
    // 证明宏不占内存的技巧
    printf("\n=== 内存占用证明 ===\n");
    
    // 多个地方使用同一个宏
    int arr1[MAX_BUFFER_SIZE];
    int arr2[MAX_BUFFER_SIZE];
    int arr3[MAX_BUFFER_SIZE];
    // 预处理后都变为 int arr1[1024]; 等
    // 没有额外的"MAX_BUFFER_SIZE"变量占用内存
    
    // 但如果使用变量
    const int buffer_size = 1024;
    int arr4[buffer_size];  // C99支持变长数组
    // buffer_size 变量会占用内存（4字节）
    
    printf("宏不单独占用内存，变量占用内存\n");
    
    return 0;
}