#include "sys.h"
#include "stdlib.h"	 
#include <stdbool.h>

#define RIGHT 1
#define LEFT 2
#define DOWN 3
#define UP 4
extern u8 KeyValue;
void GUI_Clear(void);//界面清除
void Creat_map(void);//创建地图
void Paint_Map(int x,int y);//绘制地图点坐标
void Paint_Head(int x,int y );//绘制蛇头点坐标
void Paint_Body(int x,int y );//绘制蛇身函数
void Paint_Food(int x,int y );//绘制食物点坐标
void Paint_Clean(int x,int y);
void GUI_Refresh(void);//界面刷新
void Snake_Init(void);//蛇及地图初始化
void drawSnake(void);            //画蛇
void Get_Command(void);//获取键盘值
void Move(void);//移动
int Chek(int i,int j);//检查地图空位
void Food(void);//生成食物
bool GameOver(void);//游戏结束
void Show_Score(void);//显示分数
void Show_Endface(void);//显示界面
void Show_Interface(void);//显示界面
void initializeRandomSeed(void);

void Playing(void);
void Start(void);
