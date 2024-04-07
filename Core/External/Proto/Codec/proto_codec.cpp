#include "proto_codec.h"
#include "indicator.h"

RequestBuffer ProtoCodec::request_buffer = RequestBuffer();

ResponseBuffer ProtoCodec::response_buffer = ResponseBuffer(100);

light_detector::RequestContainer ProtoCodec::request_container =
        light_detector::RequestContainer();

RequestBuffer* ProtoCodec::get_request_buffer() {
    return &request_buffer;
}

ResponseBuffer* ProtoCodec::get_response_buffer() {
    return &response_buffer;
}

int ProtoCodec::decode_request_container() {
    request_container.clear();

    if (request_container.deserialize(request_buffer) == ::EmbeddedProto::Error::NO_ERRORS) {
        State::get_request_container_sequence()->add(request_container);

        request_buffer.clear();

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int ProtoCodec::encode_response_container(const light_detector::ResponseContainer& content) {
    if (content.serialize(response_buffer) == ::EmbeddedProto::Error::NO_ERRORS) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
};