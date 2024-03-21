#include <cstdio>
#include <string>
#include <cstring>
#include <unistd.h>

#include "cpr/cpr.h"
#include "toml11/toml.hpp"
#include "RPi-RFID/MFRC522.h"
#include "hash-library/sha1.h"
#include "hash-library/hmac.h"

const int MAXLENGTH = 128;

std::string loadConfig();

int main() {
    MFRC522 mfrc;
    char buffer[MAXLENGTH];
    char UID[21];
    auto config = new auto (toml::parse("config.toml"));
    const std::string secret(toml::find<std::string>(*config, "SECRET"));
    const std::string uri(toml::find<std::string>(*config,"API_URI"));

    delete config;
    mfrc.PCD_Init();

    while (true) {
        sleep(1);
        if (!mfrc.PICC_IsNewCardPresent())
            continue;
        if (!mfrc.PICC_ReadCardSerial())
            continue;
        memset(UID,0, sizeof(UID));
        for (uint8_t i = 0; i < mfrc.uid.size; i++) {
            snprintf(UID+ strlen(UID),3,"%02X",mfrc.uid.uidByte[i]);
        }
        snprintf(buffer,MAXLENGTH,R"({"UID":"%s","SAK":%hhu,"timestamp":%ld})",UID, mfrc.uid.sak, time(nullptr));
        std::string body(buffer);

        cpr::Post(
                cpr::Url{uri},
                cpr::Body{body},
                cpr::Header{
                    {"content-type","application/json"},
                    {"X-signature", hmac<SHA1>(body,secret)}

                }
        );
    }
}