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
}

void loop()
{

    // Read Accelerometer Values
    mpu.getAcceleration(&ax, &ay, &az);

    // Calculate Tilt Angle
    angleX = atan2(ay, az) * 180 / PI;

    // Print on Serial Monitor
    Serial.print("Angle X: ");
    Serial.println(angleX);

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

    // Posture Logic
    if (abs(angleX) > 20)
    {

        digitalWrite(MOTOR1, HIGH);
        delay(500); // Vibrate for 500ms

        digitalWrite(MOTOR1, LOW);
        delay(700); // Pause for 700ms

        digitalWrite(MOTOR2, HIGH);
        delay(500); // Vibrate for 500ms

        digitalWrite(MOTOR2, LOW);
        delay(700); // Pause for 700ms

        display.setTextSize(2);

        display.setCursor(0, 40);
        display.println("SLOUCH");
    }
    else
    {

        digitalWrite(MOTOR1, LOW);
        digitalWrite(MOTOR2, LOW);

        display.setTextSize(2);

        display.setCursor(0, 40);
        display.println("GOOD");
    }

    // Update OLED
    display.display();

    delay(500);
}