FROM mcr.microsoft.com/devcontainers/universal:2-linux

COPY display.sh /etc/profile.d/display.sh
RUN chmod +x /etc/profile.d/display.sh

RUN apt-get update \
    && apt-get install -y libsfml-dev xauth \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


