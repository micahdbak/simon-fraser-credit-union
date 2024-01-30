# DNS-Transaction-Challenge-2024
The Public Interface for the DNS Transaction Challenge


Please note that due to limited server capacity for this event
we implore you to limit calls to our server through these APIs
to only one function call every second, idealy once every 5 or so seconds.

We understand if some minor exeptions to this are required and have the capacity to support this, but please if possible comply with this message.

The network has security and will auto detect users abusing the network with high frequency calls, users will have their access auto removed by the network security protocal if sufficent calls are made within a quick time period.

Also so please note this events APIs does not have high scurity built in there for please do not send any sensitive information via API calls or API calls behond the scope of this event.

If an API call behond what is provided is required, contact the DNS execs for support in making a custom API call.


Here are some examples of how to delay a stream in Python, C, Java and C++:

#python
import time

def delay_one_second():
    time.sleep(1)

#Usage
delay_one_second()
print("Program continues after 1-second delay.")
#python


//C
#include <unistd.h>

void delay_one_second() {
    sleep(1);
}

//Usage
delay_one_second();
printf("Program continues after 1-second delay.\n");
//C


//Java
public class DelayExample {
    public static void delayOneSecond() {
        try {
            Thread.sleep(1000); // 1000 milliseconds = 1 second
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    //Usage
    public static void main(String[] args) {
        delayOneSecond();
        System.out.println("Program continues after 1-second delay.");
    }
}
//Java


//C++
#include <iostream>
#include <thread>
#include <chrono>

void delayOneSecond() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//Usage
int main() {
    delayOneSecond();
    std::cout << "Program continues after 1-second delay." << std::endl;
    return 0;
}
//C++
________________________
**Documentation:**
________________________
**Network API Docs:**
________________________
**Bank API Docs:**

