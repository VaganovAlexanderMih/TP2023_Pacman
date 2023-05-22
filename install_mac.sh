#!/bin/bash
brew update
brew install docker docker-compose
sudo mkdir /usr/local/bin
sudo chown $USER /usr/local/bin
chmod +x run.sh
chmod +x run_mac.sh
chmod +x project_builder.sh
docker build -t game .
