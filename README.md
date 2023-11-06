# ZepherQuest
## A hobbyist weather monitoring project

## Features

### Current
- Utilizes FreeRTOS for efficient multitasking.
- Tasks divided into two main categories: Communications and IO.
- A main task pinned to each core of the ESP to utilize its dual-core capabilities.
- All sub-tasks created from their respective core main task, and pinned to their core, to create an easy to understand task heirachy.
- A simple HTTP server that resonds to a GET request by taking a reading and transmitting the read value.
  
### Coming
- Measure temperature, humidity, and atmospheric pressure using appropriate sensors.
- A web interface for viewing the real-time data.

### Future
- Regular logging of weather conditions, and long term data storage.
- Web based UI for viewing historical data.

## Hardware 
- NodeMCU32s ESP32 development board.

## Software
- [PlatformIO](https://platformio.org/).
- [EspIdf 4.4.1](https://github.com/espressif/esp-idf/tree/release/v4.4)
- [FreeRTOS library](https://github.com/FreeRTOS/FreeRTOS) (included in ESP32 Arduino Core).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributors
- Corey Knight
