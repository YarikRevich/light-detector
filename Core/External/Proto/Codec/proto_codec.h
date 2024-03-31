#ifndef LIGHT_DETECTOR_PROTO_CODEC_H
#define LIGHT_DETECTOR_PROTO_CODEC_H

#include "data.h"
#include "info.h"
#include "settings.h"
#include "request.h"
#include "response.h"

#include "request_buffer.h"
#include "response_buffer.h"

/**
 * Represents codec used to decompose and composite request and response.
 */
class ProtoCodec {
public:
    /**
     * Retrieves common request buffer instance.
     *
     * @return common instance of request buffer.
     */
    static RequestBuffer<100> getRequestBuffer();

    /**
     * Retrieves common response buffer instance.
     *
     * @return common instance of response buffer.
     */
    static ResponseBuffer<100> getResponseBuffer();
private:
    /**
     * Represents common instance of request buffer.
     */
    static RequestBuffer<100> requestBuffer;

    /**
     * Represents common instance of response buffer.
     */
    static ResponseBuffer<100> responseBuffer;
//
//    /**
//     * Represents data bus request implementation.
//     */
//    static light_detector::DataBusRequestContent dataBusRequestContent;
//
//    /**
//     * Represents data bus response implementation.
//     */
//    light_detector::DataBusResponse dataBusResponse;
//
//    /**
//     * Represents info bus request implementation.
//     */
//    light_detector::InfoBusRequest infoBusRequest;
//
//    /**
//     * Represents info bus response implementation.
//     */
//    light_detector::InfoBusResponse infoBusResponse;
//
//    /**
//     * Represents settings bus request implementation.
//     */
//    light_detector::SettingsBusRequest settingsBusRequest;
//
//    /**
//     * Represents settings bus response implementation.
//     */
//    light_detector::SettingsBusResponse settingsBusResponse;
};

#endif //LIGHT_DETECTOR_PROTO_CODEC_H
