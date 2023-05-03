#!/bin/bash
brew install docker-ce
brew install docker-compose
chmod +x run.sh
chmod +x project_builder.sh
docker build -t game .