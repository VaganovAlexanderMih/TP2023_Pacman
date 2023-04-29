#!/bin/bash
if ! [ "$(dpkg -s docker-ce)" ]; then
    apt-get install docker-ce
fi

if ! [ "$(dpkg -s docker-compose)" ]; then
    apt-get install docker-compose
fi
chmod +x run.sh
chmod +x project_builder.sh
docker build -t game .