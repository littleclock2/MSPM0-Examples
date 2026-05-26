#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "oled.h"  
#include "stdlib.h"
#include "delay.h"
#include "snake.h"
#define MAXLENGTH  100    //蛇的最大长度
    int map[32][12]={0};//地图大小  x,y（一个坐标为4*4个像素点）     实际按4倍尺寸放大后地图大小为128*48个像素点
    int score;            //分数
    bool eated=false;      //蛇吃到食物的标记
    u8 KeyValue=0;        //获取按键值
    struct {       
    int snake_Grid[MAXLENGTH][2];      //二维数组，行坐标表示蛇节点，列表示当前节点的x，y坐标
    int length;    //蛇的长度
    int direction;//蛇的方向
}snake;                          //定义结构体变量snake

int tailX, tailY; 
int FoodX, FoodY;

//创建地图函数
void Creat_map()//创建地图
{
	int i,j;
	for(i=0;i<12;i++)
	{
		for(j=0;j<32;j++)
		{
  		 if(i==0||i==11)
		 {
		   map[j][i]=-2;
		 }
		 if(j==0||j==31)
		 {
		   map[j][i]=-2;
		 }
		}
	}
}

//绘制地图函数
void Paint_Map(int x,int y)//绘制地图点坐标
{
	int i,j;
	for(i=4*y;i<4*y+4;i++)     
	{
	  for(j=4*x;j<4*x+4;j++)
	  {
		    OLED_DrawPoint(j,i+16); 
	  }
	
	}

}

//绘制蛇头函数
void Paint_Head(int x,int y )//绘制蛇头点坐标
{
	int i,j;
	for(i=4*y;i<4*y+4;i++)     
	{
	  for(j=4*x;j<4*x+4;j++)
	  {
		if(i==4*y||i==4*y+3)
		{
			
			 OLED_DrawPoint(j,i+16);  
			
		}
		if(j==4*x||j==4*x+3)
		{
			
			 OLED_DrawPoint(j,i+16);  
		
		}
	  }
    }
}

//绘制蛇身函数
void Paint_Body(int x,int y )//绘制蛇身函数
{
	int i,j;
	for(i=4*y;i<4*y+4;i++)     
	{
	  for(j=4*x;j<4*x+4;j++)
	  {
		if(i==4*y||i==4*y+3)
		{
			
			 OLED_DrawPoint(j,i+16);  
			
		}
		if(j==4*x||j==4*x+3)
		{
			
			 OLED_DrawPoint(j,i+16);  
		
		}
	  }
    }
}

//绘制食物坐标函数
void Paint_Food(int x,int y )//绘制食物点坐标
{
	int i,j;
	for(i=4*y;i<4*y+4;i++)     
	{
	  for(j=4*x;j<4*x+4;j++)
	  {
		
	   if(i==4*y+1||i==4*y+2)
		{
			
			 OLED_DrawPoint(j,i+16);  
			
		}
	   if(j==4*x+1||j==4*x+2)
		{
			
			 OLED_DrawPoint(j,i+16); 
		
		} 
	  }
	
	}
    // 更新食物的坐标
    FoodX = x;
    FoodY = y;
}

void Paint_Clean(int x,int y)//取消地图点坐标
{
	int i,j;
	for(i=4*y;i<4*y+4;i++)     
	{
	  for(j=4*x;j<4*x+4;j++)
	  {
		    OLED_DrawNoPoint(j,i+16); 
	  }
	
	}

}
//清除界面函数
void GUI_Clear()//界面清除
{
   int i,j;
	for(i=0;i<32;i++)
	{
		for(j=0;j<12;j++)
		{
          map[i][j]=0; 
		}
	}
}


