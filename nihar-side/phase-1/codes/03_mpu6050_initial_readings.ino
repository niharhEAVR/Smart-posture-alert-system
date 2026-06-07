#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup()
{
    Serial.begin(115200);

    Wire.begin(21, 22);

    mpu.initialize();
    delay(500);

    if (mpu.testConnection())
        Serial.println("MPU6050 Connected!");
    else
        Serial.println("Connection Failed");
}

void loop()
{

    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    mpu.getMotion6(
        &ax, &ay, &az,
        &gx, &gy, &gz);

    Serial.print("AX: ");
    Serial.print(ax);

    Serial.print(" AY: ");
    Serial.print(ay);

    Serial.print(" AZ: ");
    Serial.println(az);

    delay(500);
}