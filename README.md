<div align='center'><img src='./img/QCFA.png' alt="QCFA" width="350" height="350" style="display: block; margin: 0 auto"/>

![GitHub issues](https://img.shields.io/github/issues/AbdoullahBougataya/QCFA?style=flat-square&logo=github&logoColor=cyan&color=cyan&link=https://github.com/AbdoullahBougataya/QCFA/issues?q=is%3Aopen)
![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/t/AbdoullahBougataya/QCFA/main?style=flat-square&logo=git&logoColor=cyan&color=cyan&link=https://github.com/AbdoullahBougataya/QCFA/commits/main)
![GitHub](https://img.shields.io/github/license/AbdoullahBougataya/QCFA?style=flat-square&logo=firefox&logoColor=cyan&color=cyan&link=https://github.com/AbdoullahBougataya/QCFA/blob/main/LICENSE)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/AbdoullahBougataya/QCFA?style=flat-square&logo=github&logoColor=cyan&color=cyan&link=%23)
![Static Badge](https://img.shields.io/badge/Runs_on-Arduino_UNO-cyan?style=flat-square&logo=arduino&logoColor=cyan&link=https://store.arduino.cc/products/arduino-uno-rev3)
![Build Status](https://img.shields.io/badge/build-passing-cyan?style=flat-square&logo=arduino&logoColor=cyan)

###### 🕹️ **Q**uadcopter **C**ontrol **F**unctions using **A**rduino Uno 🕹️
</div>

</div>

---

# How to use it ?

## Installation 💾:

### Manually:

#### Windows:

Please skip this command if you already installed the Servo library:

```
git clone https://github.com/arduino-libraries/Servo.git <YOUR PROJECT DEPENDENCIES DIRECTORY>\Servo
```

then Run:

```
git clone https://github.com/AbdoullahBougataya/QCFA.git <YOUR PROJECT DEPENDENCIES DIRECTORY>\QCFA
```

#### Mac or Linux:

Please skip this command if you already installed the Servo library:

```
git clone https://github.com/arduino-libraries/Servo.git <YOUR PROJECT DEPENDENCIES DIRECTORY>/Servo
```

then Run:

```
git clone https://github.com/AbdoullahBougataya/QCFA.git <YOUR PROJECT DEPENDENCIES DIRECTORY>/QCFA
```

# Use cases

First set the ESCs to the Arduino UNO pins 3, 5, 6 and 9 as shown in the image below:

Create this `main.cpp` file:

```
#include <Arduino.h>
#include <Servo.h>
#include <QCFA.h>

void setup()
{
  int motor1_esc_pin = 3;
  int motor2_esc_pin = 5;
  int motor3_esc_pin = 6;
  int motor4_esc_pin = 9;
  mass = 0.3525;  /* variable of the mass */
  radius = 0.038; /* variable of the propeller radius */
  voltage = 22.8; /* variable of the battery voltage */
  KVs = 2450;     /* variable of the KVs of the motor */
  /* The pulse width attached to pins 9, 3, 5, 6
   have a minimum of 1000 µs and maximum of 2000 µs */
  ESC1.attach(motor1_esc_pin, 1000, 2000);
  ESC2.attach(motor2_esc_pin, 1000, 2000);
  ESC3.attach(motor3_esc_pin, 1000, 2000);
  ESC4.attach(motor4_esc_pin, 1000, 2000);
  bool calibrated = false; /* Set calibrated to false if it's the first time */
  if (calibrated == false)
  {
    calibrate(20000); /*20000 µs is the time taken by the ESC to be calibrated (it may vary depending on the ESCs used)*/
  }
}

void loop()
{
  ESC1.write(90);
  exit(0);
}
```

Then build it to the Arduino UNO.
