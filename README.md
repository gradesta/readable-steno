# readable-steno

[Discord link](https://discord.com/channels/136953735426473984/1390298469813452810)

Imagine if you had a steno keyboard where the keys could move on their own. This would allow you to read haptically in the same way you typed. And perhapse at up to hundres of words per minute. Far faster than braille. This is the idea of our project. 

<img width="1200" height="592" alt="image" src="https://github.com/user-attachments/assets/336b565a-e12b-42d2-8278-ccda3fd47217" />

So far we have a prototype with LED lights rather than solenoids. In the future, we will replace these LEDs with electromagnets which can trigger the keys to jump up at you.


# Tutorial to replicate
### Prerquisites
There are some dependencies you will have to install before following this tutorial, these include dependencies both for the firmware and pico-sdk:
```
sudo apt install cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```
### Steps
1. Clone [the readable steno](https://github.com/gradesta/readable-steno#) and the [pico-sdk](https://github.com/raspberrypi/pico-sdk#) repositories: 
```
git clone git@github.com:gradesta/readable-steno.git
git clone git@github.com:raspberrypi/pico-sdk.git
```
2. Now we need to initiate the submodules, for pico-sdk as the tinyUsb module does not come installed in pico-sdk immediately:
```
cd pico-sdk
git submodule update --init
```

3. Before we can start building our project, we need a `dict.h` file, which the firmware expects to be present. To do this, we will use a .json steno dictionary. You can either use the same as us (typey-type-full.json) or add your own in its place. We will move to the `read_code` folder and run the translation script:
```
cd ../readable-steno/read_code
python3 translator.py <your_dict_name>.json
```
You should see a `dict.h` file now.


4. Next we will make a build folder and generate the necessary CMake files in it. If you are correctly following these steps, then the file paths should be the same:
```
mkdir build
cd build
cmake .. -DPICO_SDK_PATH=../../../pico-sdk
```

5. You should have several new files generated in the `build` folder. Now, just run:
```
make
```
And your firmware should be compiled.

6. After it is compiled a file called `read_code.uf2` will be in the `build` folder. This is the firmware for the board. To flash it, hold the reset button on the microcontroller while plugging it in. It should show up as a usb device. Now just drag the `read_code.uf2` file on it, wait while it flashes and you are done.

### Keep in mind
If you used the liatris  controller, then you cannot use GPIO 10 for the LEDs. In [this](https://github.com/gradesta/readable-steno/blob/main/dev_log/%235-11_08_2025-15_08_2025.md) dev-log we showed how we fixed it. The important thing is, not to forget to change the pin number in [led_driver.h](https://github.com/gradesta/readable-steno/blob/main/read_code/led_driver.h). 