//刷新界面函数：根据map数组里面的值一次性刷新游戏界面内的点坐标
void GUI_Refresh()//界面刷新
{
	int i,j,temp;
	for(i=0;i<32;i++)                 
	{
		for(j=0;j<12;j++)
		{
		   temp=map[i][j];
         switch (temp)
		 {
			 case 2:	      
			   Paint_Body(i,j);  
		          break;
			 case  1:		   
		       Paint_Head(i,j);  
		          break;
			 case -2:		   
		       Paint_Map(i,j);  
		          break;
			 case-1:		   
		       Paint_Food(i,j);  
		          break;
			 case 0:		   
		       Paint_Clean(i,j);
		    	  break;
	   }		   
		}
	}
//	OLED_Refresh_Gram();
	
}

//初始化蛇和地图函数：初定蛇长度为5、方向向右、蛇头坐标位于（7，5）
void Snake_Init()//蛇及地图初始化
{  
	int i;
   snake.length=5;
   snake.direction=RIGHT;
   score=0;
   snake.snake_Grid[0][0]=7;//x坐标,蛇头坐标
   snake.snake_Grid[0][1]=5;//y坐标,蛇头坐标
   tailX = snake.snake_Grid[snake.length - 1][0]; // Initialize tail coordinates
   tailY = snake.snake_Grid[snake.length - 1][1];
   for(i=1;i<snake.length;i++)
    {
        snake.snake_Grid[i][0]=snake.snake_Grid[0][0]-i;
        snake.snake_Grid[i][1]=snake.snake_Grid[0][1];  //给刚开始的蛇身几个初始坐标
    }
    Creat_map();
}

//画蛇函数：将二维数组snake.snake_Grid里面的各个蛇坐标的值存入map数组
void drawSnake()            //画蛇
{
    int i,x,y;
	//蛇头
		x=snake.snake_Grid[0][0];
		y=snake.snake_Grid[0][1];
        map[x][y]=1; 
    //蛇身
	for(i=1;i<snake.length;i++)
    {
		x=snake.snake_Grid[i][0];
		y=snake.snake_Grid[i][1];
        map[x][y]=2;       
    }

}

//按键处理函数：自定义矩形键盘值控制蛇的方向
void Get_Command()//获取键盘值
{
	u8 key=1;
	key=KeyValue;	
		switch(key)
		{
			case 1:if(snake.direction!=RIGHT)         //左
                   snake.direction=LEFT;			
                   break;
			case 2:if(snake.direction!=LEFT)           //右
                   snake.direction=RIGHT;			
                   break;
			case 3:if(snake.direction!=DOWN)        //上
                   snake.direction=UP;
                   break;
			case 4:if(snake.direction!=UP)         //下
                   snake.direction=DOWN;
                   break;		
		}    
}

//蛇的移动函数：蛇身移动就让其坐标等于前一个坐标的值，蛇头则根据蛇的方向就行移动
void Move() {
    int i;
    int headX = snake.snake_Grid[0][0];
    int headY = snake.snake_Grid[0][1];
    tailX = snake.snake_Grid[snake.length - 1][0]; // 存储当前尾巴的坐标
    tailY = snake.snake_Grid[snake.length - 1][1];
    // 判断蛇头是否与食物坐标重合
    if (headX == FoodX && headY == FoodY) {
        snake.length++;
        eated = true;  // 设置为true，表示吃到了食物
        score += 1;
        
        Food(); // 生成新的食物
    } else {
        map[tailX][tailY] = 0; // 清除尾巴
    }

    for (i = snake.length - 1; i > 0; i--) {
        snake.snake_Grid[i][0] = snake.snake_Grid[i - 1][0];
        snake.snake_Grid[i][1] = snake.snake_Grid[i - 1][1];
    }

    switch (snake.direction) {
        case UP:
            snake.snake_Grid[0][1]--;
            break;
        case DOWN:
            snake.snake_Grid[0][1]++;
            break;
        case LEFT:
            snake.snake_Grid[0][0]--;
            break;
        case RIGHT:
            snake.snake_Grid[0][0]++;
            break;
    }

    drawSnake();
}


