The c++ server will receive a request from the UI and update the results. For the solution, I used POST request to update the weather.
 - The server will receive and update the values in JSON format
 - I used HTTP listener library to handle the request and JSON library.
 - There are three void functions inside the server: 
 1- The first function is to display JSON which will serialize the value
2- The second function is to handle request, which will receive the JSON data from the UI and give an answer
3- The third function is to handle posts, which will update the JSON data, based on the key and the value of the received format.
The right way persuing in this format was to use GET request, unfortunately the libraries that i decided to use did not support that and when they received data they will instantly report it as NULL

I tried to implement the c++ server to receive the data from weather API, however with no success. So I decided to write the weather conditions inside the server.

## Python Tester
    -I was not able to complete the test phase in python, but I do believe this is the code needed for the test.

## UI
    -The user will be presented with the option to choose city and day. However, the server only supports the capital of Bulgaria at the moment. After the user chooses a city he will be able to choose the weather for 3 days. Today, Tomorrow, and Yesterday. 

## Installation
To start the c++ server, you will need to install vcpkg, boost, cmake, openssl
for the python tester, you will need to install urllib3.
To eliminate CORS errors, I added firefox extension to the browser because disabling google web security did not work for me in google chrome
