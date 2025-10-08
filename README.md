# readable-steno

[Discord link](https://discord.com/channels/136953735426473984/1390298469813452810)

Imagine if you had a steno keyboard where the keys could move on their own. This would allow you to read haptically in the same way you typed. And perhapse at up to hundres of words per minute. Far faster than braille. This is the idea of our project. 

<img width="1200" height="592" alt="image" src="https://github.com/user-attachments/assets/336b565a-e12b-42d2-8278-ccda3fd47217" />

So far we have a prototype with LED lights rather than solenoids. In the future, we will replace these LEDs with electromagnets which can trigger the keys to jump up at you.


# Tutorial to replicate
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

3. Move to `readable-steno/read-code` and make a `build` folder and enter it:
```
cd ../readable-steno/read-code
mkdir build
cd build
```

4. Now we will generate the CMake files, if you are correctly following these steps, then the file paths should be the same:
```
cmake .. -DPICO_SDK_PATH=../../../pico-sdk
```

5. You should have several new files generated in the `build` folder, you can try to use:
```
make
```
But it will fail, on a missing header file, to fix it we have to move up to `read-code`:
```
cd ..
```
Here you will see a file with the same name, but .json. This is the dictionary the board uses. If you want to change it, you can, but make sure the new json dict has the same structure. To create the header file we will use the provided python script:
```
python3 translator.py <your_dict_name>.json
```
After the script you should see a new file called `dict.h`. Now we can move back to build and compile it:
```
cd build
make
```

6. After it is compiled a file called `read_code.uf2` will be in the `build` folder. This is the firmware for the board. To flash it, hold the reset button on the microcontroller while plugging it in. It should show up as a usb device. Now just drag the `read_code.uf2` file on it, wait while it flashes and you are done.

## Keep in mind
If you used the liatris  controller, then you cannot use GPIO 10 for the LEDs. In [this](https://github.com/gradesta/readable-steno/blob/main/dev_log/%235-11_08_2025-15_08_2025.md) dev-log we showed how we fixed it. The important thing is, not to forget to change the pin number in [led_driver.h](https://github.com/gradesta/readable-steno/blob/main/read_code/led_driver.h). 