#!/bin/bash
set -e

echo 'export GIT_EDITOR=vi' >> ~/.bashrc

# Update and install clangd
sudo apt-get update && sudo apt-get install -y clangd
