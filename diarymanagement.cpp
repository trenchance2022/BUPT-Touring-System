#include "diarymanagement.h"
#include "ui_diarymanagement.h"

diaryManagement::diaryManagement(QWidget *parent, std::string account) :
    QWidget(parent),
    ui(new Ui::diaryManagement)
{
    ui->setupUi(this);
    m_account = account;
    m_model = new QStringListModel(this);//存放数据的QStringListModel数据模型
    for(int i = 0; i < 10000; i++){
        itemID[i] = 0;
    }

    // 读取 JSON 文件
    QFile file("./diaries.json");
    if (!file.open(QIODevice::ReadOnly)) {//只读打开
        qDebug()<<"文件打开失败";
    }

    // 使用 cJSON 解析 JSON
    //用QTextStream将文件内容读取为QString类型
    QTextStream fs(&file);
    QString jsonContent = fs.readAll();
    json = cJSON_Parse(jsonContent.toStdString().c_str());

    diaries = parseDiariesContents(json);//将日记文件放入类的私有vector<Diary>类型变量diaries中
    for(auto i : diaries){//对每条日记，提取它的信息到一个QString中，将其按行放入数据模型，并将其ID存入自定义的第一个位置
        QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(i.title.c_str()).arg(i.destination.c_str()).arg(i.author.c_str()).arg(i.rating).arg(i.popularity);
        m_model->insertRow(m_model->rowCount());
        QModelIndex index = m_model->index(m_model->rowCount() - 1);
        m_model->setData(index, t);
        itemID[index.row()] = i.ID;
    }
    file.close();

    ui->diaryView->setModel(m_model);
    ui->diaryView->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
}

diaryManagement::~diaryManagement()
{
    delete ui;
}

void diaryManagement::on_btnSearch_clicked()//当按下搜索键触发
{
    m_model->removeRows(0, m_model->rowCount());//清空数据模型内已有的所有行
    std::vector matchedDiary = diaries;
    if(ui->diarySearch->text().isEmpty()){//不进行字符串匹配的搜索
        switch(ui->comboSort->currentIndex()){
        case 0:
            browseByNone(matchedDiary);
            break;
        case 1:
            browseByRating(matchedDiary);//按评分搜索
            break;
        case 2:
            browseByPopularity(matchedDiary);
            break;
        case 3:
            browseByInterest(matchedDiary);
            break;
        }
    } else{//需要进行字符串匹配的搜索
        switch (ui->comboMethod->currentIndex()){
        case 0:
            searchByDest();//按地点搜索
            break;
        case 1:
            searchByTitle();//按标题搜索
            break;
        case 2:
            searchByContent();//按内容搜索
            break;
        }
    }
}

std::vector<Diary> diaryManagement::parseDiariesContents(cJSON *diaries)
{
    std::vector<Diary> result;

    cJSON* diaryArray = cJSON_GetObjectItem(diaries, "diaries");
    if (!diaryArray) {
        qDebug() << "Invalid JSON format. 'diaries' array not found.";
        return result;
    }

    cJSON* entry = diaryArray->child;
    while (entry != NULL) {
        Diary diary = {
            cJSON_GetObjectItem(entry, "ID")->valueint,
            cJSON_GetObjectItem(entry, "title")->valuestring,
            cJSON_GetObjectItem(entry, "destination")->valuestring,
            cJSON_GetObjectItem(entry, "author")->valuestring,
            cJSON_GetObjectItem(entry, "rating")->valuedouble,
            cJSON_GetObjectItem(entry, "popularity")->valueint,
            decompressString(cJSON_GetObjectItem(entry, "ID")->valueint)
        };
        result.push_back(diary);
        entry = entry->next;
    }

    return result;
}

void diaryManagement::searchByDest()
{
    vector<Diary> matchedDiary;

    //黑箱部分（不懂问rzg）总之能筛选出一个字符串匹配的Dairy集合
    unordered_map<size_t, vector<Diary>> destinationHashToDiaries;
    cJSON* diariesArray = cJSON_GetObjectItem(json, "diaries");
    if (!diariesArray || !cJSON_IsArray(diariesArray)) {
        qDebug() << "JSON 格式无效";
    }
    for (int i = 0; i < cJSON_GetArraySize(diariesArray); ++i) {
        cJSON* diaryJson = cJSON_GetArrayItem(diariesArray, i);
        Diary diary = cJSONToDiary(diaryJson);
        // 对标题进行哈希并添加到哈希映射中
        size_t destinationHash = complexHashFunction(diary.destination);
        destinationHashToDiaries[destinationHash].push_back(diary);
    }

    size_t userInputHash = complexHashFunction(ui->diarySearch->text().toStdString());
    auto it = destinationHashToDiaries.find(userInputHash);

    if(it != destinationHashToDiaries.end()){
        for (const Diary& diary : it->second){
            matchedDiary.push_back(diary);
        }
    }

    switch(ui->comboSort->currentIndex()){//在进行字符串匹配的筛选后，按照排序方式进行再一次筛选
    case 0:
        browseByNone(matchedDiary);
        break;
    case 1:
        browseByRating(matchedDiary);
        break;
    case 2:
        browseByPopularity(matchedDiary);
        break;
    case 3:
        browseByInterest(matchedDiary);
        break;
    }
}

