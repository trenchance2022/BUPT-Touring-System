#ifndef MYMAP_H
#define MYMAP_H

#include <QWidget>
#include "destinationrecommend.h"
#include "mylabel.h"
#include <QString>
#include <QDebug>
#include "route_plan.h"
#include "editmultipoint.h"
#include "kmp.h"

namespace Ui {
class myMap;
}

class myMap : public QWidget
{
    Q_OBJECT

public:
    explicit myMap(QWidget *parent, Attraction &Attr, int Index);
    ~myMap();
    void quickSort(vector<int>& indices, int low, int high);
    bool exactMatch(const string& text, const string& pattern);
    void findPopularityTopK(vector<int>& arr, int low, int high, int k, int selectedSpotIndex, int selectedBuildIndex);
    void quickPopularityFullSort(vector<int>& arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex);
    int partitionPopularity(vector<int>& arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex);
    void findDistanceTopK(vector<int>& arr, int low, int high, int k, int selectedSpotIndex, int selectedBuildIndex);
    int partitionDistance(vector<int>& arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex);
    void quickDistanceFullSort(vector<int>& arr, int low, int high, int selectedSpotIndex, int selectedBuildIndex);

private slots:
    void on_backBtn_clicked();

    void on_routePlanBtn_clicked();

    void on_editRouteBtn_clicked();

    void on_facilitySearch_clicked();

    void on_foodSearch_clicked();

signals:
    void quit_function();

private:
    Ui::myMap *ui;
    Attraction m_attr;
    int midplace[12];
    int spotIndex;
    myLabel* mapImg;
    int trafficTool;
    int numForMulti;
    int placeForMult[12];
    EditMultiPoint *dlgMulti = nullptr;
    vector<int> m_restaurantID;
};

#endif // MYMAP_H
