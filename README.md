# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## Reflection

Two separate PID controllers were implemented in this project. The first to control the cross track error (keep the car at the center of the road) by manipulating the steering angle and the second is maintaining the speed of the vehicle by controlling the throttle.

#### Describe the effect each of the P, I, D components had in your implementation:

* P term: The proportional term is the most intuitive term in the PID controller. It directly scales the error value so that the control variable takes action to minimize this error. For example, the steering angle will be a scaled value of the cross track error in the first P controller and the throttle will be proportional to the speed error in the second controller of only a proportional term was used. While this term is essential in minimizing the errors, relying only the p term can cause overshoots which are represented by wobbling for cross track distance control and cycle of accelerating and breaking for speed control.

* D term: The derivative term is essential for smoothening the response of the system and minimize overshoot problems associated with proportional control. By taking action to counter,the rate at which the error value changes, very drastic and fast response of the system is countered even if this change was in the direction to minimize the error. This leads to a smoother response with minimal overshoot once parameters are tuned appropriately. In the case of this project, the D term proved effective in solving the wobbling in cross track distance control and almost entirely eliminate the cycles of accelerating and breaking for speed control. The main issue with the D term is when high frequency measurement noise exists as these can cause rates of change in the measured error signal that do not represent the actual rate of change of the process variable. 

* I term: The integral term of a PID controller is concerned with the integral (sum) of all measured error values, this sum is then scale by the integral gain and set for the manipulated value. The integral term helps in eliminating small errors in which the efforts of the proportional term are not enough to eliminate, practically, this becomes more useful in the presence of disturbances. In this case, the benefit of the integral term was more apparent in the vehicle velocity control loop where even small velocity errors die out with time. In cross track distance control loop, high integral gain values would severely cause overshoots, which in turn causes the car to wobble. 

#### Describe how the final hyperparameters were chosen:

As shown above, all of the PID parameters can play a role in minimizing errors and enhancing the response of a system, however, all of the terms can have a negative effect on the behavior of the system as well. Therefore, it is important to carefully tune PID parameters to ensure that the overall system behaves appropriately. 

For the cross track distance control, the twiddle method was first used to find initial PID parameters. These initial parameters provided satisfactory performance as the car did not leave the track but suffered from overshoots that clearly visible where the car would frequently shift to the other side of the road and keep doing so for a while. Manual tuning was then used to counter this problem where the D term was increased, and the I term was strongly minimized. This helped minimize overshoots in general, but another problem appeared where the car would strongly steer suddenly even it was almost at the center of the road. A solution that proved sufficient was implementing a low pass filter on the error signal prior to passing it to the PID controller. The time constant of the low pass filter was manually selected through trial.

As for the speed controller, the PID parameters and the filter's time constant were manually tuned and good results were obtained without the need for an extensive tuning process.


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

