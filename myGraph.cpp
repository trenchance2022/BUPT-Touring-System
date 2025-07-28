#include "myGraph.h"
#include <cstring>
#include <fstream>
#include <codecvt>
#include <QFile>
#include <./json.hpp>
#include <QDebug>
using namespace std;
using json = nlohmann::json;
Attraction attr[MAX_ATTRACTION_NUM];



void loadAttractionArray(string filename) {

    // 读取json文件
    ifstream file(filename);  // 打开文件流
    if (!file.is_open()) {
        cout << "file opening error\n" << endl;
        exit(0);
    }
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // 解析json文件
    cJSON *spotArray = cJSON_Parse(data.c_str());  // 解析JSON数据
    if (!spotArray) { 
        cout << "cJSON_Parse error\n" << endl; 
        exit(0); 
    }
    int spotSize = cJSON_GetArraySize(spotArray);  // 获取JSON数组大小
    for (int i = 0; i < spotSize; i++) {
        // 解析Attraction的name和popularity属性
        cJSON *spot = cJSON_GetArrayItem(spotArray, i);  // 获取数组中的对象
        cJSON *name = cJSON_GetObjectItem(spot, "name");  // 获取name属性
        cJSON *isSchool = cJSON_GetObjectItem(spot, "isSchool");  // 获取isSchool属性
        cJSON *popularity = cJSON_GetObjectItem(spot, "popular");  // 获取popular属性
        cJSON *rating = cJSON_GetObjectItem(spot, "rating");  // 获取rating属性
        attr[i].name = name->valuestring;  // 将name属性值赋给Attraction的name
        attr[i].isSchool = isSchool->valueint;
        attr[i].popularity = popularity->valueint;  // 将popular属性值赋给Attraction的popularity
        attr[i].rating = rating->valuedouble;  // 将rating属性值赋给Attraction的rating
        //qDebug() << attr[i].name;
        // 解析Attraction的graph属性
        cJSON *builds = cJSON_GetObjectItem(spot, "builds");  // 获取builds属性
        cJSON *routes = cJSON_GetObjectItem(spot, "routes");  // 获取routes属性

        int buildsSize = cJSON_GetArraySize(builds);  // 获取builds数组大小
        for(int j = 0; j < buildsSize; j++){
            cJSON *build = cJSON_GetArrayItem(builds, j);  // 获取builds数组中的对象
            cJSON *name = cJSON_GetObjectItem(build, "name");  // 获取name属性
            cJSON *isFacility = cJSON_GetObjectItem(build, "isFacility");  // 获取isFacility属性
            cJSON *coordinates = cJSON_GetObjectItem(build, "coordinates");
            cJSON *x = cJSON_GetArrayItem(coordinates, 0);  // 获取x属性
            cJSON *y = cJSON_GetArrayItem(coordinates, 1);  // 获取y属性

            attr[i].graph.vertexes[j].name = name->valuestring;  // 设置景点的名字
            attr[i].graph.vertexes[j].isFacility = isFacility->valueint;
            attr[i].graph.vertexes[j].x = x->valueint;  // 设置景点的横坐标
            attr[i].graph.vertexes[j].y = y->valueint;  // 设置景点的纵坐标
            attr[i].graph.vertexes[j].first = NULL;  // 初始化景点的边链表
        }

        int routeSize = cJSON_GetArraySize(routes);  // 获取routes数组大小
        for (int j = 0; j < routeSize; j++) {
            cJSON *edge = cJSON_GetArrayItem(routes, j);  // 获取routes数组中的对象
            cJSON *start = cJSON_GetObjectItem(edge, "start");  // 获取start属性
            cJSON *end = cJSON_GetObjectItem(edge, "end");  // 获取end属性
            cJSON *length = cJSON_GetObjectItem(edge, "distance");  // 获取distance属性
            cJSON *walkCongestion = cJSON_GetObjectItem(edge, "walkCongestion");  // 获取walkCongestion属性
            cJSON *bikeCongestion = cJSON_GetObjectItem(edge, "bikeCongestion");  // 获取bikeCongestion属性
            cJSON *electricCongestion = cJSON_GetObjectItem(edge, "electricCongestion");  // 获取walkCongestion属性
            cJSON *start_build = cJSON_GetArrayItem(builds, start->valueint);  // 获取builds数组中对应start索引的对象
            cJSON *start_name = cJSON_GetObjectItem(start_build, "name");  // 获取start_build对象的name属性
            cJSON *end_build = cJSON_GetArrayItem(builds, end->valueint);  // 获取builds数组中对应end索引的对象
            cJSON *end_name = cJSON_GetObjectItem(end_build, "name");  // 获取end_build对象的name属性
            cJSON *mid = cJSON_GetObjectItem(edge, "midpoint");
            cJSON *midx = cJSON_GetArrayItem(mid, 0);
            cJSON *midy = cJSON_GetArrayItem(mid, 1);

            // 添加边
            ArcNode *newArc = new ArcNode;  // 创建新的边节点
            newArc->ID = start->valueint;
            newArc->name = start_name->valuestring;  // 设置边的起始节点名称
            newArc->length = length->valueint;  // 设置边的长度
            newArc->walkCongestion = walkCongestion->valuedouble;
            newArc->bikeCongestion = bikeCongestion->valuedouble;
            newArc->electricCongestion = electricCongestion->valuedouble;
            newArc->midx = midx->valueint;
            newArc->midy = midy->valueint;
            newArc->next = attr[i].graph.vertexes[end->valueint].first;  // 将边连接到目标节点的链表中
            attr[i].graph.vertexes[end->valueint].first = newArc;  // 更新目标节点的链表头

            newArc = new ArcNode;
            newArc->ID = end->valueint;
            newArc->name = end_name->valuestring;
            newArc->length = length->valueint;
            newArc->walkCongestion = walkCongestion->valuedouble;
            newArc->bikeCongestion = bikeCongestion->valuedouble;
            newArc->electricCongestion = electricCongestion->valuedouble;
            newArc->midx = midx->valueint;
            newArc->midy = midy->valueint;
            newArc->next = attr[i].graph.vertexes[start->valueint].first;
            attr[i].graph.vertexes[start->valueint].first = newArc;
        }

        cJSON *foods = cJSON_GetObjectItem(spot, "foods");
        for(int j = 0; j < cJSON_GetArraySize(foods); j++){
            cJSON *food = cJSON_GetArrayItem(foods, j);
            cJSON *name = cJSON_GetObjectItem(food, "name");
            cJSON *restaurantID = cJSON_GetObjectItem(food, "restaurantID");
            cJSON *cuisine = cJSON_GetObjectItem(food, "cuisine");
            cJSON *popularity = cJSON_GetObjectItem(food, "popularity");
            attr[i].foods[j].name = name->valuestring;
            attr[i].foods[j].restaurantID = restaurantID->valueint;
            attr[i].foods[j].cuisine = cuisine->valuestring;
            attr[i].foods[j].popularity = popularity->valueint;
        }

    }
    cJSON_Delete(spotArray);  // 释放cJSON对象内存
}


