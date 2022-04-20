FROM debian:buster

RUN apt-get update && apt-get install -y qemu qemu-user
COPY main.out /app/main.out

EXPOSE 34952
CMD qemu-cris -cpu crisv10 /app/main.out