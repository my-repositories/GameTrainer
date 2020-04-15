ARG ALPINE_TAG
FROM docker.pkg.github.com/my-repositories/gametrainer/env-alpine:${ALPINE_TAG}

WORKDIR /project

COPY ./ ./

RUN \
    make T=1 && \
    ./build/Release-x64/tests/gt_os/test_gt_os && \
    mv ./.ci/.coveralls.yml ./ && \
    export TRAVIS_BRANCH=reborn && \
    coveralls --root . --build-root build -e deps -E ".*CMakeFiles.*" -E ".*googletest.*" --skip-ssl-verify --verbose
