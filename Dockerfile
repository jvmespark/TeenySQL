# initial build
FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    g++ \
    make 

WORKDIR /teenysql

COPY src/ ./src/
COPY build/ ./build/

WORKDIR /teenysql/build
RUN make build