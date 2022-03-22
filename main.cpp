#include <QApplication>
#include <tree.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tree view;
    view.show();
    return a.exec();
}
