#include "diaryview.h"
#include "ui_diaryview.h"

DiaryView::DiaryView(QWidget *parent, std::vector<Diary> diaries, int id)
    : QWidget(parent)
    , ui(new Ui::DiaryView)
{
    ui->setupUi(this);
    m_diaries = diaries;
    m_id = id - 1;
    std::string title = diaries[m_id].title;
    std::string dest = diaries[m_id].destination;
    std::string content = diaries[m_id].content;
    ui->title->setText(QString::fromStdString(title));
    ui->dest->setText(QString::fromStdString(dest));
    ui->content->setPlainText(QString::fromStdString(content));
}

DiaryView::~DiaryView()
{
    delete ui;
}

void DiaryView::on_confirmBnt_clicked()
{
    int popularity = m_diaries[m_id].popularity + 1;
    double r;
    if(ui->radio5->isChecked()) r = 5;
    else if(ui->radio4->isChecked()) r = 4;
    else if(ui->radio3->isChecked()) r = 3;
    else if(ui->radio2->isChecked()) r = 2;
    else if(ui->radio1->isChecked()) r = 1;
    double rating = ((m_diaries[m_id].rating * m_diaries[m_id].popularity) + r) / popularity;

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
    file.close();


    cJSON* diaryArray = cJSON_GetObjectItem(json, "diaries");
    if (!diaryArray) {
        qDebug() << "Invalid JSON format. 'diaries' array not found.";
    }
    cJSON* entry = diaryArray->child;
    while (entry != NULL) {
        if (cJSON_GetObjectItem(entry, "ID")->valueint == m_id + 1) {
            cJSON_GetObjectItem(entry, "rating")->valuedouble = static_cast<double>(rating);
            cJSON_GetObjectItem(entry, "popularity")->valuedouble = static_cast<double>(popularity);
            break;
        }
        entry = entry->next;
    }
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    char* jsonStr = cJSON_Print(json);
    stream << jsonStr << "\n";
    file.close();
    this->close();
    emit quit_function();
}

