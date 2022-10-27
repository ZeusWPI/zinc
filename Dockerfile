FROM thevlang/vlang:alpine
COPY src /src
WORKDIR /src
RUN v main.v

FROM alpine:latest
COPY --from=0 /src/main /
CMD ["/main"]
