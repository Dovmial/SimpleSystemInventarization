#include "View.hpp"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile("./styles/Adaptic.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet{ QLatin1String(styleSheetFile.readAll()) };
    a.setStyleSheet(styleSheet);

    View w;
    w.show();
    
    return a.exec();
}
