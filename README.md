| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- |

---

# BrigaidRange - Field Test Toolkit for BLE/WiFi/LoRa Range Testing

### Configuration

```
idf.py menuconfig
```

- Set the WiFi SSID and Password
- Set WiFi Channel (1-13)
- Set STA maximum connection number
- Set the Field Test Mode (0: WiFi source, 1: WiFi Scanner, 2: BLE Beacon, 3: BLE Scanner) (More test modes will be added in the future)

> Supports startup beep sound (on GPIO 23) (Soon to be added to the menuconfig) for naked eye debugging (bootloops, startup confirmation, etc.)

### Build and Flash

```
idf.py build
idf.py -p PORT flash
```

### Monitor

```
idf.py -p PORT monitor
```