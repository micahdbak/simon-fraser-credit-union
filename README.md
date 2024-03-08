# DNS-Transaction-Challenge-2024
The Public Interface for the DNS Transaction Challenge


Please note that due to limited server capacity for this event
we implore you to limit calls to our server through these APIs
to only one function call every second, idealy once every 5 or so seconds.

We understand if some minor exeptions to this are required and have the capacity to support this, but please if possible comply with this message.

The network has security and will auto detect users abusing the network with high frequency calls, users will have their access auto removed by the network security protocal if sufficent calls are made within a quick time period.

Also please note this event's APIs do not have high security built in, so please do not send any sensitive information via API calls (or API calls beyond the scope of this event).

If an API call beyond what is provided is required, contact the DNS execs for support in making a custom API call.


Here are some examples of how to delay a stream in Python, C, Java and C++:
```
#python
import time

def delay_one_second():
    time.sleep(1)

#Usage
delay_one_second()
print("Program continues after 1-second delay.")
#python
```
________________________________
```
//C
#include <unistd.h>

void delay_one_second() {
    sleep(1);
}

//Usage
delay_one_second();
printf("Program continues after 1-second delay.\n");
//C
```
________________________________
```
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
```
________________________________
```
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
```
________________________________


DNS Bank API:

Dependencies: BSD Sockets (Build into most UNIX-like Systems) || winsock (For C/C++ on Windows Only)

```
bank_verify(account_id: str, subject: str, first_arg: str, second_arg="")
#Bank Verifications take Account ID, String Inputs's ("NAME", "CODE", "PASS")
#and then the corresponding verifications and will return if the Account ID
#is accociated with the correspoing name/transaction code/password.
#Use First Arg for: First Name. Transaction Code, Password.
#Use Secont Arg for: Last Name. Will return a string status

bank_transfer(account_from:str, account_to:str, secure_code: str, amount: str)
#Bank Transfers Take a From Account & From Transaction Code and deposit the amount in the To Account. Will return a string message

bank_get_info(account_id: str)
#Information Requests will return information about a users account for networks to verify in the form of a string message.

bank_status()
#Will return if the Bank Server is Online

bank_time()
#Will return the current time of the Bank Server (In Saskachuwan Time CST)
```
```
#Example Use:
import dns_bank_api as dns

def main():
	result = dns.bank_status()
	print(result)
main()
```
________________________________
DNS Network API:

Dependencies: BSD Sockets (Build into most UNIX-like Systems) || winsock (For C/C++ on Windows Only)

```
network_check(network_id: str)
#Network Checks will inform the user how many packets are waiting to be processed in the server. Returns a String.

network_request(network_id: str)
#Network Requests will gram the oldest stored packet in the network que return it to you as a string and the remove the packet from the que.

network_status()
#Will return if the Network Server is Online

network_time()
#Will return the current time of the Network Server (In Saskachuwan Time CST)
```
```
#Example Use:
import dns_network_api as dns

def main():
	result = dns.network_check("888")
	print(result)
main()
```
________________________________
Objective:
```
Be the first person to create a Bebit and or Credit Card Network.
Sign up our merchent vendors.
Sign up one of our execs to your network.
And pay for your prize using balence from the DNS Bank(or your bank of choice).
```
