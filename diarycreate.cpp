#include "diarycreate.h"
#include "ui_diarycreate.h"

DiaryCreate::DiaryCreate(QWidget *parent, std::string account)
    : QWidget(parent)
    , ui(new Ui::DiaryCreate)
{
    ui->setupUi(this);
    m_account = account;
}

DiaryCreate::~DiaryCreate()
{
    delete ui;
}

void DiaryCreate::on_cancel_clicked()
{
    this->close();
    emit quit_function();
}


void DiaryCreate::on_confirm_clicked()
{
    // 读取 JSON 文件
    QFile file("./diaries.json");
    if (!file.open(QIODevice::ReadOnly)) {//只读打开
        qDebug()<<"文件打开失败";
    }
    // 使用 cJSON 解析 JSON
    //用QTextStream将文件内容读取为QString类型
    QTextStream fs(&file);
    QString jsonContent = fs.readAll();
    cJSON* json = cJSON_Parse(jsonContent.toStdString().c_str());
    std::vector<Diary> diaries = parseDiariesContents(json);

    Diary newDiary;
    newDiary.ID = diaries.size() + 1;
    newDiary.author = m_account;
    newDiary.rating = 0.00;
    newDiary.popularity = 0;
    newDiary.content = "";

    newDiary.title = ui->title->text().toStdString();
    newDiary.destination = ui->dest->text().toStdString();

    compressString(ui->content->toPlainText().toStdString(), newDiary.ID);
    saveDiary(newDiary);
    this->close();
    emit quit_function();
}

std::vector<Diary> DiaryCreate::parseDiariesContents(cJSON *diaries)
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

void DiaryCreate::saveDiary(const Diary& diary) {
    QFile file("./diaries.json");
    cJSON* root = cJSON_Parse("{}");

    // Read existing entries from the file
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream fs(&file);
        QString jsonContent = fs.readAll();
        cJSON* existingDiaries = cJSON_Parse(jsonContent.toStdString().c_str());

        if (existingDiaries) {
            cJSON* existingArray = cJSON_GetObjectItem(existingDiaries, "diaries");
            if (existingArray) {
                // Add existing entries to the new JSON object
                cJSON_AddItemToObject(root, "diaries", cJSON_Duplicate(existingArray, true));
            }

            cJSON_Delete(existingDiaries);
        }

        file.close();
    }

    // Add the new entry to the JSON object
    cJSON* newDiary = cJSON_CreateObject();
    cJSON_AddItemToObject(newDiary, "title", cJSON_CreateString(diary.title.c_str()));
    cJSON_AddItemToObject(newDiary, "ID", cJSON_CreateNumber(diary.ID));
    cJSON_AddItemToObject(newDiary, "destination", cJSON_CreateString(diary.destination.c_str()));
    cJSON_AddItemToObject(newDiary, "author", cJSON_CreateString(diary.author.c_str()));
    cJSON_AddItemToObject(newDiary, "rating", cJSON_CreateNumber(diary.rating));
    cJSON_AddItemToObject(newDiary, "popularity", cJSON_CreateNumber(diary.popularity));
    cJSON_AddItemToObject(newDiary, "content", cJSON_CreateString(diary.content.c_str()));

    // Add the new entry to the "diaries" array
    cJSON* diariesArray = cJSON_GetObjectItem(root, "diaries");
    if (!diariesArray) {
        diariesArray = cJSON_AddArrayToObject(root, "diaries");
    }
    cJSON_AddItemToArray(diariesArray, newDiary);

    // Convert the JSON structure to a string
    char* jsonStr = cJSON_Print(root);

    // Write the JSON string to the file

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << jsonStr << "\n";
        file.close();
    }

    // Clean up memory
    free(jsonStr);
    cJSON_Delete(root);
}