void diaryManagement::searchByTitle()
{
    vector<Diary> matchedDiary;
    unordered_map<size_t, vector<Diary>> titleHashToDiaries;
    cJSON* diariesArray = cJSON_GetObjectItem(json, "diaries");

    if (!diariesArray || !cJSON_IsArray(diariesArray)) {
        qDebug() << "JSON 格式无效";
    }

    for (int i = 0; i < cJSON_GetArraySize(diariesArray); ++i) {
        cJSON* diaryJson = cJSON_GetArrayItem(diariesArray, i);
        Diary diary = cJSONToDiary(diaryJson);

        // 对标题进行哈希并添加到哈希映射中
        size_t titleHash = complexHashFunction(diary.title);
        titleHashToDiaries[titleHash].push_back(diary);
    }

    size_t userInputHash = complexHashFunction(ui->diarySearch->text().toStdString());
    auto it = titleHashToDiaries.find(userInputHash);

    if (it != titleHashToDiaries.end()) {
        for (const Diary& diary : it->second){
            matchedDiary.push_back(diary);
        }
    }

    switch(ui->comboSort->currentIndex()){//在进行字符串匹配的筛选后，按照排序方式进行再一次筛选
    case 0:
        browseByNone(matchedDiary);
        break;
    case 1:
        browseByRating(matchedDiary);
        break;
    case 2:
        browseByPopularity(matchedDiary);
        break;
    case 3:
        browseByInterest(matchedDiary);
        break;
    }
}

void diaryManagement::searchByContent()
{
    vector<Diary> matchedDiary;

    // 遍历 diaries
    for (const Diary& diary : diaries) {
        if (kmpSearch (diary.content, ui->diarySearch->text().toStdString())){
            matchedDiary.push_back(diary);
        }
    }

    switch(ui->comboSort->currentIndex()){//在进行字符串匹配的筛选后，按照排序方式进行再一次筛选
    case 0:
        browseByNone(matchedDiary);
        break;
    case 1:
        browseByRating(matchedDiary);
        break;
    case 2:
        browseByPopularity(matchedDiary);
        break;
    case 3:
        browseByInterest(matchedDiary);
        break;
    }
}

void diaryManagement::browseByRating(std::vector<Diary> &matchedDiary)
{
    if(matchedDiary.size() < 10){//如果集合长度小于10，不需要使用findRatingTopK函数
        quickRatingSort(matchedDiary, 0, matchedDiary.size() - 1);
        for(auto i : matchedDiary){
            QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(i.title.c_str()).arg(i.destination.c_str()).arg(i.author.c_str()).arg(i.rating).arg(i.popularity);
            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, t);
            itemID[index.row()] = i.ID;
        }
    } else{//长度大于10，正常排序并挑出前十名
        findRatingTopK(matchedDiary, 0, matchedDiary.size() - 1, 10);
        quickRatingSort(matchedDiary, 0, 9);
        for(int i = 0; i < 10; i++){
            Diary temp = matchedDiary[i];
            QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(temp.title.c_str()).arg(temp.destination.c_str()).arg(temp.author.c_str()).arg(temp.rating).arg(temp.popularity);
            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, t);
            itemID[index.row()] = temp.ID;
        }
    }
}

void diaryManagement::browseByNone(std::vector<Diary> &matchedDiary)
{
    for(auto i : matchedDiary){//对每条日记，提取它的信息到一个QString中，将其按行放入数据模型，并将其ID存入自定义的第一个位置
            QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(i.title.c_str()).arg(i.destination.c_str()).arg(i.author.c_str()).arg(i.rating).arg(i.popularity);
                            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, t);
            itemID[index.row()] = i.ID;
    }
}

