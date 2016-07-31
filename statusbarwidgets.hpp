#ifndef STATUSBARWIDGETS_HPP
#define STATUSBARWIDGETS_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "config/configuration.hpp"

class StatusBarWidgets : public QObject
{
        Q_OBJECT

    public:
        explicit StatusBarWidgets(QObject *parent = 0);
        ~StatusBarWidgets();

        QLabel* time;
        QLabel* habSerial;
        QLabel* localGpsSerial;
        QLabel* serverSync;

    private:
        Configuration* config;

        QTimer* timeTimer;

        void initLabelStyle(QLabel* label);

        void initTime();
        void initHabSerial();
        void initLocalGpsSerial();
        void initServerSync();

        void initTimeTimer();

    public slots:
        void updateFromConfig();

    private slots:
        void updateTime();
};

#endif // STATUSBARWIDGETS_HPP
