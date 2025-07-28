#include "route_plan.h"
#include <QDebug>
#include <QString>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

static bool visited[MAX_VERTEX_NUM];
int prevNode[MAX_VERTEX_NUM];
int dist[MAX_VERTEX_NUM];
double timelen[MAX_VERTEX_NUM];

static int m_dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
static int m_prevNode[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
static double m_timelen[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int anspath[MAX_VERTEX_NUM];
int idx;

void Multi_point_route_planning(ALGraph* graph, bool isSchool){
    int start, num;
    int place[12];
    bool state = true;
    while(state){
        cout << "Please enter your location:\n"
             << "ID:";
        cin >> start;
        if(start < 0 || start >= MAX_VERTEX_NUM){
            cout << "Invalid ID. Please try again." << endl;
            continue;
        }
        cout << "Please enter the number of place you want to visit: (no more than 10)\n"
             << "Number: ";
        cin >> num;
        if(num < 0 || num > 10){
            cout << "Invalid number. Please try again." << endl;
            continue;
        }
        cout << "Please enter the ID of the place you want to visit:\n";
        for(int i = 1; i <= num; i++){
            cout << "place" << i << " ID: ";
            cin >> place[i];
            if(place[i] < 0 || place[i] >= MAX_VERTEX_NUM || place[i] == start){
                cout << "Invalid ID. Please try again." << endl;
                i--;
                continue;
            }
        }
        state = false;
    }

    cout << "Shortest distance or shortest time?" << endl;
    cout << "a. Shortest distance\n"
         << "b. Shortest time\n"
         << "Enter your choice: ";
    state = true;
    while(state){
        char choice;
        cin >> choice;
        switch (choice) {
            case 'a':
                FloydByDist(graph, start, num, place);
                break;
            case 'b':
                if(isSchool){
                    cout << "Whether to use bike? (y/n)" << endl;
                    char choice;
                    cin >> choice;
                    if(choice == 'y'){
                        FloydByTime(graph, start, num, place, 1);
                    } else{
                        FloydByTime(graph, start, num, place, 0);
                    }
                } else{
                    cout << "Whether to use electric car? (y/n)" << endl;
                    char choice;
                    cin >> choice;
                    if(choice == 'y'){
                        FloydByTime(graph, start, num, place, 2);
                    } else{
                        FloydByTime(graph, start, num, place, 0);
                    }
                }
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        state = false;
    }
}

void FloydByDist(ALGraph* graph, int start, int num, int place[]){
    //初始化m_dist和m_path数组
    for(int i = 0; i < MAX_VERTEX_NUM; i++){
        for(int j = 0; j < MAX_VERTEX_NUM; j++){
            if(i == j) m_dist[i][j] = 0;
            else m_dist[i][j] = INF;
            m_prevNode[i][j] = -1;
        }
    }

    // 初始化图的权重
    for(int i = 0; i < MAX_VERTEX_NUM; i++){
        ArcNode* p = graph->vertexes[i].first;
        while(p){
            m_dist[i][p->ID] = p->length;
            m_prevNode[i][p->ID] = i;
            p = p->next;
        }
    }

    // Floyd-Warshall算法主体
    for(int k = 0; k < MAX_VERTEX_NUM; k++){
        for(int i = 0; i < MAX_VERTEX_NUM; i++){
            for(int j = 0; j < MAX_VERTEX_NUM; j++){
                if(m_dist[i][k] != INF && m_dist[k][j] != INF && m_dist[i][j] > m_dist[i][k] + m_dist[k][j]){
                    m_dist[i][j] = m_dist[i][k] + m_dist[k][j];
                    m_prevNode[i][j] = m_prevNode[k][j];
                }
            }
        }
    }

    if(m_dist[start][place[1]] == INF){
        cout << "There's no path from " << graph->vertexes[start].name << " to " << graph->vertexes[place[1]].name << endl;
        return;
    }

    //升序排序place数组
    for(int i = 1; i <= num; i++){
        for(int j = i + 1; j <= num; j++){
            if(place[i] > place[j]){
                int temp = place[i];
                place[i] = place[j];
                place[j] = temp;
            }
        }
    }

    place[0] = start;
    place[num + 1] = start;

    int min_dist = INF;
    do {
        int d = getdis(num, place);
        if (min_dist > d) {//如果存在更短的路径则更新答案，并把路径存到anspath[]
            min_dist = d;
            idx = 0;
            savpath(place, num);
        }
    } while (next_permutation(place + 1, place + num + 1));

    cout << "The shortest distance is " << min_dist << endl;
    cout << "The shortest path is: ";
    for (int i = 0; i < idx - 1; i++) {
        qDebug() << QString::fromStdString(graph->vertexes[anspath[i]].name + "->");
    }
    qDebug() << QString::fromStdString(graph->vertexes[anspath[idx - 1]].name);
}

void FloydByTime(ALGraph* graph, int start, int num, int place[], int flag){
    //初始化m_dist和m_path数组
    for(int i = 0; i < MAX_VERTEX_NUM; i++){
        for(int j = 0; j < MAX_VERTEX_NUM; j++){
            if(i == j) {
                m_dist[i][j] = 0;
                m_timelen[i][j] = 0;
            }
            else {
                m_dist[i][j] = INF;
                m_timelen[i][j] = INF;
            }
            m_prevNode[i][j] = -1;
        }
    }

    // 初始化图的权重
    for(int i = 0; i < MAX_VERTEX_NUM; i++){
        ArcNode* p = graph->vertexes[i].first;
        while(p){
            m_dist[i][p->ID] = p->length;
            double congestion;
            double walkCongestion = p->walkCongestion;
            if(flag == 1){
                congestion = p->bikeCongestion;
            } else if(flag == 2){
                congestion = p->electricCongestion;
            } else if(flag == 0){
                congestion = p->walkCongestion;
            }
            double congestionUsed;
            if(congestion + 1 > 1) congestionUsed = congestion < walkCongestion ? congestion : walkCongestion;
            else congestionUsed = walkCongestion;
            m_timelen[i][p->ID] = p->length * congestionUsed;
            m_prevNode[i][p->ID] = i;
            p = p->next;
        }
    }

    // Floyd-Warshall算法主体
    for(int k = 0; k < MAX_VERTEX_NUM; k++){
        for(int i = 0; i < MAX_VERTEX_NUM; i++){
            for(int j = 0; j < MAX_VERTEX_NUM; j++){
                if(m_timelen[i][k] != INF && m_timelen[k][j] != INF && m_timelen[i][j] > m_timelen[i][k] + m_timelen[k][j]){
                    m_dist[i][j] = m_dist[i][k] + m_dist[k][j];
                    m_timelen[i][j] = m_timelen[i][k] + m_timelen[k][j];
                    m_prevNode[i][j] = m_prevNode[k][j];
                }
            }
        }
    }

    if(m_dist[start][place[1]] == INF){
        cout << "There's no path from " << graph->vertexes[start].name << " to " << graph->vertexes[place[1]].name << endl;
        return;
    }

    //升序排序place数组
    for(int i = 1; i <= num; i++){
        for(int j = i + 1; j <= num; j++){
            if(place[i] > place[j]){
                int temp = place[i];
                place[i] = place[j];
                place[j] = temp;
            }
        }
    }

    place[0] = start;
    place[num + 1] = start;

    int min_dist = INF;
    double min_timelen = INF;
    do {
        double d = gettimelen(num, place);
        if (min_timelen > d) {//如果存在更短的路径则更新答案，并把路径存到anspath[]
            min_timelen = d;
            idx = 0;
            savpath(place, num);
        }
    } while (next_permutation(place + 1, place + num + 1));

    cout << "The shortest time is " << min_timelen << endl;
    cout << "The shortest path is: ";
    for (int i = 0; i < idx - 1; i++) {
        qDebug() << QString::fromStdString(graph->vertexes[anspath[i]].name + "->");
    }
    qDebug() << QString::fromStdString(graph->vertexes[anspath[idx - 1]].name);
}

int getdis(int num, int place[]){
    int distance = m_dist[place[0]][place[1]];
    if (m_dist[place[0]][place[1]] == INF)
        return INF + 1;
    for (int i = 1; i < num; i++) {
        if (m_dist[place[i]][place[i + 1]] == INF)
            return INF + 1;
        distance += m_dist[place[i]][place[i + 1]];
    }
    if (m_dist[place[num]][num + 1] == INF)
        return INF + 1;
    distance += m_dist[place[num]][num + 1];
    return distance;
}

int gettimelen(int num, int place[]){
    int timelen = m_timelen[place[0]][place[1]];
    if (m_timelen[place[0]][place[1]] == INF)
        return INF + 1;
    for (int i = 1; i < num; i++) {
        if (m_timelen[place[i]][place[i + 1]] == INF)
            return INF + 1;
        timelen += m_timelen[place[i]][place[i + 1]];
    }
    if (m_timelen[place[num]][num + 1] == INF)
        return INF + 1;
    timelen += m_timelen[place[num]][num + 1];
    return timelen;
}


void savpath(int place[], int num){
    for(int i = 0; i <= num; i++){
        getpath(place[i], place[i + 1]);
    }
    anspath[idx++] = place[num + 1];
}

void getpath(int start, int end){
    if (start == end) {
        return;
    }
    getpath(start, m_prevNode[start][end]);
    anspath[idx++] = m_prevNode[start][end];
}

void two_point_route_planning(ALGraph* graph, bool isSchool){
    int start, end;
    bool state = true;
    while(state){
        cout << "Please enter the ID of the start place:\n"
             << "ID:";
        cin >> start;
        if(start < 0 || start >= MAX_VERTEX_NUM){
            cout << "Invalid ID. Please try again." << endl;
            continue;
        }
        cout << "Please enter the ID of the end place:\n"
             << "ID:";
        cin >> end;
        if(end < 0 || end >= MAX_VERTEX_NUM){
            cout << "Invalid ID. Please try again." << endl;
            continue;
        }
        state = false;
    }
    cout << "Start: " << graph->vertexes[start].name << endl;
    cout << "End: " << graph->vertexes[end].name << endl;
    cout << "Shortest distance or shortest time?" << endl;
    cout << "a. Shortest distance\n"
         << "b. Shortest time\n"
         << "Enter your choice: ";
    state = true;
    while(state){
        char choice;
        cin >> choice;
        switch (choice) {
            case 'a':
                DjikstraByDist(graph, start);
                cout << "The shortest distance path from " << graph->vertexes[start].name << " to " << graph->vertexes[end].name << " is " << dist[end] << endl;
                break;
            case 'b':
                if(isSchool){
                    cout << "Whether to use bike? (y/n)" << endl;
                    char choice;
                    cin >> choice;
                    if(choice == 'y'){
                        DjikstraByTime(graph, start, 1);
                    } else{
                        DjikstraByTime(graph, start, 0);
                    }
                } else{
                    cout << "Whether to use electric car? (y/n)" << endl;
                    char choice;
                    cin >> choice;
                    if(choice == 'y'){
                        DjikstraByTime(graph, start, 2);
                    } else{
                        DjikstraByTime(graph, start, 0);
                    }
                }
                cout << "The shortest time to go from " << graph->vertexes[start].name << " to " << graph->vertexes[end].name << " is " << timelen[end] << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        state = false;
    }
    
    //打印最短路径
    printPath(graph, start, end);

    cout << "" << endl;

    //打印所有路径点和中间点
    printMidpoint(graph, start, end);

    cout << endl;
}

void DjikstraByTime(ALGraph* graph, int start, int flag) {
    //初始化visited数组
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        visited[i] = false;
    }

    //初始化dist数组
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        dist[i] = INT_MAX;
        timelen[i] = INT_MAX;
    }
    dist[start] = 0;
    timelen[start] = 0;

    //初始化prev数组
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        prevNode[i] = -1;
    }

    // 主循环
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        // 找到未访问的最近节点
        double minDist = INT_MAX;
        int minIndex = -1;
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            if (!visited[j] && timelen[j] < minDist) {
                minDist = timelen[j];
                minIndex = j;
            }
        }

        // 如果没有找到未访问的节点，跳过当前迭代
        if (minIndex == -1) {
            continue;
        }

        // 标记为已访问
        visited[minIndex] = true;

        double congestion;
        double walkCongestion = graph->vertexes[minIndex].first->walkCongestion;
        if(flag == 1){
            congestion = graph->vertexes[minIndex].first->bikeCongestion;
        } else if(flag == 2){
            congestion = graph->vertexes[minIndex].first->electricCongestion;
        } else if(flag == 0){
            congestion = graph->vertexes[minIndex].first->walkCongestion;
        }

        // 更新邻居节点的距离
        for (ArcNode* p = graph->vertexes[minIndex].first; p; p = p->next) {
            double congestionUsed;
            if(congestion + 1 > 1) congestionUsed = congestion < walkCongestion ? congestion : walkCongestion;
            else congestionUsed = walkCongestion;
            if (!visited[p->ID] && timelen[minIndex] + p->length * congestionUsed < timelen[p->ID]) {
                timelen[p->ID] = timelen[minIndex] + p->length * congestionUsed;
                dist[p->ID] = dist[minIndex] + p->length;
                prevNode[p->ID] = minIndex;
            }
        }
    }
}

