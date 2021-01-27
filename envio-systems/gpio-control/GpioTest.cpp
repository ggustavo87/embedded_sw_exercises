
/**
 * @file   GpioTest.cpp
 *
 * @brief  Toggles gpio X (every second) when​ gpio​ Y in HIGH.
 *
 * @author gustavo.garcia
 * @date   Jan 23, 2021
 */

/* INCLUDES ******************************************************************/
#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>


/* DEFINITIONS ***************************************************************/

const size_t GPIO_UNDEFINED = 0xffff;
const size_t HIGH           = 1;
const size_t LOW            = 0;

int alive = true;

/* USINGS ********************************************************************/
using namespace std; 

/* STATIC DECLARATIONS *******************************************************/

/**
 * @brief Handles Ctrl+c signal.
 *
 * @param sig The signal received.
 */ 
void sigint_handler(int sig)
{
  alive = false;
}

/**
 * @brief Exports the desired gpio.
 *
 * @param gpioId The gpio Id to be exported.
 */
void gpio_export(int gpioId) {
  string exportFile = "/sys/class/gpio/export" ;

  int fd = open(exportFile.c_str(), O_WRONLY);

  if (fd == -1) {
    cout <<"Unable to open /sys/class/gpio/export" << endl;
    exit(EXIT_FAILURE);
  }
    
  string gpioString = to_string(gpioId);

  if (write(fd, gpioString.c_str(), gpioString.length()) != gpioString.length()) {
    cout <<"Error writing to /sys/class/gpio/export" << endl;
    exit(EXIT_FAILURE);
  }

  close(fd);
}

/**
 * @brief Sets the gpio as input/output .
 *
 * @param gpioId    The gpio Id to be exported.
 * @param direction The desired direction.
 */
void gpio_set_direction(int gpioId, string direction) {
  string directionPath = "/sys/class/gpio/gpio" + to_string(gpioId) + "/direction";

  int fd = open(directionPath.c_str(), O_WRONLY);

  if (fd == -1) {
    cout <<"Unable to open " << directionPath << endl;
    exit(1);
  }

  if (write(fd, direction.c_str(), strlen(direction.c_str())) != strlen(direction.c_str())) {
    cout <<"Error writing to " << directionPath << endl;
    exit(1);
  }

  close(fd);
}

/**
 * @brief Toggles gpio output.
 *
 * @param fd The sysfs file descriptor to be toggled.
 */
void gpio_toggle_pin(int fd) {
  char buffer[2]="";

  read(fd, buffer, 1);

  if (strcmp(buffer, to_string(HIGH).c_str()))
    write(fd, to_string(HIGH).c_str(), 1);
  else
    write(fd, to_string(LOW).c_str(), 1);
}

/**
 * @brief Application entry point.
 *
 * @param argc The number of arguments.
 * @param argv The arguments collection.
 *
 * @return 0 if successful; otherwise, an error code.
 */
int main(int argc, char **argv)
{ 
  signal(SIGINT, sigint_handler);

  int option;
  int gpioIn = GPIO_UNDEFINED;
  int gpioOut = GPIO_UNDEFINED;

  cout << "I: Checking Parameters.\n" << endl;

  while ((option = getopt (argc, argv, "o:i:")) != -1)
  {
    switch (option)
    {
      case 'i':
        gpioIn = atoi(optarg);
        break;

      case 'o':
        gpioOut = atoi(optarg);
        break;

      default:
        cout << "Usage: %s [-i GPIO_IN] [-o GPIO_OUT]\n" << endl;
        exit(EXIT_FAILURE);
    }
  }

  if (gpioIn == GPIO_UNDEFINED || gpioOut == GPIO_UNDEFINED)  {
    cout << "Usage: %s [-i GPIO_IN] [-o GPIO_OUT]\n" << endl;
    exit(EXIT_FAILURE);
  }

  gpio_export(gpioIn);
  gpio_export(gpioOut);

  gpio_set_direction(gpioIn, "in");
  gpio_set_direction(gpioOut, "out");

  string gpioInPath = "/sys/class/gpio/gpio" + to_string(gpioIn) + "/value";
  string gpioOutPath = "/sys/class/gpio/gpio" + to_string(gpioOut) + "/value";

  int fdIn = open(gpioInPath.c_str(), O_WRONLY);
  int fdOut = open(gpioInPath.c_str(), O_WRONLY);


  while(alive)
  {
    char inBuffer[2]="";

    read(fdIn, inBuffer, 1);
    
    if (strcmp(inBuffer, to_string(HIGH).c_str())) {
      write(fdOut, to_string(LOW).c_str(), 1);
    }
    else {
      gpio_toggle_pin(fdOut);
    }
    sleep(1);
  }

  close(fdIn);
  close(fdOut);

  return 0;
}

