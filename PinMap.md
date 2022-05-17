# Arduino Mega

- Pin  6 (PWM)        -> Motor Right Forward
- Pin  7 (PWM)        -> Motor Right Backward
- Pin  8 (PWM)        -> Motor Right PWM

- Pin  9 (PWM)        -> Motor Left Forward
- Pin 10 (PWM)        -> Motor Left Backward
- Pin 11 (PWM)        -> Motor Left PWM

- Pin 14 (TX3)        -> (<-> Nano 8 (SoftwareSerial RX))
- Pin 15 (RX3)        -> (<-> Nano 9 (SoftwareSerial TX))

**TODO :**
- Switch Yellow/Blue
- Tirette
- Encoders Left/Right (needs interrupt pins)
- Servos actionners x3 Left + x3 Right
- Vacuum pump Left/Right
- Status LEDs ? (Yellow/Blue, Fault, wait for tirette)

# Arduino Nano

- Pin  0 (RX)         ->
- Pin  1 (TX)         ->
- Pin  2 (INT0)       ->
- Pin  3 (INT1/PWM)   ->
- Pin  4              -> Sonar 0 Trigger
- Pin  5 (PWM)        -> Sonar 0 Echo
- Pin  6 (PWM)        -> Sonar 1 Trigger
- Pin  7              -> Sonar 1 Echo
- Pin  8              -> SoftwareSerial RX (<-> Mega 14 (TX3))
- Pin  9 (PWM)        -> SoftwareSerial TX (<-> Mega 15 (RX3))
- Pin 10 (SS/PWM)     -> Sonar 2 Trigger
- Pin 11 (MOSI/PWM)   -> Sonar 2 Echo
- Pin 12 (MISO)       -> Sonar 3 Trigger
- Pin 13 (SCK)        -> Sonar 3 Echo
- Pin 14/A0 (ADC)     ->
- Pin 15/A1 (ADC)     ->
- Pin 16/A2 (ADC)     ->
- Pin 17/A3 (ADC)     ->
- Pin 18/A4 (ADC/SDA) ->
- Pin 19/A5 (ADC/SCL) ->
- Pin A6 (ADC only)   ->
- Pin A7 (ADC only)   ->
