/*
后缀表达式(也称逆波兰表示法，Postfix Expression)：
一、定义：是一种数学表达式的书写方式，用来方便计算机进行求值运算。
    
    注：中缀表达式(Infix expression): 我们熟知的操作符在操作数中间的表达式，比如(3 + 4) * 5。


二、特点：操作符位于两个操作数之后，并完全消除括号，从而方便计算机进行求值运算(具体见三部分内容)。
        举例：(3 + 4) * 5对应的后缀表达式为：3 4 + 5 *


三、计算后缀表达式的过程(需要用到栈来辅助)：
    1.从左到右扫描表达式(注意：表达式以字符串形式存储，而字符串末尾有\0结束符)。

    2.遇到操作数，就将其压入栈。

    3.遇到操作符，则从栈中弹出两个操作数（注意顺序：先弹出的是右操作数，后弹出的是左操作数），
        按操作符进行计算，并将结果压回栈中。

    4.扫描结束后(通过识别结束符\0来结束)，栈中剩下的唯一数字就是最终结果。


四、中缀表达式转换成后缀表达式的操作见3-7
*/
#include<stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // 通过宏定义，将MAXSIZE设置成100
typedef int ElemType; // 给int类型起别名ElemType，使得以后如果改为其他类型，只需修改此处int


// ============= 基础结构定义 =============
// 栈的顺序结构定义(用于存储操作数)
typedef struct{
    ElemType* data; 
    int top;        
}Stack;

// 用枚举型(enum)的标识符指代后缀表达式的各字符内容
typedef enum{
    LEFT_PARE,  // 左括号
    RIGHT_PARE, // 右括号
    ADD,        // 加
    SUB,        // 减
    MUL,        // 乘
    DIV,        // 除
    MOD,        // 取余
    EOS,        // 结束符\0
    NUM         // 数字
}contentType;


// ============= 后缀表达式 ==============
char expr[] = "82/2+56*-";


// ============= 所需要的栈的操作 =============
// 栈的初始化
Stack* initStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    s->top = -1; 
    return s;
}

// 进栈(push)
int push(Stack* s, ElemType e)
{
    if (s->top >= MAXSIZE - 1)
    {
        printf("栈已满\n");
        return 0;
    }
    s->top++;
    s->data[s->top] = e;
    return 1;
}

// 出栈(pop)
int pop(Stack* s, ElemType* e)
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 0;
    }
    *e = s->data[s->top]; 
    s->top--;
    return 1;
}


// ============= 后缀表达式的求解操作 =============
/*
辅助函数：getToken
    形参：记录后缀表达式的字符symbol、记录后缀表达式的第index个索引

    函数作用：
        (1)将后缀表达式expr的第*index索引的字符x赋值给*symbol；
        (2)赋完值后，将索引index的值加1(当下次调用该函数时索引指向的是后缀表达式的下一个字符)；
        (3)返回字符x对应的枚举型contentType的标识符(例如EOS、NUM等)。
*/
contentType getToken(char* symbol, int* index)
{
    *symbol = expr[*index]; // 取出后缀表达式expr的第*index索引的字符并赋值给*symbol
    *index = *index + 1;    

    // 将后缀表达式的第*index索引的字符*symbol进行以下模式匹配
    switch(*symbol)
    {
        case '(':
            return LEFT_PARE;
        case ')':
            return RIGHT_PARE;
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '%':
            return MOD;
        case '\0':
            return EOS;
        default:
            return NUM;
    }
}

// 主要函数：后缀表达式的求解
int eval(Stack* s)
{
    // 创建各个变量
    char symbol;       // 记录后缀字符串的各个字符
    int op1, op2;      // op1记录左操作数，op2记录右操作数
    int index = 0;     // 记录后缀表达式的索引值(第0个索引开始)
    contentType token; // 记录后缀表达式各字符对应的枚举标识符(例如EOS、NUM等)
    ElemType result;   // 记录后缀表达式的求解结果

    // getToken函数具体见辅助函数内容
    token = getToken(&symbol, &index);
    
    // 通过循环不断扫描表达式并求解
    while (token != EOS) // 循环结束条件：token是字符串结束符\0(用EOS指代)
    {
        // token是数字NUM：将其压入栈s中
        if (token == NUM) 
        {
            push(s, symbol - '0'); // symbol - '0'：将symbol的字符数字转成int类型传入push中
        }
        // token是操作符：从栈s中先取出右操作数，再取出左操作数，按操作符进行计算，将结果压回栈中
        else  
        {
            pop(s, &op2); // 第一次出栈给右操作数op2赋值
            pop(s, &op1); // 第二次出栈给左操作数op1赋值

            // 通过token的操作符内容进行模式匹配，然后进行该操作运算，并将结果压入栈s中
            switch(token)
            {
                case ADD:
                    push(s, op1 + op2);
                    break;
                case SUB:
                    push(s, op1 - op2);
                    break;
                case MUL:
                    push(s, op1 * op2);
                    break;
                case DIV:
                    push(s, op1 / op2);
                    break;
                case MOD:
                    push(s, op1 % op2);
                    break;
                default:
                    break;
            }
        }

        // 执行后缀表达式的下一个索引的getToken操作
        token = getToken(&symbol, &index);
    }

    // 将后缀表达式求解结果从栈s中取出并赋值给result
    pop(s, &result);
    printf("%d\n", result);
    return 1;
}


// ============= 主函数main =============
int main()
{
    // 声明一个栈s并初始化
    Stack* s = initStack();

    // 打印后缀表达式expr的形式
    printf("%s\n", expr); // 82/2+56*-

    // 求解后缀表达式expr
    eval(s); // -24


    free(s);



    return 0;
}
