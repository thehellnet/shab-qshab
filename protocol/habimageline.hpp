#ifndef HABIMAGELINE_HPP
#define HABIMAGELINE_HPP

#include <QByteArray>

#include "line.hpp"
#include "command.hpp"

class HabImageLine : public Line
{
    public:
        HabImageLine();
        ~HabImageLine();

        long getTimestamp() const;
        void setTimestamp(long value);

        QString serialize() override;

        int getSliceTot() const;
        void setSliceTot(int value);

        int getSliceNum() const;
        void setSliceNum(int value);

        QByteArray getData() const;
        void setData(const QByteArray& value);

    private:
        long timestamp;

        int sliceTot;
        int sliceNum;
        QByteArray data;
};

#endif // HABIMAGELINE_HPP
