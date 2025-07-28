#include "mymap.h"
#include "ui_mymap.h"

myMap::myMap(QWidget *parent, Attraction &Attr, int Index)
    : QWidget(parent)
    , ui(new Ui::myMap)
{
    ui->setupUi(this);
    m_attr = Attr;
    spotIndex = Index;
    for(int i = 0; i < 12; i++){
        placeForMult[i] = -1;
    }
    mapImg = new myLabel(this);
    for(int i = 0; i < MAX_VERTEX_NUM; i++){
        if(m_attr.graph.vertexes[i].name == ""){
            break;
        }
        ui->currPos->addItem(QString::fromStdString(m_attr.graph.vertexes[i].name));
    }
    for(int i = 0; i < MAX_VERTEX_NUM; i++){
        if(m_attr.graph.vertexes[i].name == ""){
            break;
        }
        ui->destPos->addItem(QString::fromStdString(m_attr.graph.vertexes[i].name));
    }
    if(m_attr.isSchool) {
        ui->traffic->addItem(QString("自行车"));
        trafficTool = 1;
    }
    else {
        ui->traffic->addItem(QString("电瓶车"));
        trafficTool = 2;
    }

    vector<string> cuisine;
    for (int i = 0; i < MAX_FOOD_NUM; i++) {
        if (m_attr.foods[i].name != "") {
            bool isSelected = false;
            for (int j = 0; j < cuisine.size(); j++) {
                if (exactMatch(cuisine[j], m_attr.foods[i].cuisine)) {
                    isSelected = true;
                    break;
                }
            }

            if (!isSelected) {
                cuisine.push_back(m_attr.foods[i].cuisine);
            }
        }
    }
    for (int i = 0; i < cuisine.size(); i++) {
        ui->foodKind->addItem(QString::fromStdString(cuisine[i]));
    }

    vector<int> restaurantID;

    for (int i = 0; i < MAX_FOOD_NUM; i++) {
        if (m_attr.foods[i].name != "") {

            bool isSelected = false;
            for (int j = 0; j < restaurantID.size(); j++) {
                if (restaurantID[j] == m_attr.foods[i].restaurantID) {
                    isSelected = true;
                    break;
                }
            }

            if (!isSelected) {
                restaurantID.push_back(m_attr.foods[i].restaurantID);
            }

        }
    }

    for (int i = 0; i < restaurantID.size(); i++) {
        ui->restaurant->addItem(QString::fromStdString(m_attr.graph.vertexes[restaurantID[i]].name));
        m_restaurantID.push_back(restaurantID[i]);
    }
}

myMap::~myMap()
{
    delete ui;
}

void myMap::on_backBtn_clicked()
{
    this->close();
    emit quit_function();
}


void myMap::on_routePlanBtn_clicked()
{
    if(ui->multiChk->isChecked()){
        numForMulti = 0;
        for(int i = 1; i <= 11; i++){
            if(placeForMult[i] == -1){
                numForMulti = i - 1;
                break;
            }
        }
        int tempArr[12];
        for(int i = 0; i < 12; i++){
            tempArr[i] = placeForMult[i];
        }
        if(numForMulti != 0)
        {
            switch(ui->category->currentIndex()){
            case 0:
                FloydByDist(&m_attr.graph, ui->currPos->currentIndex(), numForMulti, tempArr);
                mapImg->routePaint(m_attr, 2, ui->currPos->currentIndex(), ui->destPos->currentIndex());
                break;
            case 1:
                if(ui->traffic->currentIndex() == 0)
                    FloydByTime(&m_attr.graph, ui->currPos->currentIndex(), numForMulti, tempArr, 0);
                else
                    FloydByTime(&m_attr.graph, ui->currPos->currentIndex(), numForMulti, tempArr, trafficTool);
                mapImg->routePaint(m_attr, 2, ui->currPos->currentIndex(), ui->destPos->currentIndex());
                break;
            }
        }
    } else{
        switch(ui->category->currentIndex()){
        case 0:
            DjikstraByDist(&m_attr.graph, ui->currPos->currentIndex());
            mapImg->routePaint(m_attr, 1, ui->currPos->currentIndex(), ui->destPos->currentIndex());
            break;
        case 1:
            if(ui->traffic->currentIndex() == 0)
                DjikstraByTime(&m_attr.graph, ui->currPos->currentIndex(), 0);
            else
                DjikstraByTime(&m_attr.graph, ui->currPos->currentIndex(), trafficTool);
            mapImg->routePaint(m_attr, 1, ui->currPos->currentIndex(), ui->destPos->currentIndex());
            break;
        }
    }
}