//生成食物函数：在游戏界面内空位生成食物点坐标，并将食物坐标存入map数组
int Chek(int i,int j)//检查地图空位
{
	if(map[i][j]!=0)
	{
		return 0;
	}
	return 1;   //是空位就返回1
}



void Food()//生成食物
{
    int n;
	int i,j;
	do
	{
        srand(n);
		i=(rand()%30)+1;                 //生成1~30之间的一个数
        j=(rand()%10)+1;                 //生成1~10之间的一个数
        n++;
	
	}
	while(Chek(i,j)==0);                //检查该点是否为空位
	map[i][j]=-1;//画出食物
}

bool GameOver()//游戏结束
{
	bool isGameOver=false;
	int sx=snake.snake_Grid[0][0],sy=snake.snake_Grid[0][1],i;//蛇头坐标
	for(i=1; i<snake.length; i++)    //判断有没有吃到自己
    {
        if(snake.snake_Grid[i][0]==sx&&snake.snake_Grid[i][1]==sy)
            isGameOver=true;
    }
	if(snake.snake_Grid[0][0]==31||snake.snake_Grid[0][0]==0|| \
		snake.snake_Grid[0][1]==11||snake.snake_Grid[0][1]==0)        //判断有没有撞墙
		isGameOver=true;
    return isGameOver;
}

//显示分数
void Show_Score()//显示分数
{
	OLED_ShowString(30,6,"Score:",16);
	OLED_ShowNum(80,6,score,2,16);

}

void Show_Endface(){
    GUI_Clear();
    GUI_Refresh();//更新显示
    OLED_Refresh();
    OLED_ShowCHinese(0,2,9);//贪
    OLED_ShowCHinese(16,2,10);//吃
    OLED_ShowCHinese(32,2,11);//蛇
    OLED_ShowCHinese(48,2,12);//小
    OLED_ShowCHinese(64,2,13);//游
    OLED_ShowCHinese(80,2,14);//戏
    OLED_ShowChar(44,5,45,16);//'-'
    OLED_ShowChar(52,5,45,16);//'-'
    OLED_ShowChar(60,5,84,16);//'T'
    OLED_ShowChar(68,5,67,16);//'C'
    OLED_ShowCHinese(76,5,15);//实
    OLED_ShowCHinese(92,5,16);//验
    OLED_ShowCHinese(108,5,17);//室
}

void Show_Interface(void){
    GUI_Clear();
    GUI_Refresh();//更新显示
    OLED_Refresh();
    OLED_ShowCHinese(16,1,9);//贪
    OLED_ShowCHinese(32,1,10);//吃
    OLED_ShowCHinese(48,1,11);//蛇
    OLED_ShowCHinese(64,1,12);//小
    OLED_ShowCHinese(80,1,13);//游
    OLED_ShowCHinese(96,1,14);//戏
    OLED_ShowCHinese(0,5,0);//按
    OLED_ShowCHinese(16,5,1);//任
    OLED_ShowCHinese(32,5,2);//意
    OLED_ShowCHinese(48,5,3);//方
    OLED_ShowCHinese(64,5,4);//向
    OLED_ShowCHinese(80,5,5);//键
    OLED_ShowCHinese(96,5,6);//开
    OLED_ShowCHinese(112,5,7);//始
}

void Start(){
    GUI_Clear();
    Snake_Init();//    Creat_map();
    drawSnake();
    GUI_Refresh();
	Show_Score();
}

void Playing(){
    int i=1;
    Food();
    while(i){       
        Get_Command();//得到键值
        Move();//蛇移动
        if(GameOver()){//判断是否结束
            i=0;
            GUI_Clear();
            GUI_Refresh();//更新显示
            OLED_Refresh();
            OLED_ShowString(30,2,"Score:",16);
            OLED_ShowNum(80,2,score,2,16);
            break;
        }
        
        GUI_Refresh();//更新显示
        OLED_Refresh();
        Show_Score();
        delay_ms(500);
    }
}
