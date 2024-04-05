#include "proto_codec.h"

RequestBuffer<DEFAULT_REQUEST_BUFFER_SIZE> ProtoCodec::request_buffer =
        RequestBuffer<DEFAULT_REQUEST_BUFFER_SIZE>();

ResponseBuffer<DEFAULT_RESPONSE_BUFFER_SIZE> ProtoCodec::response_buffer =
        ResponseBuffer<DEFAULT_RESPONSE_BUFFER_SIZE>();

light_detector::RequestContainer ProtoCodec::request_container =
        light_detector::RequestContainer();

RequestBuffer<DEFAULT_REQUEST_BUFFER_SIZE>& ProtoCodec::get_request_buffer() {
    return request_buffer;
}

ResponseBuffer<DEFAULT_RESPONSE_BUFFER_SIZE>& ProtoCodec::get_response_buffer() {
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
    if (content.serialize(response_buffer) == ::EmbeddedProto::Error::NO_ERRORS) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
};