void myMap::on_editRouteBtn_clicked()
{
    if(dlgMulti == nullptr){
        vector<QString> points;
        for(int i = 0; i < MAX_VERTEX_NUM; i++){
            if(m_attr.graph.vertexes[i].name == ""){
                break;
            }
            points.push_back(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        dlgMulti = new EditMultiPoint(this, points);
    }

    int ret = dlgMulti->exec();
    if(ret == QDialog::Accepted){
        for(int i = 0; i < 12; i++){
            placeForMult[i] = -1;
        }
        for(int i = 1; i <= 10; i++){
            placeForMult[i] = dlgMulti->way[i - 1];
        }
        ui->wayList->clear();
        for(int i = 1; i <= 10; i++){
            if(placeForMult[i] == -1) break;
            ui->wayList->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[placeForMult[i]].name));
        }
    }
}


void myMap::on_facilitySearch_clicked()
{
    int selectedBuildIndex = ui->currPos->currentIndex();
    DjikstraByDist(&m_attr.graph, selectedBuildIndex);

    vector<int> indices;
    int vertex_num = sizeof(m_attr.graph.vertexes) / sizeof(m_attr.graph.vertexes[0]);
    string userInput = ui->facilityInput->text().toStdString();
    for (int i = 0; i < vertex_num; i++) {
        if (kmpSearch(m_attr.graph.vertexes[i].name, userInput)){
            if (dist[i] > 0 && dist[i] <= 400)
            {
                indices.push_back(i);
            }
        }
    }

    quickSort(indices, 0, indices.size() - 1);

    vector<string> category;

    switch(ui->facilitySort->currentIndex()){
    case 0:
    {
        ui->facilityResult->clear();
        for(int i : indices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 1:
    {
        category.push_back("Gym");
        category.push_back("Swimming Pool");
        category.push_back("Basketball Court");
        category.push_back("Tennis Court");
        category.push_back("Badminton Court");
        category.push_back("Football Field");
        category.push_back("台球");
        category.push_back("游泳");
        category.push_back("篮球");
        category.push_back("网球");
        category.push_back("羽毛球");
        category.push_back("足球");
        category.push_back("排球");
        category.push_back("体育馆");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j]) && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 2:
    {
        category.push_back("Canteen");
        category.push_back("Coffee Shop");
        category.push_back("Cafeteria");
        category.push_back("咖啡厅");
        category.push_back("综合食堂");
        category.push_back("麦当劳");
        category.push_back("食堂");
        category.push_back("餐厅");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 3:
    {
        category.push_back("Restroom");
        category.push_back("Toilet");
        category.push_back("卫生间");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 4:
    {
        category.push_back("超市");
        category.push_back("Supermarket");
        category.push_back("Bookstore");
        category.push_back("书店");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 5:
    {
        category.push_back("图书馆");
        category.push_back("Bookstore");
        category.push_back("Library");
        category.push_back("书店");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 6:
    {
        category.push_back("医院");
        category.push_back("Hospital");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 7:
    {
        category.push_back("停车");
        category.push_back("Parking Lot");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 8:
    {
        category.push_back("公寓");
        category.push_back("Dormitory");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 9:
    {
        category.push_back("邮局");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    case 10:
    {
        category.push_back("像");
        category.push_back("喷泉");

        vector<int> newIndices;

        for (int i = 0; i < indices.size(); i++) {
            for (int j = 0; j < category.size(); j++) {
                if (kmpSearch(m_attr.graph.vertexes[indices[i]].name, category[j])  && !kmpSearch(m_attr.graph.vertexes[indices[i]].name, "十字路口")) {
                    newIndices.push_back(indices[i]);
                }
            }
        }

        quickSort(newIndices, 0, newIndices.size() - 1);

        ui->facilityResult->clear();
        for(int i : newIndices){
            ui->facilityResult->appendPlainText(QString::fromStdString(m_attr.graph.vertexes[i].name));
        }
        break;
    }
    }
}

void myMap::quickSort(vector<int> &indices, int low, int high)
{
    if (low < high) {
        int pivot = indices[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (dist[indices[j]] <= dist[pivot]) {
                i++;
                swap(indices[i], indices[j]);
            }
        }

        swap(indices[i + 1], indices[high]);
        int partitionIndex = i + 1;

        quickSort(indices, low, partitionIndex - 1);
        quickSort(indices, partitionIndex + 1, high);
    }
}

bool myMap::exactMatch(const string &text, const string &pattern)
{
    // 获取字符串长度
    size_t textLength = text.length();
    size_t patternLength = pattern.length();

    // 如果长度不相等，则不可能匹配
    if (textLength != patternLength) {
        return false;
    }

    // 逐字符比较
    for (size_t i = 0; i < textLength; ++i) {
        if (text[i] != pattern[i]) {
            return false;  // 发现不一致字符，返回false
        }
    }

    return true;  // 所有字符都匹配，返回true
}

void myMap::findPopularityTopK(vector<int> &arr, int low, int high, int k, int selectedSpotIndex, int selectedBuildIndex)
{
    if (low < high) {
        int pivotIndex = partitionPopularity(arr, low, high, selectedSpotIndex, selectedBuildIndex);

        if (pivotIndex == k) {
            // 找到第k大的数，不再递归左右两侧
            return;
        } else if (pivotIndex < k) {
            // 第k大的数在右侧
            findPopularityTopK(arr, pivotIndex + 1, high, k, selectedSpotIndex, selectedBuildIndex);
        } else {
            // 第k大的数在左侧
            findPopularityTopK(arr, low, pivotIndex - 1, k, selectedSpotIndex, selectedBuildIndex);
        }
    }
}

void myMap::quickPopularityFullSort(vector<int> &arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex)
{
    if (low < high) {
        int pivotIndex = partitionPopularity(arr, low, high, selectedSpotIndex, selectedBuildIndex);
        quickPopularityFullSort(arr, low, pivotIndex - 1, selectedSpotIndex, selectedBuildIndex);
        quickPopularityFullSort(arr, pivotIndex + 1, high, selectedSpotIndex, selectedBuildIndex);
    }
}

int myMap::partitionPopularity(vector<int> &arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (attr[selectedSpotIndex].foods[arr[j]].popularity >= attr[selectedSpotIndex].foods[pivot].popularity) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void myMap::findDistanceTopK(vector<int> &arr, int low, int high, int k, int selectedSpotIndex, int selectedBuildIndex)
{
    if (low < high) {
        int pivotIndex = partitionDistance(arr, low, high, selectedSpotIndex, selectedBuildIndex);

        if (pivotIndex == k) {
            // 找到第k小的数，不再递归左右两侧
            return;
        } else if (pivotIndex < k) {
            // 第k小的数在右侧
            findDistanceTopK(arr, pivotIndex + 1, high, k, selectedSpotIndex, selectedBuildIndex);
        } else {
            // 第k小的数在左侧
            findDistanceTopK(arr, low, pivotIndex - 1, k, selectedSpotIndex, selectedBuildIndex);
        }
    }
}

int myMap::partitionDistance(vector<int> &arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {

        if (dist[attr[selectedSpotIndex].foods[arr[j]].restaurantID] <= dist[attr[selectedSpotIndex].foods[pivot].restaurantID]) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void myMap::quickDistanceFullSort(vector<int> &arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex)
{
    if (low < high) {
        int pivotIndex = partitionDistance(arr, low, high, selectedSpotIndex, selectedBuildIndex);
        quickDistanceFullSort(arr, low, pivotIndex - 1, selectedSpotIndex, selectedBuildIndex);
        quickDistanceFullSort(arr, pivotIndex + 1, high, selectedSpotIndex, selectedBuildIndex);
    }
}

void myMap::on_foodSearch_clicked()
{
    vector<int> indices;
    string userInput = ui->foodInput->text().toStdString();
    bool found = false;
    int food_num = sizeof(m_attr.foods) / sizeof(m_attr.foods[0]);
    for (int i = 0; i < food_num; i++) {
        if (kmpSearch(m_attr.foods[i].name, userInput)){
            found = true;
            indices.push_back(i);
        }
    }
    int selectedSpotIndex = spotIndex;
    int selectedBuildIndex = ui->currPos->currentIndex();
    switch(ui->foodSort->currentIndex()){
    case 0:
        ui->foodResult->clear();
        if (!indices.empty()) {
            if (indices.size() > 10) {
                findPopularityTopK(indices, 0, indices.size() - 1, 10, selectedSpotIndex, selectedBuildIndex);
                quickPopularityFullSort(indices, 0, 9, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < 10; i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[indices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[indices[i]].restaurantID].name)));
                }
            }
            else{
                quickPopularityFullSort(indices, 0, indices.size() - 1, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < indices.size(); i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[indices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[indices[i]].restaurantID].name)));
                }
            }
        }
        break;
    case 1:
        ui->foodResult->clear();
        if (!indices.empty()) {
            if (indices.size() > 10) {
                findDistanceTopK(indices, 0, indices.size() - 1, 10, selectedSpotIndex, selectedBuildIndex);
                quickDistanceFullSort(indices, 0, 9, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < 10; i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[indices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[indices[i]].restaurantID].name)));
                }
            }
            else {
                quickDistanceFullSort(indices, 0, indices.size() - 1, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < indices.size(); i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[indices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[indices[i]].restaurantID].name)));
                }
            }
        }
        break;
    case 2:
    {
        ui->foodResult->clear();
        vector<int> newIndices;
        for (auto i : indices) {
            if (exactMatch(ui->foodKind->currentText().toStdString(), m_attr.foods[i].cuisine)) {
                newIndices.push_back(i);
            }
        }
        if (!newIndices.empty()) {
            if (newIndices.size() > 10) {
                findPopularityTopK(newIndices, 0, newIndices.size() - 1, 10, selectedSpotIndex, selectedBuildIndex);
                quickPopularityFullSort(newIndices, 0, 9, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < 10; i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[newIndices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[newIndices[i]].restaurantID].name)));
                }
            }
            else{
                quickPopularityFullSort(newIndices, 0, newIndices.size() - 1, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < newIndices.size(); i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[newIndices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[newIndices[i]].restaurantID].name)));
                }
            }
        }
        break;
    }
    case 3:
    {
        ui->foodResult->clear();
        vector<int> newIndices;
        for (auto i : indices) {
            if (m_attr.foods[i].restaurantID == m_restaurantID[ui->restaurant->currentIndex()]) {
                newIndices.push_back(i);
            }
        }
        if (!newIndices.empty()) {
            if (newIndices.size() > 10) {
                findPopularityTopK(newIndices, 0, newIndices.size() - 1, 10, selectedSpotIndex, selectedBuildIndex);
                quickPopularityFullSort(newIndices, 0, 9, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < 10; i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[newIndices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[newIndices[i]].restaurantID].name)));
                }
            }
            else{
                quickPopularityFullSort(newIndices, 0, newIndices.size() - 1, selectedSpotIndex, selectedBuildIndex);
                for (int i = 0; i < newIndices.size(); i++) {
                    ui->foodResult->appendPlainText(QString("%1：%2").arg(QString::fromStdString(m_attr.foods[newIndices[i]].name)).arg(QString::fromStdString(m_attr.graph.vertexes[m_attr.foods[newIndices[i]].restaurantID].name)));
                }
            }
        }
        break;
    }
    }
}

