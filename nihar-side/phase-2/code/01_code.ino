#define MOTOR1 25
#define MOTOR2 26

#include <Wire.h>
#include <MPU6050.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= OLED SETTINGS =================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= MPU6050 =================

MPU6050 mpu;

int16_t ax, ay, az;

// ================= VARIABLES =================

float angleX;
float referenceAngle;

// ================= POSTURE SETTINGS =================

const float POSTURE_THRESHOLD = 10.0; // degrees
const unsigned long BAD_TIME = 5000;  // 5 seconds

bool badPosture = false;
unsigned long badStartTime = 0;

void setup()
{
    // Serial Monitor
    Serial.begin(115200);

    // I2C Pins for ESP32
    Wire.begin(21, 22);

    pinMode(MOTOR1, OUTPUT);
    digitalWrite(MOTOR1, LOW);

    pinMode(MOTOR2, OUTPUT);
    digitalWrite(MOTOR2, LOW);

    // Initialize MPU6050
    mpu.initialize();

    // Check MPU6050 connection
    if (mpu.testConnection())
    {
        Serial.println("MPU6050 Connected");
    }
    else
    {
        Serial.println("MPU6050 Connection Failed");
    }

    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED Not Found");

        while (1)
            ;
    }

    // Clear OLED
    display.clearDisplay();
    display.display();

    // Startup Message
    display.setTextSize(2);
    display.setTextColor(WHITE);

    display.setCursor(10, 20);
    display.println("START");

    display.display();

    delay(2000);

    // ================= CALIBRATION =================

    Serial.println("Sit Straight For Calibration");

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.println("SIT STRAIGHT");
    display.setCursor(0, 35);
    display.println("CALIBRATING...");
    display.display();

    float sum = 0;

    for (int i = 0; i < 100; i++)
    {
        mpu.getAcceleration(&ax, &ay, &az);

        float tempAngle =
            atan2(ay, az) * 180.0 / PI;

        sum += tempAngle;

        delay(20);
    }

    referenceAngle = sum / 100.0;

    Serial.print("Reference Angle: ");
    Serial.println(referenceAngle);

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 25);
    display.println("CALIBRATION DONE");
    display.display();

    delay(2000);
}

void loop()
{
    // Read Accelerometer Values
    mpu.getAcceleration(&ax, &ay, &az);

    // Calculate Tilt Angle
    angleX = atan2(ay, az) * 180 / PI;

    // Calculate Deviation
    float deviation = angleX - referenceAngle;

    // Serial Monitor
    Serial.print("Current: ");
    Serial.print(angleX);

    Serial.print("  Ref: ");
    Serial.print(referenceAngle);

    Serial.print("  Dev: ");
    Serial.println(deviation);

    // Clear OLED
    display.clearDisplay();

    // Title
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SMART POSTURE");

    // Angle Display
    display.setCursor(0, 15);
    display.print("Angle: ");
    display.print(angleX);

    display.setCursor(0, 25);
    display.print("Dev: ");
    display.print(deviation);

    // ================= POSTURE LOGIC =================

    if (abs(deviation) > POSTURE_THRESHOLD)
    {
        if (!badPosture)
        {
            badPosture = true;
            badStartTime = millis();
        }

        if (millis() - badStartTime >= BAD_TIME)
        {
            digitalWrite(MOTOR1, HIGH);
            digitalWrite(MOTOR2, HIGH);
        }

        display.setTextSize(2);
        display.setCursor(0, 45);
        display.println("SLOUCH");
    }
    else
    {
        badPosture = false;

        digitalWrite(MOTOR1, LOW);
        digitalWrite(MOTOR2, LOW);

        display.setTextSize(2);
        display.setCursor(10, 45);
        display.println("GOOD");
    }

    // Update OLED
    display.display();

    delay(100);
}