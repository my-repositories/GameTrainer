ARG ALPINE_TAG
FROM alpine:${ALPINE_TAG}

WORKDIR /project

RUN apk --no-cache add bash readline-dev curl git cmake clang-dev make gcc g++ libc-dev linux-headers && \
    apk add --no-cache --virtual .build-deps python3-dev libffi-dev openssl-dev && \
    apk add --no-cache --update python3 && \
    pip3 install --upgrade pip setuptools cpp-coveralls pyyaml && \
    mkdir deps && \
    cd deps && \
    git clone https://github.com/google/googletest.git googletest && \
    curl -R -O http://www.lua.org/ftp/lua-5.3.4.tar.gz && \
    tar -zxf lua-5.3.4.tar.gz && \
    rm -rf lua-5.3.4.tar.gz && \
    cd lua-5.3.4 && \
    make linux test && \
    make install && \
    cd ../..
