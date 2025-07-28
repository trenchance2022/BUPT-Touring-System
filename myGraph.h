#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <iostream>
#include "cJSON.h"


#define MAX_VERTEX_NUM 100
#define MAX_ATTRACTION_NUM 200
#define MAX_EDGE_NUM 300
#define MAX_FOOD_NUM 100

using namespace std;

class Foods{
public:
    string name;
    int restaurantID;
    string cuisine;
    int popularity;
};

class ArcNode {//边表结点（代表两个景点之间的道路）
public:
    int ID;//边的终点的ID
    string name;//边的终点的名字
    ArcNode *next;//指向从起点伸出的下一条边
    int length;//边的长度
    int midx;
    int midy;
    double walkCongestion;//边的步行拥挤度
    double bikeCongestion;//边的骑行拥挤度
    double electricCongestion;//边的电动车拥挤度
};

class VNode {//顶点表结点（代表一个景点）（边的起点）
public:
    string name;//景点的名字
    bool isFacility;//是否为设施
    int x;//景点的横坐标
    int y;//景点的纵坐标
    ArcNode *first;//指向第一条以该景点为起点的边
};

class ALGraph {//邻接表（代表一个景点图）
public:
    VNode vertexes[MAX_VERTEX_NUM];//顶点表（代表一个景区内所有的景点）
};

class Attraction {//景区类
public:
    string name;//景区的名字
    bool isSchool;//是否为学校
    int popularity;//景区的热度
    double rating;//景区的评分
    ALGraph graph;//景区的内部地图
    Foods foods[MAX_FOOD_NUM];//景区内的美食
};

extern Attraction attr[MAX_ATTRACTION_NUM];

void loadAttractionArray(string);//将json中保存的数据读取到景区类中的函数，参数为json文件的路径字符串
void saveAttractionArray(string);//将景区类中的数据保存到json文件中的函数，参数为json文件的路径字符串

#endif
