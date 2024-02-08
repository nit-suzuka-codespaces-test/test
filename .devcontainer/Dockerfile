FROM mcr.microsoft.com/devcontainers/universal:2-linux

RUN --mount=type=cache,target=/var/cache/apt \
    -- mount=type=cache,target=/var/lib/apt \
    rm /etc/apt/apt.conf.d/docker-clean
    && apt-get update \
    && apt-get install -y libsfml-dev xauth 
    
COPY display.sh /etc/profile.d/display.sh
RUN chmod +x /etc/profile.d/display.sh
