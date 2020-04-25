ARG ALPINE_TAG
FROM docker.pkg.github.com/my-repositories/gametrainer/env-alpine:${ALPINE_TAG}

WORKDIR /project

COPY ./ ./

RUN \
    make T=1 C=Debug && \
    cd build/Debug-x64 && ctest -VV && cd ../.. && \
    mv ./.ci/.coveralls.yml ./ && \
    export TRAVIS_BRANCH=reborn && \
    coveralls --root . --build-root build -e deps -E ".*CMakeFiles.*" -E ".*googletest.*" --skip-ssl-verify --verbose
