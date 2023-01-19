#!/bin/bash
docker run -d --rm \
    --net=host \
    -v `pwd`/default.conf:/etc/nginx/conf.d/default.conf \
    nginx:alpine-slim

