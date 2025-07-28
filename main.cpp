#include "login.h"
#include "myGraph.h"
#include <QApplication>
#include <./json.hpp>

using json = nlohmann::json;

int main(int argc, char *argv[])
{



    loadAttractionArray("./data_map.json");

    QApplication a(argc, argv);
    login w; //打开登录界面
    w.show();
    return a.exec();
}
