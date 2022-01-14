// LED pin definitions (anode)
#define LED_BLUE        33      // (local, OBC)
#define LED_GREEN       0       // (local, OBC)
#define LED_YELLOW      1       // (local, OBC)
#define LED_AMBER       32      // (local, OBC)

// GPIO pin definitions (PQ60 bus)
#define GPIO_0          2       // Digital IO, EPS IRQ
#define GPIO_1          14      // Digital IO, 12-bit true analogue DAC
#define GPIO_2          30      // Digital IO, I2C SDA
#define GPIO_3          29      // Digital IO, I2C SCL
#define GPIO_4          10      // Digital IO, UART TX (used for camera payload)
#define GPIO_5          9       // Digital IO, UART RX (used for camera payload)
#define GPIO_6          4       // Digital IO, CAN RX, PWM
#define GPIO_7          3       // Digital IO, CAN TX, PWM
#define GPIO_8          20      // Digital IO, 12-bit ADC, PWM
#define GPIO_9          13      // Digital IO, 13-bit differential / 12-bit single ended ADC
#define GPIO_10         12      // Digital IO, 13-bit differential / 12-bit single ended ADC
#define GPIO_11         5       // SD card chip select (Allows payloads to directly access SD card.)
#define GPIO_12         21      // Digital IO, 12-bit ADC, PWM

// SPI pin definitions
#define BUS_SPI_SCK     13      // SPI SCK clock (bus, CLK)
#define BUS_SPI_MOSI    11      // SPI MISO Master Out Slave In (bus, DO)
#define BUS_SPI_MISO    12      // SPI MOSI Master In Slave Out (bus, DI)
#define CS_SD           5       // SD card chip select (bus, GPIO 11)
#define SD_DETECT       31      // SD card detect (local, OBC)
#define CS_RFM          15      // Radio chip select (local, OBC)
#define NIRQ_RFM        16      // Radio IRQ pin (local, OBC)

// I2C pin definitions
#define BUS_I2C_SCL     19      // Primary I2C clock line
#define BUS_I2C_SDA     18      // Primary I2C data line

// I2C device address definitions
#define ADDR_EPS        0x2A    // Electrical Power System board I2C address
#define ADDR_TEMP       0x48    // TMP102 temperature sensor I2C address
#define ADDR_LIGHT      0x60    // SI1145 light sensor I2C address
#define ADDR_IMU_M      0x1C    // LSM9DS1 magnetometer I2C address
#define ADDR_IMU_AG     0x6A    // LSM9DS1 accelerometer / gyroscope I2C adress

// EPS output definitions
#define OUTPUT_3V3_1    0       // 1st switched 3.3V output, radio is powered from this line
#define OUTPUT_3V3_2    1       // 2nd switched 3.3V output, camera is powered from this line
#define OUTPUT_3V3_3    2       // 3rd switched 3.3V output, available for custom payloads
#define OUTPUT_BAT_1    3       // 1st switched battery output, available for custom payloads
#define OUTPUT_BAT_2    4       // 2nd switched battery output, available for custom payloads