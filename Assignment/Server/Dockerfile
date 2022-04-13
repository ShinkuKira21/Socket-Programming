FROM ubuntu as developer-os
LABEL name="Edward Patch" email="1801492@student.uwtsd.ac.uk"
RUN g++ main.cpp ../Libraries/INet4Address.cpp -Wall -pthread


#### THE WEB Client ##############
FROM developer-os AS server
# Expose our webservers port number
EXPOSE 5100
# Execute the application
ENTRYPOINT ["./a.out"]