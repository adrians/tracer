# Electronic tracer

![Screenshot](/doc/screenshot.png)

## The "driver-v1" folder

* Use it for physical tracer board, version 1.
* Prerequisites: `libudev1` and `g++` installed (`sudo apt-get install libudev1 build-essential`).
* Driver based on Kerry Wong's library (<https://github.com/kerrydwong/MCP2210-Library>).
* To build the driver-application, run `cd driver-v1; make`. It will generate the `tracer` binary, which should be run as root (or with the `setuid` bit set).

## The "driver-mock" folder

* Use it for local testing, without a tracer board. It's a dummy data source.
* Prerequisites: `g++` installed.
* To build it, run `cd driver-mock; make`. It will generate the `tracer` binary.

## The "frontend" directory

* Frontend done using electron.js and apex charts.
* It uses `npm`.
* To build, run `npm install`.
* To run, copy the `tracer` binary (from either `driver-v1` or `driver-mock` directories), and then run `npm start`.

The `driver-v1` requires setuid permissions. See the snippet below.

```bash
cd frontend
cp ../driver-v1/tracer .
sudo chown root tracer
sudo chmod +s tracer
npm start
```

## The "board" directory

* Contains the kicad project used for manufacturing the first iteration of the board.
