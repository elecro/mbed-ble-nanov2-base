// Copyright (c) 2019 elecro
//
// Licensed under the BSD 3-Clause License
// <LICENSE.md or https://opensource.org/licenses/BSD-3-Clause>.
// This file may not be copied, modified, or distributed except
// according to those terms.

#include "blue.hpp"

#include <mbed.h>

void blue_AdvertisementCallback(const Gap::AdvertisementCallbackParams_t* params)
{
    /* Address is in little endian, thus the reverse order. */
    printf("AD Remote: [%02x:%02x:%02x:%02x:%02x:%02x] rssi: %d\r\n",
               params->peerAddr[5], params->peerAddr[4], params->peerAddr[3],
               params->peerAddr[2], params->peerAddr[1], params->peerAddr[0],
               (int)params->rssi);

    /* Process the AdvertisementCallbackData: */
    for (uint8_t data_idx = 0; data_idx < params->advertisingDataLen; data_idx++)
    {
        /* Advertisment data (AD) format (array of bytes):
         * n.   byte: Advertising data entry length.
         * n+1. byte: Type of the data. (Name, Service uuid, etc.)
         * n+2+ bytes: payload, contents of the data
         *
         * mbed info: features/FEATURE_BLE/ble/GapAdvertisingData.h
         */

        /* The first byte of the AD entry is the length of the entry.
         *
         * It is possible that there is no data for a given entry.
         *  Skip them for now.
         */
        const uint8_t record_length = params->advertisingData[data_idx];
        if (record_length == 0)
        {
            continue;
        }

        /* The second byte (usually) of the AD entry is the type information.*/
        const uint8_t type = params->advertisingData[data_idx + 1];

        /* From the third byte it is the payload of the AD entry */
        const uint8_t value_length = record_length - 1;
        const uint8_t* value_ptr = params->advertisingData + data_idx + 2;

        switch (type) {
            case GapAdvertisingData::SHORTENED_LOCAL_NAME:
            case GapAdvertisingData::COMPLETE_LOCAL_NAME: {
                /* The "device name" is a series of charactes (bytes). */
                printf(" Found NAME: ");
                for (uint8_t byte = 0; byte < value_length; byte++) {
                    printf("%c", value_ptr[byte]);
                }
                printf("\r\n");
                break;
            }
            case GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS: {
                /* The 16 bit UUIDss are array of two bytes in little endian. */
                printf(" Found 16bit UUIDs:\r\n");
                for (uint8_t idx = 0; idx < value_length; idx += 2) {
                    uint16_t service_uuid = (value_ptr[idx + 1] << 8) | (value_ptr[idx + 0]);
                    printf("%d. 0x%04x\r\n", idx + 1, service_uuid);
                }
                break;
            }
            default: {
                printf(" Got adv packet type: %02x (%d bytes): ", type, value_length);
                for (uint8_t byte = 0; byte < value_length; byte++) {
                    printf("%02x ", value_ptr[byte]);
                }
                printf("\r\n");
                break;
           }
        }

        data_idx += record_length;
    }
    wait(1);
}

void blue_StartScan(BLE& ble)
{
    /* Scan for BLE devices. */
    ble.gap().setScanParams(600, 500, 0, true);
    ble.gap().startScan(blue_AdvertisementCallback);
}




/* BLE connection callback
 *
 * Note: ATM only one connection can be done in parallel.
 */
void blue_ConnectedCallback(const Gap::ConnectionCallbackParams_t* params)
{
    const BLEProtocol::AddressBytes_t& peer_addr = params->peerAddr;

    /* Address is in little endian, thus print it in reverse order. */
    printf("Connection form: [%02x:%02x:%02x:%02x:%02x:%02x]",
           peer_addr[5], peer_addr[4], peer_addr[3],
           peer_addr[2], peer_addr[1], peer_addr[0]);

    /* In a connection a device has its own role:
     *  * Central: This device can search for services/characteristics and access them.
     *  * Peripheral: This device is the "data provider", it should have it's own service(s)/characteristic(s).
     */
    switch (params->role) {
        case Gap::CENTRAL: printf(" and I'm a CENTRAL device"); break;
        case Gap::PERIPHERAL: printf(" and I'm a PERIPHERAL device"); break;
        default: break;
    }
    printf("\r\n");
}

void blue_DisconnectedCallback(const Gap::DisconnectionCallbackParams_t *params)
{
    printf("Disconnected\r\n");
    /* After disconnection the advertisement and scanning could be restarted. */
}

void blue_AddConnectionCallbacks(BLE& ble)
{
    Gap& gap = ble.gap();
    gap.onConnection(blue_ConnectedCallback);
    gap.onDisconnection(blue_DisconnectedCallback);
}
