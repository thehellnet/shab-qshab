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

    private:
        Ui::ConfigWindow *ui;
        QSettings* settings;
        Configuration* config;

        void load();
        void save();
        void updateSerialPortsLists();
        void populateSerialPortsParams();

    private slots:
        void updateLocalGpsStatus();
        void updateServerSyncStatus();
        void updateLogRawStatus();
        void updateLogImagesStatus();

        void chooseLogRawPath();
        void chooseLogIamgesPath();

        void handleOK();
        void handleApply();
        void handleClose();
        void handleReset();
};

#endif // CONFIGWINDOW_HPP
