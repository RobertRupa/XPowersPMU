#include "esphome.h"

#define XPOWERS_CHIP_AXP2101
#include "XPowersLib.h"

#define I2C_SDA                     (7)
#define I2C_SCL                     (6)

class AXP2101Component : public Component {
 public:
  void setup() override {
    // This will be called once to set up the component
    // think of it as the setup() call in Arduino
    ESP_LOGD("custom", "Custom component setup");
    
    if (!PMU.begin(Wire, AXP2101_SLAVE_ADDRESS, I2C_SDA, I2C_SCL)) {
        Serial.println("Failed to initialize power.....");
        while (1) {
            delay(5000);
        }
    }
    //Set the working voltage of the camera, please do not modify the parameters
    PMU.setALDO1Voltage(1800);  // CAM DVDD  1500~1800
    PMU.enableALDO1();
    PMU.setALDO2Voltage(2800);  // CAM DVDD 2500~2800
    PMU.enableALDO2();
    PMU.setALDO4Voltage(3000);  // CAM AVDD 2800~3000
    PMU.enableALDO4();

    // TS Pin detection must be disable, otherwise it cannot be charged
    PMU.disableTSPinMeasure();
    
  }
  private:
    XPowersPMU  PMU;
};