void DjikstraByDist(ALGraph* graph, int start) {
    //初始化visited数组
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        visited[i] = false;
    }

    //初始化dist数组
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    //初始化prev数组
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        prevNode[i] = -1;
    }

    // 主循环
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        // 找到未访问的最近节点
        int minDist = INT_MAX;
        int minIndex = -1;
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }

        // 如果没有找到未访问的节点，跳过当前迭代
        if (minIndex == -1) {
            continue;
        }

        // 标记为已访问
        visited[minIndex] = true;

        // 更新邻居节点的距离
        for (ArcNode* p = graph->vertexes[minIndex].first; p; p = p->next) {
            if (!visited[p->ID] && dist[minIndex] + p->length < dist[p->ID]) {
                dist[p->ID] = dist[minIndex] + p->length;
                prevNode[p->ID] = minIndex;
            }
        }
    }
}

void printPath(ALGraph* graph, int start, int end) {
    if (start == end) {
        cout << "Path:";
        cout << graph->vertexes[start].name;
        return;
    }
    if (prevNode[end] == -1) {
        cout << "No path from " << graph->vertexes[start].name << " to " << graph->vertexes[end].name << endl;
        return;
    }
    printPath(graph, start, prevNode[end]);
    cout << " -> " << graph->vertexes[end].name;
}


