# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04

ARG DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-euxo", "pipefail", "-c"]

RUN <<'EOT' bash
apt-get update

apt-get install \
  --assume-yes \
  --quiet \
  doxygen \
  g++-14 \
  gcc-14

apt-get clean --assume-yes

rm -rf /tmp/*
rm -rf /var/tmp/*
rm -rf /var/log/*
rm -rf /var/lib/apt/lists/*

update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100
update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100

EOT
