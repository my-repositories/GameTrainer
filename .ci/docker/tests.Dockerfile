ARG ALPINE_TAG
FROM docker.pkg.github.com/my-repositories/gametrainer/env-alpine:${ALPINE_TAG}

WORKDIR /project

COPY ./ ./

RUN \
    make T=1 && \
    ./build/Release-x64/tests/gt_os/Release/test_gt_os && \
    mv ./.ci/.coveralls.yml ./ && \
    coveralls --root build -E ".*CMakeFiles.*" --skip-ssl-verify
