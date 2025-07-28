#include "destinationrecommend.h"
#include "ui_destinationrecommend.h"
#include "QMessageBox"
#include "QInputDialog"
#include <QStandardItemModel>
#include <QDebug>
QStringList items;

destinationRecommend::destinationRecommend(QWidget *parent,std::string account)
    : QWidget(parent)
    , ui(new Ui::destinationRecommend)
{
    ui->setupUi(this);


}

destinationRecommend::~destinationRecommend()
{
    delete ui;
}

void destinationRecommend::on_pushButton_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        recommend_mode();

        break;
    case 1:
        search_mode();
        break;


    }
}
void destinationRecommend::recommend_mode() {
    vector<string> category;
    switch (ui->comboBox_3->currentIndex()) {
    case 0:
        category.push_back("University");
        category.push_back("Academy");

        category.push_back("大学");
        category.push_back("学院");

        break;

    case 1:
        category.push_back("Park");
        category.push_back("公园");
        category.push_back("Beach");
        category.push_back("海滩");

        break;

    case 2:
        category.push_back("Cave");
        category.push_back("洞穴");
        category.push_back("Desert");
        category.push_back("沙漠");


        break;
    }
    vector<int> indices;
    int attr_num = sizeof(attr) / sizeof(attr[0]);
    for (int i = 0; i < attr_num; i++) {
        for (int j = 0; j < category.size(); j++) {
            if (kmpSearch(attr[i].name, category[j])) {
                indices.push_back(i);
                //qDebug()<<"ok";
            }
        }
    }
    switch (ui->comboBox_2->currentIndex())
    {
    case 0:
        // 按照热度排序TOP10
        sortAndPrintPopTop10(indices);
        break;
    case 1:
        // 按照评分排序TOP10
        sortAndPrintRateTop10(indices);
        break;
    }
}
void destinationRecommend::sortAndPrintPopTop10(vector<int>& indices) {
    if(indices.size() >= 10) findPopularityTopK(indices, 0, indices.size() - 1, 10);
    if(indices.size() < 10) quickPopularityFullSort(indices, 0, indices.size() - 1);
    else quickPopularityFullSort(indices, 0, 9);
    m_model = new QStringListModel(this);
    int count;
    if(indices.size() >= 10) count = 10;
    else count = indices.size();
    if (!indices.empty()) {
        for (int i = 0; i < count; i++) {

            // 获取索引对应的 Attraction 实例
            const Attraction &attraction = attr[indices[i]];
            qDebug()<<attr[indices[i]].name;
            // 创建一个字符串来存储 Attraction 的信息
            QString info = QString("Name: %1, Popularity: %2, Rating: %3")
                               .arg(QString::fromStdString(attraction.name))
                               .arg(attraction.popularity)
                               .arg(attraction.rating);
            // 创建一个 QStandardItem 来存储信息字符串
            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, info);
            attrIndex[index.row()] = indices[i];
        }
        ui->listView->setModel(m_model);
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }

    else {
        QStringList stringList;
        stringList<< "No matched result.\n";
        ui->listView->setModel(new QStringListModel(stringList));
    }



}
void destinationRecommend::sortAndPrintRateTop10(vector<int>& indices) {
    if(indices.size() >= 10) findRatingTopK(indices, 0, indices.size() - 1, 10);
    if(indices.size() < 10) quickRatingFullSort(indices, 0, indices.size() - 1);
    else quickRatingFullSort(indices, 0, 9);

    m_model = new QStringListModel(this);
    int count;
    if(indices.size() >= 10) count = 10;
    else count = indices.size();
    if (!indices.empty()) {
        for (int i = 0; i < count; i++) {

            // 获取索引对应的 Attraction 实例
            const Attraction &attraction = attr[indices[i]];
            qDebug()<<attr[indices[i]].name;
            // 创建一个字符串来存储 Attraction 的信息
            QString info = QString("Name: %1, Popularity: %2, Rating: %3")
                               .arg(QString::fromStdString(attraction.name))
                               .arg(attraction.popularity)
                               .arg(attraction.rating);
            // 创建一个 QStandardItem 来存储信息字符串
            m_model->insertRow(m_model->rowCount());
            QModelIndex index = m_model->index(m_model->rowCount() - 1);
            m_model->setData(index, info);
            attrIndex[index.row()] = indices[i];
        }
        ui->listView->setModel(m_model);
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }

    else {
        QStringList stringList;
        stringList<< "No matched result.\n";
        ui->listView->setModel(new QStringListModel(stringList));
    }


}
void destinationRecommend::findPopularityTopK(vector<int>& arr, int low, int high, int k) {
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

void destinationRecommend::findRatingTopK(vector<int>& arr, int low, int high, int k) {
    if (low < high) {
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


void destinationRecommend::search_mode() {
    vector<int> indices;
    bool found = false;
    QStringList stringList;
    stringList << "Error: Invalid input. Please enter correct name.";
    int attr_num = sizeof(attr) / sizeof(attr[0]);
    m_model = new QStringListModel(this);

    for (int i = 0; i < attr_num; i++) {
        if (kmpSearch(attr[i].name, ui->lineEdit->text().toStdString())){
            found = true;
            indices.push_back(i);
            //qDebug()<<"find";
        }
    }

    if (found != true) {
        qDebug()<<"notfind";
        ui->listView->setModel(new QStringListModel(stringList));
    }
    else{
        switch (ui->comboBox_2->currentIndex())
        {
        case 0:
            // 按照热度排序
            quickPopularityFullSort(indices, 0, indices.size() - 1);
            for (int index : indices) {
                // 获取索引对应的 Attraction 实例
                const Attraction &attraction = attr[index];

                // 创建一个字符串来存储 Attraction 的信息
                QString info = QString("Name: %1, Popularity: %2, Rating: %3")
                                   .arg(QString::fromStdString(attraction.name))
                                   .arg(attraction.popularity)
                                   .arg(attraction.rating);
                // 创建一个 QStandardItem 来存储信息字符串
                m_model->insertRow(m_model->rowCount());
                QModelIndex i = m_model->index(m_model->rowCount() - 1);
                m_model->setData(i, info);
                attrIndex[i.row()] = index;
            }
            ui->listView->setModel(m_model);
            ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

            break;
        case 1:
            // 按照评分排序
            quickRatingFullSort(indices, 0, indices.size() - 1);
            for (int index : indices) {
                // 获取索引对应的 Attraction 实例
                const Attraction &attraction = attr[index];

                // 创建一个字符串来存储 Attraction 的信息
                QString info = QString("Name: %1, Popularity: %2, Rating: %3")
                                   .arg(QString::fromStdString(attraction.name))
                                   .arg(attraction.popularity)
                                   .arg(attraction.rating);
                // 创建一个 QStandardItem 来存储信息字符串
                m_model->insertRow(m_model->rowCount());
                QModelIndex i = m_model->index(m_model->rowCount() - 1);
                m_model->setData(i, info);
                attrIndex[i.row()] = index;
            }
            ui->listView->setModel(m_model);
            ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            break;


        }
    }
}

void destinationRecommend::quickPopularityFullSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionPopularity(arr, low, high);
        quickPopularityFullSort(arr, low, pivotIndex - 1);
        quickPopularityFullSort(arr, pivotIndex + 1, high);
    }
}

void destinationRecommend::quickRatingFullSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRating(arr, low, high);
        quickRatingFullSort(arr, low, pivotIndex - 1);
        quickRatingFullSort(arr, pivotIndex + 1, high);
    }
}
int destinationRecommend::partitionPopularity(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (attr[arr[j]].popularity >= attr[pivot].popularity) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}
int destinationRecommend::partitionRating(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (attr[arr[j]].rating >= attr[pivot].rating) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}




void destinationRecommend::on_listView_doubleClicked(const QModelIndex &index)
{
    myMap* w = new myMap(nullptr, attr[attrIndex[index.row()]], attrIndex[index.row()]);
    this->hide();
    w->show();
    connect(w, &myMap::quit_function, this, &destinationRecommend::show);
}

