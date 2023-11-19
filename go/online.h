
#ifndef ONLINE_H
#define ONLINE_H


#include <QMainWindow>


class online : public QMainWindow
{
    Q_OBJECT
public:
    explicit online(QWidget *parent = nullptr);

signals:
    void onlineBack();


};

#endif // ONLINE_H
