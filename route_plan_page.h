#ifndef ROUTE_PLAN_PAGE_H
#define ROUTE_PLAN_PAGE_H

#include <iostream>
#include "myGraph.h"
#include "facility_search.h"

struct Coordinate {
    int x;
    int y;
    Coordinate* next;
};

void route_plan_page();
void route_plan(ALGraph*, bool);
void two_point_route_planning(ALGraph*, bool);
void DjikstraByTime(ALGraph* graph, int start, int flag);
void DjikstraByDist(ALGraph* graph, int start);
void printPath(ALGraph* graph, int start, int end);
void Multi_point_route_planning(ALGraph* graph, bool);
void FloydByDist(ALGraph* graph, int start, int num, int place[]);
void FloydByTime(ALGraph* graph, int start, int num, int place[], int flag);
int getdis(int num, int place[]);
void savpath(int place[], int num);
void getpath(int a, int b);
void site_list(ALGraph* graph);
void printMidpoint(ALGraph* graph, int start, int end);

extern int dist[MAX_VERTEX_NUM];



#endif
