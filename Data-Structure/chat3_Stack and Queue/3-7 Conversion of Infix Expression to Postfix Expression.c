/*
中缀表达式(Infix expression)转换为后缀表达式(Postfix expression)：
一、一些注意事项：
    1.需要用到栈来辅助
    2.操作符之间的优先级通过ASCII的值来判定，其中结束符'\0'的ASCII值为0，优先级最低。

二、具体操作步骤：
    1.先将优先级最低的结束符'\0'压入栈中，作为栈顶。

    2.遇到操作数，直接输出。

    3.遇到操作符，与栈顶操作符比较优先级：
        (1)若栈顶为结束符'\0'或左括号'('，或当前操作符优先级高于栈顶操作符，则直接入栈；
        (2)若没栈顶操作符优先级高或相等，则将栈顶操作符弹出并输出，然后重复比较。

    4.遇到左括号'('，直接入栈（可理解为栈外'('优先级最高，但进栈后'('优先级最低，与'\0'一致）。

    5.遇到右括号')'，则不断弹出栈顶操作符并输出，直到遇到左括号'('（注意：左括号弹出但不输出）。

    6.表达式读完后，将栈中剩余的所有操作符（除'\0'）依次弹出并输出，最终输出结果便是后缀表达式。
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

// 用枚举型(enum)的标识符指代中缀表达式的各字符内容
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


// ============= 中缀表达式 ==============
char expr[] = "x/(i-j)*y";


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


// ============= 中缀表达式转换成后缀表达式 =============
/*
辅助函数1：getToken
    形参：记录中缀表达式的字符symbol、记录中缀表达式的第index个索引

    函数作用：
        (1)将中缀表达式expr的第*index索引的字符x赋值给*symbol；
        (2)赋完值后，将索引index的值加1(当下次调用该函数时索引指向的是中缀表达式的下一个字符)；
        (3)返回字符x对应的枚举型contentType的标识符(例如EOS、NUM等)。
*/
contentType getToken(char* symbol, int* index)
{
    *symbol = expr[*index]; // 取出中缀表达式expr的第*index索引的字符并赋值给*symbol
    *index = *index + 1;    

    // 将中缀表达式的第*index索引的字符*symbol进行以下模式匹配
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

// 辅助函数2：将传入的枚举标识符token转成对应的表达式操作符并打印
int print_token(contentType token)
{
    switch(token)
    {
        case ADD:
            printf("+");
            break;
        case SUB:
            printf("-");
            break;
        case MUL:
            printf("*");
            break;
        case DIV:
            printf("/");
            break;
        case MOD:
            printf("%%"); // 注：打印%需要两个%%，因为一个%有特殊含义，就跟转义字符/n一样
            break;
        default:
            return 0;
    }
    return 1;
}

// 主要函数：中缀表达式转换成后缀表达式
void postfix(Stack* s)
{
    // 记录操作符优先级的数组(从左到右的数字依次指代枚举型里操作符的优先级，而最后一个NUM不包含)
    // 在栈内各种操作符的优先级（栈内左括号'('优先级最低）
    int in_stack[] = {0, 19, 12, 12, 13, 13, 13, 0};
    // 在栈外各种操作符的优先级（栈外左括号'('优先级最高）
    int out_stack[] = {20, 19, 12, 12, 13, 13, 13, 0};

    // 创建各个变量
    char symbol;       // 记录中缀字符串的各个字符
    int index = 0;     // 记录中缀表达式的索引值(第0个索引开始)
    contentType token; // 记录中缀表达式各字符对应的枚举标识符(例如EOS、NUM等)
    ElemType e;        // 记录要进栈出栈的元素

    // 栈s的初始设置
    s->top = 0;        // 初始栈顶指针设置为0(即栈的最底层)
    s->data[0] = EOS;  // 初始栈顶元素设置为EOS(即结束符'\0')
    
    // getToken函数具体见辅助函数1内容
    token = getToken(&symbol, &index);

    // 通过循环不断扫描中缀表达式并转换成后缀表达式
    while (token != EOS) // 循环结束条件：标识符token为结束符EOS(即'\0')
    {
        // 标识符token是数字则输出打印
        if (token == NUM)
        {
            printf("%c", symbol);
        }
        // 标识符token是右括号时，从栈s中不断取出标识符，直到左括号LEFT_PARE为止
        else if (token == RIGHT_PARE)
        {
            while (s->data[s->top] != LEFT_PARE)
            {
                pop(s, &e);
                print_token(e); // 打印枚举标识符e对应的具体表达式操作符(见辅助函数2)
            }
            pop(s, &e); // 取出左括号标识符LEFT_PARE，但不打印(即直接丢弃)
        }
        // 标识符是除结束符EOS、数字NUM、右括号RIGHT_PARE之外的各种操作符
        else
        {
            // 当栈外标识符token小于等于栈顶标识符时,不断从栈s中取出栈顶标识符并打印,直到大于为止
            while (in_stack[s->data[s->top]] >= out_stack[token])
            {
                pop(s, &e);
                print_token(e);
            }
            // 当栈外标识符token大于栈顶标识符时便将其压入栈s中
            push(s, token);
        }
        // 执行中缀表达式的下一个索引的getToken操作
        token = getToken(&symbol, &index);
    }

    // 中缀表达式扫描完毕后，依次取出栈s内的标识符并打印，直到取到栈底标识符即结束符EOS为止
    pop(s, &e);
    token = e;
    while (token != EOS)
    {
        print_token(token);
        pop(s, &e);
        token = e;
    }
    printf("\n");
}


// ============= 主函数main =============
int main()
{
    // 声明一个栈s并初始化
    Stack* s = initStack();

    // 打印中缀表达式expr的形式
    printf("%s\n", expr); // x/(i-j)*y

    // 将中缀表达式expr转换成后缀表达式
    postfix(s); // xij-/y*


    free(s);



    return 0;
}