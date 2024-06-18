# Penguin Readme

## Motors

The device has 4 motors and 4 motor controllers. This readme assumes the current configuration and placement of the mini cube is as provided to team Penguin in week 3. 

### Motor Connections

In this specific case:
- **Right Motor**:
  - Connect the 3 pins from the motor controller to the pins on the Jetson labeled 33, 37, and 35.
    - 33 is the PWM signal pin.
    - 35 is the high pin.
    - 37 is the low pin.

- **Left Motor**:
  - Connect the 3 pins from the motor controller to the pins on the Jetson labeled 32, 34, and 36.
    - 32 is the PWM signal pin.
    - 34 is the high pin.
    - 36 is the low pin.

Details on these pins and their functions can be found in the motor controller datasheet. For more information, refer to the [L298N Motor Controller Datasheet](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf). Details on which pin is which on the jetson board can be found using this manual: [J202 Jetson board Datasheet]("[https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf](https://files.seeedstudio.com/products/102991695/reComputer%20J202%20datasheet.pdf)"). Additionally you can also look at the board anc figure out pin numbers since they are written on it.

### Running the Code

1. After the pins have been connected successfully, to run the code, simply execute the following command:
   ```sh
   ros2 run motor_controller_pkg keyboard_control
   ```

2. A terminal should open up. This terminal is currently reading your keyboard inputs.

3. **Keyboard Controls**:
   - `w` - Move forward (both motors move forward).
   - `s` - Move backward (both motors move in reverse).
   - `d` - Spin right (opposite rotation to opposite motors).
   - `a` - Spin left (opposite rotation to opposite motors).
   - `q` - Stop all motors.
   - Any other button - Stops all motors.

### Changing Speed

To change the speed of the vehicle, use the following command:
```sh
ros2 topic pub /motor_speed std_msgs/Float32 "data: 50.0"  # 50% duty cycle
```
- Change the `50.0` to the desired percentage.

The code runs with a default speed of 50% and continuously monitors the speed change on a topic. This command updates the speed on that topic.

Note that the `50%` value represents power, not speed. It is analogous to pressing the gas pedal in a car. Consistently keeping it at 50% does not ensure 50% speed; it ensures 50% force from the motors at all times. Given that mass is constant, force is proportional to acceleration (F = ma).
