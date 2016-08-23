#ifndef HAB_HPP
#define HAB_HPP

#include <QByteArray>

class Hab
{
    public:
        Hab();

        int getFixStatus() const;
        void setFixStatus(int value);

        double getLatitude() const;
        void setLatitude(double value);

        double getLongitude() const;
        void setLongitude(double value);

        double getAltitude() const;
        void setAltitude(double value);

        int getSliceTot() const;
        void setSliceTot(int value);

        int getSliceNum() const;
        void setSliceNum(int value);

        QByteArray getImageData() const;
        void clearImageData();
        void appendImageData(const QByteArray& value);

        float getIntTemp() const;
        void setIntTemp(float value);

        float getExtTemp() const;
        void setExtTemp(float value);

        float getExtAlt() const;
        void setExtAlt(float value);

    private:
        int fixStatus;
        double latitude;
        double longitude;
        double altitude;

        int sliceTot;
        int sliceNum;
        QByteArray imageData;

        float intTemp;
        float extTemp;
        float extAlt;
};

#endif // HAB_HPP