void diaryManagement::browseByPopularity(std::vector<Diary> matchedDiary)
{
    if(matchedDiary.size() < 10){//如果集合长度小于10，不需要使用findPopularityTopK函数
        quickPopularitySort(matchedDiary, 0, matchedDiary.size() - 1);
            for(auto i : matchedDiary){
                QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(i.title.c_str()).arg(i.destination.c_str()).arg(i.author.c_str()).arg(i.rating).arg(i.popularity);
                m_model->insertRow(m_model->rowCount());
                QModelIndex index = m_model->index(m_model->rowCount() - 1);
                m_model->setData(index, t);
                itemID[index.row()] = i.ID;
            }
    } else{//长度大于10，正常排序并挑出前十名
        findPopularityTopK(matchedDiary, 0, matchedDiary.size() - 1, 10);
        quickPopularitySort(matchedDiary, 0, 9);
        for(int i = 0; i < 10; i++){
            Diary temp = matchedDiary[i];
            QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(temp.title.c_str()).arg(temp.destination.c_str()).arg(temp.author.c_str()).arg(temp.rating).arg(temp.popularity);
            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, t);
            itemID[index.row()] = temp.ID;
        }
    }
}

void diaryManagement::browseByInterest(std::vector<Diary> sortedDiaries)
{
    vector<string> keywordsInDestination;
    vector<Diary> matchedDiaries;
    switch(ui->comboInterest->currentIndex()){
    case 0:
        keywordsInDestination.push_back("University of Technology");
        keywordsInDestination.push_back("科学与技术大学");
        break;
    case 1:
        keywordsInDestination.push_back("Academy of Fine Arts");
        keywordsInDestination.push_back("美术学院");
        break;
    case 2:
        keywordsInDestination.push_back("Normal University");
        keywordsInDestination.push_back("师范大学");
        break;
    case 3:
        keywordsInDestination.push_back("Medical University");
        keywordsInDestination.push_back("医科大学");
        break;
    case 4:
        keywordsInDestination.push_back("University of Finance");
        keywordsInDestination.push_back("财经大学");
        break;
    case 5:
        keywordsInDestination.push_back("Lake");
        keywordsInDestination.push_back("River");
        keywordsInDestination.push_back("Island");
        keywordsInDestination.push_back("湖");
        keywordsInDestination.push_back("岛");
        keywordsInDestination.push_back("河");
        break;
    case 6:
        keywordsInDestination.push_back("Mountain");
        keywordsInDestination.push_back("Cave");
        keywordsInDestination.push_back("山");
        keywordsInDestination.push_back("洞");
        break;
    case 7:
        keywordsInDestination.push_back("Park");
        keywordsInDestination.push_back("Desert");
        keywordsInDestination.push_back("公园");
        keywordsInDestination.push_back("沙漠");
    default:
            break;
    }

    matchedDiaries = findMatchedDiaries(sortedDiaries, keywordsInDestination);

    if(matchedDiaries.size() < 10){//如果集合长度小于10，不需要使用findPopularityTopK函数
        quickPopularitySort(matchedDiaries, 0, matchedDiaries.size() - 1);
        for(auto i : matchedDiaries){
            QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(i.title.c_str()).arg(i.destination.c_str()).arg(i.author.c_str()).arg(i.rating).arg(i.popularity);
                            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, t);
            itemID[index.row()] = i.ID;
        }
    } else{//长度大于10，正常排序并挑出前十名
        findPopularityTopK(matchedDiaries, 0, matchedDiaries.size() - 1, 10);
        quickPopularitySort(matchedDiaries, 0, 9);
        for(int i = 0; i < 10; i++){
            Diary temp = matchedDiaries[i];
            QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(temp.title.c_str()).arg(temp.destination.c_str()).arg(temp.author.c_str()).arg(temp.rating).arg(temp.popularity);
            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, t);
            itemID[index.row()] = temp.ID;
        }
    }
}

