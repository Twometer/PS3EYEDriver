# PS3EYEDriver
PS3EYE Camera Driver for OSX and Windows

This is an extended version of the [OpenTrack PSEYEDriver](https://github.com/opentrack/PS3EYEDriver).
It adds a C interface that's exported as a Windows DLL, so that it can be embedded into other software.

## Building
Building it requires [`libusb-1.0`](https://github.com/libusb/libusb/releases) as a dependency. Create a `lib` folder in the project root and place
the `*.lib` and `*.h` files for `libusb-1.0` in it, then run CMake.

## Setup
These are the setup instructions for a PS3 Eye camera with this driver from the OpenTrack site:

1. Uninstall any previous driver.
2. Use the [zadig](https://zadig.akeo.ie/) program to install the libusb-win32 driver onto interface 0 of the camera. Don't use the WinUSB driver!
3. If it fails to work, try connecting the camera onto a USB 2.0 or a USB 3.0 controller that you haven't used yet. Then run zadig again.
4. In Device Manager, make sure the driver is assigned to the device. If it's not, use the "update driver" button to select libusb (it's its own category).
