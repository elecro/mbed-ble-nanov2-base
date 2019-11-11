#ifndef SERVICE_COUNTER
#define SERVICE_COUNTER

#include <ble/BLE.h>

class ServiceCounter
{
public:
    const static uint16_t SERVICE_UUID = 0xAA00;
    const static uint16_t CHARACTERISTIC_UUID = 0xAA0F;

    ServiceCounter(BLE& ble, uint8_t initValue = 2)
        : m_ble(ble)
        , m_value(initValue)
        , m_valueChar(CHARACTERISTIC_UUID, &m_value, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        /* Build the service characteristic table: */
        GattCharacteristic* table[] = {
            &m_valueChar,
        };
        /* Build the service. */
        GattService service(SERVICE_UUID, table, sizeof(table) / sizeof(table[0]));

        /* Register the service in the BLE interface. */
        m_ble.gattServer().addService(service);
        /* Register a "DataWritten" callback. */
        m_ble.gattServer().onDataWritten(this, &ServiceCounter::onDataWritten);
    }

    void startCounter(EventQueue& queue, int interval_ms)
    {
        /* Update the counter value in every "interval_ms". */
        queue.call_every(interval_ms, this, &ServiceCounter::valueIncrement);
    }

    void valueIncrement(void)
    {
        m_value++;
        m_ble.gattServer().write(m_valueChar.getValueAttribute().getHandle(),
                                 &m_value, sizeof(m_value));
    }

private:

    void onDataWritten(const GattWriteCallbackParams* params)
    {
        /* Check if the data received is for this characterisic. */
        if (params->handle != m_valueChar.getValueAttribute().getHandle()) {
            return;
        }
        printf("Recived Data!\r\n");

        printf(" Data length: %d\r\n", params->len);
        printf(" Data: %d\r\n", params->data[0]);

        /* Update characteristic with the new value. */
        m_value = params->data[0];
        m_ble.gattServer().write(m_valueChar.getValueAttribute().getHandle(),
                                 &m_value, sizeof(m_value));
    }

    BLE& m_ble;
    uint8_t m_value;
    ReadWriteGattCharacteristic<uint8_t> m_valueChar;
};


#endif
