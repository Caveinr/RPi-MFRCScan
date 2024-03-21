# RPi-MFRCScan

MFRC522+RPi, POST result to designated url.

For every 1 second , the program will see if there is a card present,
and use HTTP POST method to send result of presented card to url which
is offered in ```config.toml```.

# Usage

## Compile
Before compiling , there`re some steps:
* The dep RPi-RFID was written with C++ 11 long ago and used global namespace std,
  while another dep CPR requires C++ 17 at least , which introduces std::byte.
  In this way, ```typedef uint8_t byte``` in RPi-RFID would be ambiguous. 
  A simple but lazy way is to rename all byte to another name.
* RPi-RFID depends bcm2835 library, you can acquire installment 
  guide it at [here](http://www.airspayce.com/mikem/bcm2835/).

```shell
git clone https://github.com/Caveinr/RPi-MFRCScan.git --recursive
cd RPi-MFRCScan
cmake .
```
## Config
```toml
SECRET=""
API_URI="your_api_url:port/path"
```
```secret``` is the salt value to make header ```X-signature```, 
which is the result of hmac with SHA1 of HTTP body.

## Pin Layout

The following table shows the pin layout used:

(Physical Pin)

|           | MFRC522 | Raspberry Pi |
|-----------|---------|--------------|
| Signal    | Pin     | Pin          |
| RST/Reset | RST     | 22           |
| SPI SS    | SDA     | 24           |
| SPI MOSI  | MOSI    | 19           |
| SPI MISO  | MISO    | 21           |
| SPI SCK   | SCK     | 23           |
| 3V        | 3v      | 1            |
| GND       | GND     | 25           |



## API
Example request body:
```json
{
  "UID":"AABBCCDD",
  "SAK":8,
  "timestamp":1711025917
}
```


# Dependency
* **CPR**
  * From: [GitHub](https://github.com/libcpr/cpr)
  * License: MIT
* **RPi-RFID**
  * From: [GitHub](https://github.com/villinte/RPi-RFID)
  * License: Unlicensed
* **toml11**
  * From: [GitHub](https://github.com/ToruNiina/toml11)
  * License: MIT
* **hash-library**
  * From: [GitHub](https://github.com/stbrumme/hash-library)
  * License: Zlib
  