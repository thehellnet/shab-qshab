#ifndef CONFIGWINDOW_HPP
#define CONFIGWINDOW_HPP

#include <QDialog>

namespace Ui {
    class ConfigWindow;
}

class ConfigWindow : public QDialog
{
        Q_OBJECT

    public:
        explicit ConfigWindow(QWidget *parent = 0);
        ~ConfigWindow();

    private:
        Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_HPP
