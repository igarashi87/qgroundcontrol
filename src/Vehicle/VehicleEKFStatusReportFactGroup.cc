/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "VehicleEKFStatusReportFactGroup.h"
#include "Vehicle.h"
#include "QGCGeo.h"

const char* VehicleEKFStatusReportFactGroup::_velocityVarianceFactName =   "velocity_variance";
const char* VehicleEKFStatusReportFactGroup::_posHorizVarianceFactName =   "pos_horiz_variance";
const char* VehicleEKFStatusReportFactGroup::_posVertVarianceFactName  =   "pos_vert_variance";
const char* VehicleEKFStatusReportFactGroup::_compassVarianceFactName  =   "compass_variance";
const char* VehicleEKFStatusReportFactGroup::_terrainAltVarianceFactName = "terrain_alt_variance";
const char* VehicleEKFStatusReportFactGroup::_airspeedVarianceFactName =   "airspeed_variance";

VehicleEKFStatusReportFactGroup::VehicleEKFStatusReportFactGroup(QObject* parent)
    : FactGroup(1000, ":/json/Vehicle/EKFStatusReportFact.json", parent)
    , _velocityVarianceFact      (0, _velocityVarianceFactName,         FactMetaData::valueTypeFloat)
    , _posHorizVarianceFact      (0, _posHorizVarianceFactName,         FactMetaData::valueTypeFloat)
    , _posVertVarianceFact       (0, _posVertVarianceFactName,          FactMetaData::valueTypeFloat)
    , _compassVarianceFact       (0, _compassVarianceFactName,          FactMetaData::valueTypeFloat)
    , _terrainAltVarianceFact    (0, _terrainAltVarianceFactName,          FactMetaData::valueTypeFloat)
    , _airspeedVarianceFact      (0, _airspeedVarianceFactName,          FactMetaData::valueTypeFloat)
{
    _addFact(&_velocityVarianceFact,               _velocityVarianceFactName);
    _addFact(&_posHorizVarianceFact,               _posHorizVarianceFactName);
    _addFact(&_posVertVarianceFact,                _posVertVarianceFactName);
    _addFact(&_compassVarianceFact,                _compassVarianceFactName);
    _addFact(&_terrainAltVarianceFact,             _terrainAltVarianceFactName);
    _addFact(&_airspeedVarianceFact,               _airspeedVarianceFactName);

    _velocityVarianceFact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _posHorizVarianceFact.setRawValue(std::numeric_limits<float>::quiet_NaN());
    _posVertVarianceFact.setRawValue(std::numeric_limits<unsigned int>::quiet_NaN());
    _compassVarianceFact.setRawValue(std::numeric_limits<unsigned int>::quiet_NaN());
    _terrainAltVarianceFact.setRawValue(std::numeric_limits<unsigned int>::quiet_NaN());
    _airspeedVarianceFact.setRawValue(std::numeric_limits<unsigned int>::quiet_NaN());
}

void VehicleEKFStatusReportFactGroup::handleMessage(Vehicle* /* vehicle */, mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_EKF_STATUS_REPORT:
       _handleEKFStatusReport(message);
       break;
    default:
        break;
    }
}

void VehicleEKFStatusReportFactGroup::_handleEKFStatusReport(mavlink_message_t& message)
{
    mavlink_ekf_status_report_t ekfStatusReport;
    mavlink_msg_ekf_status_report_decode(&message, &ekfStatusReport);

    _velocityVarianceFact.setRawValue(ekfStatusReport.velocity_variance);
    _posHorizVarianceFact.setRawValue(ekfStatusReport.pos_horiz_variance);
    _posVertVarianceFact.setRawValue(ekfStatusReport.pos_vert_variance);
    _compassVarianceFact.setRawValue(ekfStatusReport.compass_variance);
    _terrainAltVarianceFact.setRawValue(ekfStatusReport.terrain_alt_variance);
    _airspeedVarianceFact.setRawValue(ekfStatusReport.airspeed_variance);
}
