#ifndef CONFIGWINDOW_HPP
#define CONFIGWINDOW_HPP

#include <QDialog>

#include "configuration.hpp"

namespace Ui {
    class ConfigWindow;
}

class ConfigWindow : public QDialog
{
        Q_OBJECT

    public:
        explicit ConfigWindow(QWidget *parent = 0);
        ~ConfigWindow();

        void setConfig(Configuration* value);

    private:
        Ui::ConfigWindow *ui;
        Configuration* config;

        void load();
        void save();

    private slots:
        void handleOK();
        void handleApply();
        void handleClose();
        void handleReset();
};

#endif // CONFIGWINDOW_HPP
