# Hardware Sizing Calculator

A small C++ command-line application that estimates the CPU, RAM and disk requirements for processing a given number of transactions.

The calculator uses configurable transaction profiles defined in a YAML file and applies a configurable safety margin to the calculated hardware requirements.

## Requirements

- C++17 compatible compiler
- CMake 3.16 or newer
- Git
- Internet connection during the first CMake configuration/build, because dependencies are downloaded using CMake `FetchContent`

The project uses:

- [yaml-cpp](https://github.com/jbeder/yaml-cpp) `0.9.0`
- [GoogleTest](https://github.com/google/googletest) `1.17.0`

## Building

Clone the repository:

```bash
git clone https://github.com/bruithwirr/HardwareCalculator.git
cd HardwareCalculator
```

Create a build directory and configure the project:

```bash
cmake -S . -B build
```

Build the application:

```bash
cmake --build build
```

The executable will be created in the `build` directory.


## Running

From the project root, run:

```bash
./build/hardware_calc
```

By default, the application looks for `config.yaml` in the current working directory.

A different configuration file can also be provided:

```bash
./build/hardware_calc ~/my_files/example/my_config.yaml
```

## Configuration

Transaction types and their resource requirements are stored in `config.yaml`.

Example:

```yaml
safety_margin: 1.2

transactions:
  - type: READ
    cpu: 20
    ram: 1000
    disc: 1

  - type: WRITE
    cpu: 40
    ram: 4000
    disc: 500

  - type: COMPUTE
    cpu: 100
    ram: 7000
    disc: 400
```

The units used by the calculator are:

- `cpu`: CPU time per transaction in milliseconds
- `ram`: RAM requirement in KB per CPU core
- `disc`: disk space generated per transaction in KB
- `safety_margin`: multiplier applied to the calculated resource requirements

Transaction types can be added or modified without changing the calculation code.

## Running with Docker

The project can also be built and run without installing a compiler, CMake, or any dependencies locally.

Build the image from the project root:

```bash
docker build -t hardware-calc .
```

Run it interactively:

```bash
docker run -it --rm hardware-calc
```

To use a different configuration file without rebuilding the image, mount it in at runtime:

```bash
docker run -it --rm -v /path/to/my_config.yaml:/app/config.yaml hardware-calc
````
## Assumptions

This application is an estimation tool rather than a benchmark.

The transaction resource requirements in `config.yaml` are assumptions. In a production environment, these values should ideally be obtained from measurements or benchmarking of the actual transaction workload.

The safety margin is configurable because the appropriate margin depends on the workload and the desired level of capacity headroom.

A target completion time is also requested because transaction count and CPU cost alone are not sufficient to determine the required number of CPU cores. The required CPU capacity depends on how quickly the transactions need to be processed.

The calculator provides a simplified hardware estimate. It does not currently account for factors such as:

- CPU architecture differences
- I/O throughput
- network bandwidth
- database performance
- concurrent transaction behavior
- operating system overhead
- virtualization/container overhead
- workload variability

## Testing

The project uses GoogleTest for unit testing.

Build the project:

```bash
cmake -S . -B build
cmake --build build
```

Run the tests:

```bash
ctest --test-dir build
```
