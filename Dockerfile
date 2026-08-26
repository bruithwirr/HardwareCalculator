FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake git ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --target hardware_calc -j"$(nproc)"

FROM ubuntu:24.04 AS runtime

WORKDIR /app
COPY --from=build /src/build/hardware_calc ./hardware_calc
COPY --from=build /src/config.yaml ./config.yaml

ENTRYPOINT ["./hardware_calc", "config.yaml"]