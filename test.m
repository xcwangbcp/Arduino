clear 
a           = arduino('com16','uno','libraries','I2C');

global delaylength
delaylength = 0.01;
nbstep      = 20;
% channelA    = 12; % -- HIGH = forwards and LOW = backwards
% channelB    = 13; % -- HIGH = forwards and LOW = backwards
% disChannelA = 9;  % //brake (disable) CH A
% disChannelB = 8;  % //brake (disable) CH B
% sensorChan  = 5;
% sensor=readDigitalPin(a,'D5');
% while 
% Check for the sensor input
  for i=1:nbstep
  check_sensor(a);
  writeDigitalPin(a,'D9', 0);   %//ENABLE CH A
  writeDigitalPin(a,'D8', 1);   %//DISABLE CH B
  writeDigitalPin(a,'D12',1);   %//Sets direction of CH A
  writePWMVoltage(a,'D3', 5);    %//Moves CH A
  pause(delaylength);
  
  check_sensor(a);
  writeDigitalPin(a,'D9', 1);   %//DISABLE CH A
  writeDigitalPin(a,'D8', 0);   %//ENABLE CH B
  writeDigitalPin(a,'D13', 0); %//Sets direction of CH B
  writePWMVoltage(a,'D11', 5);   %//Moves CH B
  pause(delaylength);
  
  check_sensor(a);
  writeDigitalPin(a,'D9', 0); %//ENABLE CH A
  writeDigitalPin(a,'D8', 1); %//DISABLE CH B
  writeDigitalPin(a,'D12',0); %//Sets direction of CH A
  writePWMVoltage(a,'D3', 5);  %//Moves CH A
  pause(delaylength);
  
  check_sensor(a);
  writeDigitalPin(a,'D9',1);   %//DISABLE CH A
  writeDigitalPin(a,'D8',0);   %//ENABLE CH B
  writeDigitalPin(a,'D13',1);  %//Sets direction of CH B
  writePWMVoltage(a,'D11',5);        %//Moves CH B
  pause(delaylength);
  end
  stop_motor(a);
  
function stop_motor(a)
    delaylength = 0.01;
    writeDigitalPin(a,'D9',1);  %//DISABLE CH A
    writePWMVoltage(a,'D3', 0); %//stop Move CH A
    writeDigitalPin(a,'D8',1);  %//DISABLE CH B
    writePWMVoltage(a,'D11',0); %//stop Move CH B 
    pause(delaylength);
end
function check_sensor(a)
    sensor=readDigitalPin(a,'D5')
    if sensor ==0
       stop_motor(a);
    end
end
% end