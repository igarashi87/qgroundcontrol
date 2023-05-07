/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "FactGroup.h"
#include "QGCMAVLink.h"

class VehicleEKFStatusReportFactGroup : public FactGroup
{
    Q_OBJECT

public:
    VehicleEKFStatusReportFactGroup(QObject* parent = nullptr);

    Q_PROPERTY(Fact* hygroID            READ hygroID            CONSTANT)
    Q_PROPERTY(Fact* hygroTemp          READ hygroTemp          CONSTANT)
    Q_PROPERTY(Fact* hygroHumi          READ hygroHumi          CONSTANT)

    Fact* hygroID                           () { return &_hygroIDFact; }
    Fact* hygroTemp                         () { return &_hygroTempFact; }
    Fact* hygroHumi                         () { return &_hygroHumiFact; }

    // Overrides from FactGroup
    virtual void handleMessage(Vehicle* vehicle, mavlink_message_t& message) override;

    static const char* _hygroIDFactName;
    static const char* _hygroHumiFactName;

    static const char* _velocityVarianceFactName;
    static const char* _posHorizVarianceFactName;
    static const char* _posVertVarianceFactName;
    static const char* _compassVarianceFactName;
    static const char* _terrainAltVarianceFactName;
    static const char* _airspeedVarianceFactName;

protected:
    void _handleEKFStatusReport        (mavlink_message_t& message);

    Fact _velocityVarianceFact;
    Fact _posHorizVarianceFact;
    Fact _posVertVarianceFact;
    Fact _compassVarianceFact;
    Fact _terrainAltVarianceFact;
    Fact _airspeedVarianceFact;

    Fact _hygroTempFact;
    Fact _hygroHumiFact;
    Fact _hygroIDFact;
};
