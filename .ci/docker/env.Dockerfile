ARG ALPINE_TAG
FROM alpine:${ALPINE_TAG}

WORKDIR /project

RUN apk --no-cache add git cmake clang-dev make gcc g++ libc-dev linux-headers && \
    apk add --no-cache --virtual .build-deps python3-dev libffi-dev openssl-dev && \
    apk add --no-cache --update python3 && \
    pip3 install --upgrade pip setuptools cpp-coveralls pyyaml && \
    mkdir deps && \
    git clone https://github.com/google/googletest.git deps/googletest
