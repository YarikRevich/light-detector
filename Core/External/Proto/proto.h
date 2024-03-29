#ifndef LIGHT_DETECTOR_PROTO_H
#define LIGHT_DETECTOR_PROTO_H

#include "data.h"
#include "info.h"
#include "settings.h"

/**
 * Represents parser used to decompose and composite request and response.
 */
class ProtoParser {
public:


private:
    /**
     * Represents data bus request implementation.
     */
    light_detector::DataBusRequest dataBusRequest;

    /**
     * Represents data bus response implementation.
     */
    light_detector::DataBusResponse dataBusResponse;

    /**
     * Represents info bus request implementation.
     */
    light_detector::InfoBusRequest infoBusRequest;

    /**
     * Represents info bus response implementation.
     */
    light_detector::InfoBusResponse infoBusResponse;

    /**
     * Represents settings bus request implementation.
     */
    light_detector::SettingsBusRequest settingsBusRequest;

    /**
     * Represents settings bus response implementation.
     */
    light_detector::SettingsBusResponse settingsBusResponse;
};

#endif //LIGHT_DETECTOR_PROTO_H
