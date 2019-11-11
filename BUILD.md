# Build options for the example:

In this project there are multiple small examples to build one of them
please select a macro option form the list below and provide the define
name to the build option:

```sh
$ mbed compile -D <option>
```

Available build defines:

* `BLE_CONN`: Enables the connect/disconnect callbacks.
* `BLE_SCAN`: Enables the periodic advertisment scan example.
* `BLE_SRV_COUNT`: Enables a BLE counter service.

Please note that it is possible that not all combinations are valid!
