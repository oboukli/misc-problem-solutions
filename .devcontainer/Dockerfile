# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

FROM mcr.microsoft.com/devcontainers/cpp:ubuntu26.04

ARG DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-euxo", "pipefail", "-c"]

RUN <<'EOT' bash
apt-get update

apt-get install \
  --assume-yes \
  --quiet \
  doxygen \
  g++-16 \
  gcc-16

apt-get clean --assume-yes

rm -rf /tmp/*
rm -rf /var/tmp/*
rm -rf /var/log/*
rm -rf /var/lib/apt/lists/*

update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100
update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-16 160
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-16 160

EOT
