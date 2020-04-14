ARG ALPINE_TAG
FROM docker.pkg.github.com/my-repositories/gametrainer/env-alpine:${ALPINE_TAG}

WORKDIR /project

COPY ./ ./

RUN \
    cmake -B . -DCOVERAGE=1 . && \
    cmake --build . && \
    ./tests && \
    mv ./.ci/.coveralls.yml ./ && \
    coveralls --root . -E ".*CMakeFiles.*" --skip-ssl-verify
