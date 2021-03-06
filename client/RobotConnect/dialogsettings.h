#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = nullptr);
    ~DialogSettings();

    QString HostIP();

    quint16 HostPort();

private:
    Ui::DialogSettings *ui;
};

#endif // DIALOGSETTINGS_H
