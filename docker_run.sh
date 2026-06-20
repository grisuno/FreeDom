#!/bin/bash
echo "Building FreeDom Docker..."
sudo docker build -t freedom-browser .
sudo docker run -it --rm \
  --name freedom-test \
  -p 8080:8080 \
  --cap-drop=ALL \
  --security-opt no-new-privileges:true \
  --memory="2g" \
  freedom-browser