void saveAttractionArray(string filename){
    ifstream file(filename);
    if(!file){ cout << "file opening error\n" << endl; exit(0); }
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    cJSON *oldSpotArray = cJSON_Parse(data.c_str());
    if(!oldSpotArray){ cout << "cJSON_Parse error\n" << endl; exit(0); }
    cJSON *newSpotArray = cJSON_CreateArray();
    for(int i = 0; i < MAX_ATTRACTION_NUM; i++){
        if(attr[i].name == "") break;
        cJSON *newSpot = cJSON_CreateObject();
        cJSON_AddStringToObject(newSpot, "name", attr[i].name.c_str());
        cJSON_AddNumberToObject(newSpot, "popular", attr[i].popularity);
        cJSON_AddNumberToObject(newSpot, "rating", attr[i].rating);
        cJSON *oldBuilds = cJSON_GetObjectItem(cJSON_GetArrayItem(oldSpotArray, i), "builds");
        cJSON *newBuilds = cJSON_Duplicate(oldBuilds, 1);
        cJSON_AddItemToObject(newSpot, "builds", newBuilds);
        cJSON *oldRoutes = cJSON_GetObjectItem(cJSON_GetArrayItem(oldSpotArray, i), "routes");
        cJSON *newRoutes = cJSON_Duplicate(oldRoutes, 1);
        cJSON_AddItemToObject(newSpot, "routes", newRoutes);
        cJSON *oldFoods = cJSON_GetObjectItem(cJSON_GetArrayItem(oldSpotArray, i), "foods");
        cJSON *newFoods = cJSON_Duplicate(oldFoods, 1);
        cJSON_AddItemToObject(newSpot, "foods", newFoods);
        cJSON_AddItemToArray(newSpotArray, newSpot);
    }
    char* newdata = cJSON_Print(newSpotArray);
    ofstream outFile(filename);
    if(!outFile){ cout << "file opening error\n" << endl; exit(0); } 
    outFile << newdata;
    outFile.close();
    cJSON_Delete(oldSpotArray);
    cJSON_Delete(newSpotArray);
}