void site_list(ALGraph* graph) {
    cout << "The list of facilities and IDs:\n";
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertexes[i].name == "") {
            break;
        }
        cout << "ID: " << i << " Name: " << graph->vertexes[i].name << endl;
    }
}

void printMidpoint(ALGraph* graph, int start, int end) {
    Coordinate* head = nullptr;

    while (start != end) {
        Coordinate* newCoord = new Coordinate;
        newCoord->x = graph->vertexes[end].x;
        newCoord->y = graph->vertexes[end].y;
        newCoord->next = head;
        head = newCoord;

        ArcNode* Arc = graph->vertexes[end].first;
        while (Arc->ID != prevNode[end]) {
            Arc = Arc->next;
        }

        newCoord = new Coordinate;
        newCoord->x = Arc->midx;
        newCoord->y = Arc->midy;
        newCoord->next = head;
        head = newCoord;

        end = prevNode[end];
    }

    Coordinate* newCoord = new Coordinate;
    newCoord->x = graph->vertexes[start].x;
    newCoord->y = graph->vertexes[start].y;
    newCoord->next = head;
    head = newCoord;

    cout << "The list of all the points and midpoints:\n";
    Coordinate* current = head;
    while (current != nullptr) {
        cout << " (" << current->x << ", " << current->y << ") ";
        current = current->next;
    }
}
