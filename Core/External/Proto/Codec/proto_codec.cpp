#include "proto_codec.h"

RequestBuffer<100> ProtoCodec::request_buffer = RequestBuffer<100>();

ResponseBuffer<100> ProtoCodec::response_buffer = ResponseBuffer<100>();

light_detector::RequestContainer request_container = light_detector::RequestContainer();

light_detector::ResponseContainer response_container = light_detector::ResponseContainer();

RequestBuffer<100> ProtoCodec::get_request_buffer() {
    return request_buffer;
}

ResponseBuffer<100> ProtoCodec::get_response_buffer() {
    return response_buffer;
}

int ProtoCodec::decode_request_container() {
    request_container.clear();

    if (request_container.deserialize(request_buffer) == ::EmbeddedProto::Error::NO_ERRORS) {
        State::get_request_container_sequence().add(request_container);

        return EXIT_SUCCESS;
    }


    return EXIT_FAILURE;
}

int ProtoCodec::encode_response_container(const light_detector::ResponseContainer& content) {
    response_container.serialize()
};