int diaryManagement::partitionRating(std::vector<Diary>& arr, int low, int high){
    Diary pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
            if (arr[j].rating >= pivot.rating) {
                i++;
                swap(arr[i], arr[j]);
            }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void diaryManagement::quickPopularitySort(vector<Diary> &arr, int low, int high)
{
    if (low < high) {
            int pivotIndex = partitionPopularity(arr, low, high);
            quickPopularitySort(arr, low, pivotIndex - 1);
            quickPopularitySort(arr, pivotIndex + 1, high);
    }
}

void diaryManagement::findPopularityTopK(vector<Diary> &arr, int low, int high, int k)
{
    if (low < high) {
            int pivotIndex = partitionPopularity(arr, low, high);

            if (pivotIndex == k) {
                // 找到第k大的数，不再递归左右两侧
                return;
            } else if (pivotIndex < k) {
                // 第k大的数在右侧
                findPopularityTopK(arr, pivotIndex + 1, high, k);
            } else {
                // 第k大的数在左侧
                findPopularityTopK(arr, low, pivotIndex - 1, k);
            }
    }
}

int diaryManagement::partitionPopularity(vector<Diary> &arr, int low, int high)
{
    Diary pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
            if (arr[j].popularity >= pivot.popularity) {
                i++;
                swap(arr[i], arr[j]);
            }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

vector<Diary> diaryManagement::findMatchedDiaries(const vector<Diary> &unsortedDiaries, const vector<string> &keywordsInDestination)
{
    vector<Diary> matchedDiaries;

    // 遍历 sortedDiaries
    for (const Diary& diary : unsortedDiaries) {
            // 遍历 keywordsInDestination
            if (kmpPatternMatch (keywordsInDestination, diary.destination))
                matchedDiaries.push_back(diary);
    }

    return matchedDiaries;
}

Diary diaryManagement::cJSONToDiary(const cJSON *diaryItem)
{
    Diary diary;
    diary.ID = cJSON_GetObjectItem(diaryItem, "ID")->valueint;
    diary.title = cJSON_GetObjectItem(diaryItem, "title")->valuestring;
    diary.destination = cJSON_GetObjectItem(diaryItem, "destination")->valuestring;
    diary.author = cJSON_GetObjectItem(diaryItem, "author")->valuestring;
    diary.rating = cJSON_GetObjectItem(diaryItem, "rating")->valuedouble;
    diary.popularity = cJSON_GetObjectItem(diaryItem, "popularity")->valueint;
    diary.content = "";
    return diary;
}

size_t diaryManagement::complexHashFunction(const string &str)
{
    size_t hash = 5381;
    for (char c : str) {
            hash = (hash << 5) + hash + c;
    }
    return hash;
}

void diaryManagement::quickRatingSort(std::vector<Diary>& arr, int low, int high){
    if (low < high){
        int pivotIndex = partitionRating(arr, low, high);
        quickRatingSort(arr, low, pivotIndex - 1);
        quickRatingSort(arr, pivotIndex + 1, high);
    }
}

void diaryManagement::findRatingTopK(std::vector<Diary>& arr, int low, int high, int k) {
    if (low < high){
        int pivotIndex = partitionRating(arr, low, high);

        if (pivotIndex == k) {
            // 找到第k大的数，不再递归左右两侧
            return;
        } else if (pivotIndex < k) {
            // 第k大的数在右侧
            findRatingTopK(arr, pivotIndex + 1, high, k);
        } else {
            // 第k大的数在左侧
            findRatingTopK(arr, low, pivotIndex - 1, k);
        }
    }
}



void diaryManagement::on_creatBnt_clicked()
{
    DiaryCreate *w = new DiaryCreate(nullptr, m_account);
    this->hide();
    w->show();
    connect(w, &DiaryCreate::quit_function, this, &diaryManagement::Back);
}


void diaryManagement::on_backBnt_clicked()
{
    this->close();
    emit quit_function();
}

void diaryManagement::Back()
{
    m_model->removeRows(0, m_model->rowCount());
    // 读取 JSON 文件
    QFile file("./diaries.json");
    if (!file.open(QIODevice::ReadOnly)) {//只读打开
        qDebug()<<"文件打开失败";
    }

    // 使用 cJSON 解析 JSON
    //用QTextStream将文件内容读取为QString类型
    QTextStream fs(&file);
    QString jsonContent = fs.readAll();
    json = cJSON_Parse(jsonContent.toStdString().c_str());

    diaries = parseDiariesContents(json);//将日记文件放入类的私有vector<Diary>类型变量diaries中
    for(auto i : diaries){//对每条日记，提取它的信息到一个QString中，将其按行放入数据模型，并将其ID存入自定义的第一个位置
        QString t = QString("标题：%1 地点：%2 作者：%3 评分：%4 人气：%5").arg(i.title.c_str()).arg(i.destination.c_str()).arg(i.author.c_str()).arg(i.rating).arg(i.popularity);
        m_model->insertRow(m_model->rowCount());
        QModelIndex index = m_model->index(m_model->rowCount() - 1);
        m_model->setData(index, t);
        itemID[index.row()] = i.ID;
    }
    file.close();
    this->show();
}
void diaryManagement::on_diaryView_doubleClicked(const QModelIndex &index)
{
    int id = itemID[index.row()];
    DiaryView *w = new DiaryView(nullptr, diaries, id);
    this->hide();
    w->show();
    connect(w, &DiaryView::quit_function, this, &diaryManagement::Back);
}

