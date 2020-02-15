# Electronic tracer

![Screenshot](/doc/screenshot.png)

## The "driver" folder

* Prerequisites: `libudev1` and `g++` installed (`sudo apt-get install libudev1 build-essential`).
* Driver based on Kerry Wong's library (<https://github.com/kerrydwong/MCP2210-Library>).
* To build the driver-application, run `cd driver; make`. It will generate the `tracer` binary, which should be run as root (or with the `setuid` bit set).

## The "frontend" directory

* Frontend done using electron.js and apex charts.
* It uses `npm`.
* To build, run `npm install`.
* To run, copy the `tracer` binary from the driver in the same location as the rest of the files, add the `setuid` bit and run `npm start`. See the snippet below.

```bash
cd frontend
cp ../backend/tracer .
sudo chown root tracer
sudo chmod +s tracer
npm start
```

## The "board" directory

* Contains the kicad project used for manufacturing the first iteration of the board.
