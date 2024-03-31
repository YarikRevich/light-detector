#include "proto_codec.h"

RequestBuffer<100> ProtoCodec::getRequestBuffer() {
    return requestBuffer;
}

ResponseBuffer<100> ProtoCodec::getResponseBuffer() {
    return responseBuffer;
}
