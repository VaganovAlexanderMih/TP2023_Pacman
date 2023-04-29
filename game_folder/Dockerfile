FROM ubuntu:latest

RUN apt-get update -y && apt-get install -y g++ libsfml-dev cmake

COPY . .

RUN chmod +x run.sh

RUN ./run.sh